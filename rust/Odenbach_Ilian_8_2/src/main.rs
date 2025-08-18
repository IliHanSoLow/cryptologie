mod crypt;
use std::fs::File;
use std::io::{self, Write};

fn main() {
    let b:u8 = 0xFF;
    println!("{:#x}", b>>4);
    let a = crypt::mgf(&vec![1,2,3], 123).unwrap();
    println!("{a:?}");

    let cyphertext = crypt::oaep("Hello World".to_string());
    let ct: &[u8] = &cyphertext;
    let mut file = File::create("ciphertext bauer.bin").unwrap();
    file.write_all(ct).unwrap();
}
