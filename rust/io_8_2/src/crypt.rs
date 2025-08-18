use sha1::{Sha1, Digest};
use sha2::Sha256;
use uint::construct_uint;
use rand::prelude::*;

// const p:i32 = 0;
// const q:i32 = 0;
const E:i32 = 65537;            // via openssl

fn square_and_multiply(x: U1024, a: U1024, m: U1024) -> U1024 {
    let mut result = U1024::from(1);
    let mut base = x % m;
    let mut exponent = a;

    while exponent > U1024::from(0) {
        if exponent % 2 == U1024::from(1) {
            result = (result * base) % m;
        }
        base = (base * base) % m;
        exponent /= 2;
    }

    result
}

fn vec_u8_to_u1024(bytes: Vec<u8>) -> U1024 {
    if bytes.len() > 128 {
        panic!("Input too long: exceeds 1024 bits");
    }

    let mut padded = [0u8; 128];
    padded[128 - bytes.len()..].copy_from_slice(&bytes);
    U1024::from_big_endian(&padded)
}

pub fn u1024_to_vec_u8(value: U1024) -> Vec<u8> {
    let bytes = value.to_big_endian();
    bytes.to_vec()
}


pub fn mgf(seed: &Vec<u8>, length: usize) -> Option<Vec<u8>>{
    let mut hasher = Sha256::new();
    let h_len: i64 = 32;
    if length as i64 > (h_len << 32)
    {
        return None;
    }
    let mut t: Vec<u8> =  vec![];

    let mut counter: i64 = 0;
    while t.len() < length {
        let c: [u8; 8] = counter.to_be_bytes(); // Das gibts???
        let combined: Vec<u8> = [seed.clone(), c.to_vec()].concat();
        hasher.update(combined);
        t.append(&mut hasher.finalize_reset().to_vec());
        counter += 1;
    }
    Some(t[..length].to_vec())
}


construct_uint! {
    pub struct U1024(16);
}
pub fn rsa(plaintext: U1024) -> U1024{
    let hex_str = "b84fb685c8cbd42f6297f3bfad9acd5db0c77418542f39aa09b9488b93a2338b70856e26c1c60d18d02536fa6d755224cd0496fa2fa4d26843ccf0269300602b1d4e63c579da71f006e1df075143b2e10f66a0d772f272a4d525171a1163837c277b6d845f1f20a4d3b13b826de2b978110fcc14a08ad07f8e0f91fca689876b";

    let bytes = hex::decode(hex_str).expect("Decoding failed");
    println!("{}", bytes.len());
    let mut padded_bytes = vec![0u8; 128 - bytes.len()];
    padded_bytes.extend_from_slice(&bytes);
    // let n = U1024::from("0x00b84fb685c8cbd42f6297f3bfad9acd5db0c77418542f39aa09b9488b93a2338b70856e26c1c60d18d02536fa6d755224cd0496fa2fa4d26843ccf0269300602b1d4e63c579da71f006e1df075143b2e10f66a0d772f272a4d525171a1163837c277b6d845f1f20a4d3b13b826de2b978110fcc14a08ad07f8e0f91fca689876b"); // via openssl
    let n = U1024::from_big_endian(&bytes);
    square_and_multiply(plaintext, E.into(), n)
}

construct_uint!{
    pub struct U256(4);
}

pub fn oaep_real(seed: [u8; 20], mut m: Vec<u8>) -> Vec<u8>{
    let mut hasher = Sha1::new();
    hasher.update("");
    let mut ha = hasher.finalize().to_vec();
    let mut text:Vec<u8> = vec![];
    text.append(&mut ha);
    for _ in 0..20-m.len()-ha.len(){
        text.push(0);
    }
    text.append(&mut m);
    if text.len() > 128{
        println!("Something smells fishy");
    }

    let mut out: Vec<u8> = vec![0];

    let mut outtext: Vec<u8> = mgf(&seed.to_vec(), seed.len()).expect("mgf failed!");
    for (i, x) in outtext.iter_mut().enumerate() {
        *x ^= text[i];
    }

    let mut outseed: Vec<u8> = mgf(&text, 20).expect("mgf failed!");
    for (i, x) in outseed.iter_mut().enumerate() {
        *x ^= seed[i];
    }

    out.append(&mut outseed);
    out.append(&mut outtext);
    out
}

pub fn oaep(m: String) -> Vec<u8>{
    let mut rng = rand::rng();
    let mut seed: [u8;20] = [0; 20];
    for i in &mut seed{
        *i = rng.random::<u8>();
    }

    u1024_to_vec_u8(
        rsa(vec_u8_to_u1024( oaep_real(seed, m.as_bytes().to_vec()) ))
    )
}
