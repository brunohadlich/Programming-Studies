package main

import "fmt"
import "strings"

type Vertex struct {
	Lat, Long float64
}

var m map[string]Vertex

func main() {
	//The line below must be uncommented because a map needs to be
	//initialized first, otherwise the variable m will be nil and
	//assigning new values will fail
	//m = make(map[string]Vertex)
	m["Bell Labs"] = Vertex{
		40.68433, -74.39967,
	}
	fmt.Println(m["Bell Labs"])
	fmt.Printf("%T", m["Bell Lab"])

	//It is also possible to instantiate and intialize the map at
	//once like below
	var mm = map[string]Vertex{
		"Bell Labs": Vertex{
			40.68433, -74.39967,
		},
		"Google": Vertex{
			37.42202, -122.08408,
		},
	}
	//As the type Vertex is described at map creation it is not
	//necessary to use it again when adding elements, this is
	//only possible at initialization stage
	var mmm = map[string]Vertex{
		"Bell Labs": {40.68433, -74.39967},
		"Google":    {37.42202, -122.08408},
	}
	fmt.Println(m)
	fmt.Println(mm)
	fmt.Println(mmm)
}

func main2() {
	m := make(map[string]int)

	m["Answer"] = 42
	fmt.Println("The value:", m["Answer"])

	m["Answer"] = 48
	fmt.Println("The value:", m["Answer"])

	delete(m, "Answer")
	fmt.Println("The value:", m["Answer"])

	v, ok := m["Answer"]
	fmt.Println("The value:", v, "Present?", ok)
}

func WordCount(s string) map[string]int {
	words := strings.Fields(s)
	var count map[string]int = make(map[string]int)
	for _, word := range words {
		count[word] = count[word] + 1
	}
	return count
}

func main3() {
	fmt.Println(WordCount("batata doce batata assada batata frita"))
}

