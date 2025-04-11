package main

import (
	"crypto/md5"
	"fmt"
	"io"
	"os"
	// "sync"
)

var (
	hashes = make(map[string]string)
	// mu     sync.Mutex
)

func main() {
	fmt.Printf("%s\n", myHashFun(""))
	fmt.Printf("%s\n", myHashFun("Leeroy Jenkins"))

	name := "Ilian Odenbach"
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

func myHashFun(input string) string {
	h := md5.New()
	io.WriteString(h, input)
	// :5 to get the first 40 bit
	out := h.Sum(nil)[:5]
	return fmt.Sprintf("%x", out)
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
