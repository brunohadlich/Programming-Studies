package main

func Pic(dx, dy int) [][]uint8 {
	var p [][]uint8
	for y := 0; y < dy; y++ {
		p = append(p, make([]uint8, dx))
		for x := 0; x < dx; x++ {
			//p[y][x] = uint8((x+y)/2)
			p[y][x] = uint8(x*y)
		}
	}
	return p
}

func main() {
	//pic.Show(Pic)
	Pic(50, 40)
}

