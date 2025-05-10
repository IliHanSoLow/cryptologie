// Zum ausführen: go test -v *.go
// Ich habe die print statements im code gelassen, da diese bei einem erfolgreichen Test nicht printen (ohne -v flag)
// und den Entwicklungsprozess etwas beschreiben.

package io2_2

import (
	"errors"
	"fmt"
	"math/bits"
	"reflect"
)

func Q(b uint32) uint32 {
	return b ^ bits.RotateLeft32(b, 17)
}

// Function for generating a new s
func new_s(s uint32, buf uint32) uint32 {
	fmt.Printf("s: 0x%x\n", s)
	return Q(s ^ buf)
}

// H() with default s
func hashing(m string) uint32 {
	var s uint32 = 0x524f464c
	return hashing_function(m, s)
}

// H() with variable s
func hashing_function(m string, s uint32) uint32 {
	println("Called with: ", m)
	var buf uint32 = 0
	//s_0
	for x, i := range m {
		// filling up buffer
		buf |= uint32(i) << (8 * (3 - (x % 4)))
		fmt.Printf("Char: %x\n", uint32(i))
		fmt.Printf("Buf: 0x%x, x: %d, x%%8: %d\n", buf, x, (x % 4))
		// generate new s if buffer is full
		if (x+1)%4 == 0 {
			s = new_s(s, buf)
			buf = 0
		}
	}

	// filling up if buffer is not full
	if len(m)%4 != 0 {
		buf |= 0xffffffff >> (8 * (len(m) % 4))
		s = new_s(s, buf)
	}
	fmt.Printf("Final Buf: 0x%x is type %s\n", buf, reflect.TypeOf(buf))
	fmt.Printf("Final s: 0x%x\n", s)
	println("----------------------------------")
	return Q(s)
}

// brute force s of the mic
func findSForQ(hash uint32) (uint32, error) {
	var i uint32 = 0
	// for ; i < 4294967295; i++ {
	for ; i < 0xFFFFFFFF; i++ {
		if i%1000000000 == 0 {
			println("Calculating")
		}
		if Q(i) == hash {
			fmt.Printf("Found i for Q(i) = hash with hash: 0x%x and i: 0x%x\n", hash, i)
			return i, nil
		}
	}
	return 0xDEADBEEF, errors.New("Could not found s to hash")
}

// length extension attack; explenation in code
// input: mic, original_message, append_message ; output: manupulated message, mic, error
func lea(mic uint32, original_message string, append_message string) (string, uint32, error) {
	// brute force the internal state of the hashing function to calculate the mic
	s, err := findSForQ(mic)
	if err != nil {
		fmt.Println("Error:", err)
		return "", 0, err
	}
	// calculate the mic of the message to append with the internal state as if the original message was before it
	out_mic := hashing_function(append_message, s)
	// Fill message up with FF until the buffer is full. This is neccesary because this happened at the mic calculation.
	if len(original_message)%4 != 0 {
		m := []byte(original_message)
		for len(m)%4 != 0 {
			m = append(m, 0xFF)
		}
		original_message = string(m)
	}
	return original_message + append_message, out_mic, nil
}
