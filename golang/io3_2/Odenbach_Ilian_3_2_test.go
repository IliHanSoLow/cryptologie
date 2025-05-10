// To execute the code, run go test -v *.go
package io2_2

import (
	"fmt"
	"testing"
)

// This are the test-cases I used for development
type TestsHashing_t struct {
	in     string
	should uint32
}

var hashingTests = []TestsHashing_t{
	{in: "", should: 0xded7e2d2},
	{in: "A", should: 0x5d725f7f},
	{in: "AB", should: 0x5f3b5f7f},
	{in: "ABC", should: 0x5f39137f},
	{in: "ABCD", should: 0x5f391128},
	{in: "ABCDE", should: 0x2f69af58},
}

type TestsLea_t struct {
	mic uint32
	// original_message
	om string
	// append_message
	am string
	// should mic
	smic uint32
}

var leaTests = []TestsLea_t{
	// {mic: 0x632e4e5c, om: "abcd", am: "ef", smic: 0x0f6b8802},
	// {mic: 0x632e4e5c, om: "abcd", am: "efghijk", smic: 0x2638a819},
	// {mic: 0x0f6b8802, om: "abcdef", am: "ghijk", smic: 0},
	// {mic: 0x2638a819, om: "abcdefghijk", am: "foobar", smic: 0},
	// {mic: 0x782a826e, om: "foobar", am: "barfoo", smic: 0},
	// {mic: 0x885dc316, om: "barfoo", am: "foobar", smic: 0},
	// {mic: 0x632e4e5c, om: "abcd", am: "lucacs", smic: 0},
	// THIS IS THE LENGTH EXTENSION ATTACK I WANT TO BE GRATED
	{mic: 0x632e4e5c, om: "abcd", am: "iocs2", smic: 0},
}

// Test the different Qs in the task
func TestQ1(t *testing.T) {
	var in uint32 = 0x524f464c
	var should uint32 = 0xded7e2d2
	if output := Q(in); output != should {
		t.Errorf("With INPUT: %x is OUTPUT %x , not the EXPECTED: %x", in, output, should)
	}
}

func TestQ2(t *testing.T) {
	var in uint32 = 0x524f464c
	var should uint32 = 0x1b725f7d
	if output := Q(Q(in)); output != should {
		t.Errorf("With INPUT: %x is OUTPUT %x , not the EXPECTED: %x", in, output, should)
	}
}

func TestQ3(t *testing.T) {
	var in uint32 = 0x524f464c
	var should uint32 = 0xa5886999
	if output := Q(Q(Q(in))); output != should {
		t.Errorf("With INPUT: %x is OUTPUT %x , not the EXPECTED: %x", in, output, should)
	}
}

// Test the different H() 's in the task
func TestHashing(t *testing.T) {
	for _, test := range hashingTests {
		if output := hashing(test.in); output != test.should {
			t.Errorf("With INPUT: %q is OUTPUT %x , not the EXPECTED: %x", test.in, output, test.should)
		}
	}
}

// A verry somple test to check, if the findQ() works
func TestFindQ(t *testing.T) {
	var hash uint32 = 0x632e4e5c
	s, err := findSForQ(hash)
	if err != nil {
		t.Errorf("With Err:%s for hash: 0x%x", err, hash)
	}
	if Q(s) != hash {
		t.Errorf("With hash: 0x%x, is not Q(%x)", hash, s)
	}
}

// Test the length extension attack and print out the final message, and the final MIC
func TestLea(t *testing.T) {
	for _, test := range leaTests {
		outm, outmic, err := lea(test.mic, test.om, test.am)
		if err != nil {
			t.Errorf("With Err:%s for input: (0x%x, %q, %q)", err, test.mic, test.om, test.am)
		}
		fmt.Printf("outmsg: %q, outmic: 0x%x\n", outm, outmic)
		if test.smic != 0 {
			if outmic != test.smic {
				t.Errorf("With INPUT: (0x%x, %q, %q) is OUTPUT mic: %x , not the EXPECTED: mic: %x",
					test.mic, test.om, test.am, outmic, test.smic)
			}
		}

		fmt.Printf("----------------------------------")
	}
}
