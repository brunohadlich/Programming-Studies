package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	previous := 0
	last := 1
	fn := func () int {
		retorno := previous
		pivot := previous
		previous = last
		last = last + pivot
		return retorno
	}
	return fn
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}

