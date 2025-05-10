package io5_2_test

import (
	"fmt"
	"math/bits"
)

type Uint128 struct {
	High uint64
	Low  uint64
}

// 2^8 different values
func gen_s_box() [256]uint8 {
	fmt.Println("Hello World")
	s_box := [256]uint8{170}
	for i := 1; i < len(s_box); i++ {
		s_box[i] = uint8((37 * uint16(s_box[i-1]+9)) % 256)
	}
	return s_box
}

func schiffy_128_key(Uint128) {
	bits.RotateLeft64()
}
