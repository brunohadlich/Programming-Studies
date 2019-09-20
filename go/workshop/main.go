package main

import "fmt"

func main() {
	fmt.Println("Hello World main.go")
	i := 10
	fmt.Println("Variável i: ", i)
	var arr = [...] int{1, 2, 3, 4, 5, 6, 7, 8, 9}
	arr2 := arr[2:]
	fmt.Println("arr2: ", arr2)
	fmt.Println("len arr: ", len(arr2))
	fmt.Println("cap rr: ", cap(arr2))
	arr3 := arr2[:5]
	fmt.Println("arr3: ", arr3)
	fmt.Println("len arr: ", len(arr3))
	fmt.Println("cap arr: ", cap(arr3))
	arr4 := arr3[:cap(arr3)]
	fmt.Println("arr4: ", arr4)
	fmt.Println("len arr: ", len(arr4))
	fmt.Println("cap arr: ", cap(arr4))
}
