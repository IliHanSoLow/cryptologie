// TODO: https://stackoverflow.com/questions/11184336/how-to-convert-from-byte-to-int-in-go-programming
// Dont use Strings as Number
package main

import (
	"crypto/md5"
	"encoding/binary"
	"fmt"
	"io"
	"os"
	// "sync"
)

var (
	hashes = make(map[uint64]string)
	// mu     sync.Mutex
)

func main() {
	fmt.Printf("%s\n", myHashFun(""))
	fmt.Printf("%s\n", myHashFun("Leeroy Jenkins"))

	// name := "Ilian Odenbach"
	name := "Christopher Felten"
	h := myHashFun(name)

	// mu.Lock()
	hashes[h] = name
	// mu.Unlock()

	fmt.Println(myHashFun(name))

	var i uint64
	for ; ; i++ {
		// go checkCollision(i, name)
		checkCollision(i, name)
	}
}

func myHashFun(input string) uint64 {
	h := md5.New()
	io.WriteString(h, input)
	// :5 to get the first 40 bit
	out := h.Sum(nil)[:5]
	return binary.BigEndian.Uint64(out)
}

func checkCollision(i uint64, name string) {
	input := fmt.Sprintf("%s%d", name, i)
	current_hash := myHashFun(input)

	// mu.Lock()
	// defer mu.Unlock()

	if x, ok := hashes[current_hash]; ok {
		fmt.Printf("Hash collision at %s with %s | %s,\nTook %d tries\n", current_hash, input, x, i)
		os.Exit(0)
	}
	hashes[current_hash] = input
}
