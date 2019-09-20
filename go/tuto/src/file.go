//This is a single line comment

/*
This is a multiline comment.

go packages can have names that are different of the file name, this is an
example of a file called file.go that holds a package called main.

The command "go run" only executes files which hold package main, if a .go file
has a package of different name it won't be executed and will throw the error
"go run: cannot run non-main package". "go run" also needs the file that holds
the main package to have a main function otherwise it will throw the error:

runtime.main_main·f: relocation target main.main not defined
runtime.main_main·f: undefined: "main.main"

"go build" on the other hand will look at the files inside the current directory
and make a binary with the same name of the directory, in case you call
"go build file.go" it will create a binary called "file". "go build" also needs
a file with package main, in case it doesn't find it no error will be generated,
it won't create any binary and will terminate silently. In case "go build" finds
a package called main but no main function inside, it will throw the error:

runtime.main_main·f: relocation target main.main not defined
runtime.main_main·f: undefined: "main.main"

package names with more than a word should have such names concatenated like:
strutils instead of (str-utils, str_utils or strUtils).
*/
package main

//Imports can be made line by line or multiline
//The following multiline comment express a line by line import:
/*
import "fmt"
import "reflect"
*/

//multiline example
import (
	"fmt"
	"reflect"
	//package1 is the directory name, the line below imports all files
	//inside this directory, to access the functions, variables, constants
	//and resources in general use the package name instead of the
	//directory name, in this case the package name is file1 and is defined
	//on top of the files that are inside package1 folder
	"package1"
)

//multiple variables return
func f0() (int32, float32, int32, int64) {
	//go source code does not require semicolons at the end of statements
	return 4, 5, 6, 9
}

/*
Differently from most of the C like languages that define variables like:

type var_name;

go follows the pattern:

var var_name type

Here is an example of multiple named variables return
*/
func f1(p1 int32, p2 float32) (a int32, b float32, c int32, d int64) {
	a = p1
	b = p2
	//c will contain its zero value, that is 0
	d = 9
	return
}

//example of struct definition
type struct_f2 struct {
	v1, v3 int32
	v2 float32
	v4 int64
}

//function that receives struct by value
func f2(s struct_f2) {
	fmt.Printf("%d + %f = %d\n", s.v1, s.v2, s.v4)
}

//function that receives struct pointer
func f3(s *struct_f2) {
	fmt.Printf("%d + %f = %d\n", s.v1, s.v2, s.v4)
}

func f4(array ...int) {
	fmt.Println(array)
}

func types() {
	fmt.Println("Go has 17 basic built-in types, they are: string, bool, " +
		"int, uint, uintptr, int8, uint8, int16, uint16, int32, " +
		"uint32, int64, uint64, float32, float64, complex64 and " +
		"complex128. There are two alias, byte that is a alias for " +
		"uint8 and rune that is a alias for int32. Variables when " +
		"not initialized have default values, these default values " +
		"are called zero values and they are:\n")
	var a string
	var b bool
	var c int
	var d uint
	var e uintptr
	var f int8
	var g uint8
	var h int16
	var i uint16
	var j int32
	var k uint32
	var l int64
	var m uint64
	var n float32
	var o float64
	var p complex64
	var q complex128
	var r byte //realize that reflect.TypeOf returns uint8
	var s rune //realize that reflect.TypeOf returns int32
	fmt.Println(reflect.TypeOf(a), ":", a)
	fmt.Println(reflect.TypeOf(b), ":", b)
	fmt.Println(reflect.TypeOf(c), ":", c)
	fmt.Println(reflect.TypeOf(d), ":", d)
	fmt.Println(reflect.TypeOf(e), ":", e)
	fmt.Println(reflect.TypeOf(f), ":", f)
	fmt.Println(reflect.TypeOf(g), ":", g)
	fmt.Println(reflect.TypeOf(h), ":", h)
	fmt.Println(reflect.TypeOf(i), ":", i)
	fmt.Println(reflect.TypeOf(j), ":", j)
	fmt.Println(reflect.TypeOf(k), ":", k)
	fmt.Println(reflect.TypeOf(l), ":", l)
	fmt.Println(reflect.TypeOf(m), ":", m)
	fmt.Println(reflect.TypeOf(n), ":", n)
	fmt.Println(reflect.TypeOf(o), ":", o)
	fmt.Println(reflect.TypeOf(p), ":", p)
	fmt.Println(reflect.TypeOf(q), ":", q)
	fmt.Println(reflect.TypeOf(r), ":", r)
	fmt.Println(reflect.TypeOf(s), ":", s)
}

func arrays() {
	//array declaration, size is defined by elements on attribution
	var arr = [...] int{1, 2, 3, 4, 5, 6, 7, 8, 9}
	fmt.Println("var arr = [...] int{1, 2, 3, 4, 5, 6, 7, 8, 9};" , "type:", reflect.TypeOf(arr), ":", arr)
	//another array declaration
	arr2 := []int{1, 2, 3, 4, 5, 6, 7, 8, 9}
	fmt.Println("arr2 := []int{1, 2, 3, 4, 5, 6, 7, 8, 9};" , "type:", reflect.TypeOf(arr2), ":", arr2)
	//array declaration, size is defined and elements are initialized with
	//zero values
	var arr3 [9] int
	fmt.Println("var arr3 [9] int;" , "type:", reflect.TypeOf(arr3), ":", arr3)
}

func functions() {
	//short assignment example, in this case variable will have the type
	//defined as the same type of the values that are being received
	ret1, ret2, _, ret4 := f0()
	fmt.Printf("%d + %f = %d\n", ret1, ret2, ret4)

	//disconsidering third return with _
	ret1, ret2, _, ret4 = f1(4, 5)
	fmt.Printf("%d + %f = %d\n", ret1, ret2, ret4)
}

func structs() {
	//creates new struct and assigns values by order, in this case:
	//v1 = 4; v3 = 6; v2 = 5 and v4 = 9
	var_struct_f2 := struct_f2 {4, 6, 5, 9}
	f2(var_struct_f2)

	//creates new struct and assigns values by variables name
	var_struct_f2 = struct_f2 {v3: 6, v4: 9, v1: 4, v2: 5}
	f2(var_struct_f2)

	//when creating a struct variable the type after the variable name is optional
	//The line below does not use it
	var var_struct_f2_2 = struct_f2 {v3: 6, v4: 9, v1: 4, v2: 5}
	f2(var_struct_f2_2)

	//but this one does
	var var_struct_f2_3 struct_f2 = struct_f2 {v3: 6, v4: 9, v1: 4, v2: 5}
	f2(var_struct_f2_3)
}

func pointers() {
	var var_struct_f3 struct_f2 = struct_f2 {v3: 6, v4: 9, v1: 4, v2: 5}
	//example of passing struct as pointer
	f3(&var_struct_f3)

	//new allocates amount of memory equals to argument size and returns its address
	var var_struct_f3_2 *struct_f2 = new(struct_f2)
	var_struct_f3_2.v1 = 4
	var_struct_f3_2.v2 = 5
	var_struct_f3_2.v3 = 5
	var_struct_f3_2.v4 = 6
	f3(var_struct_f3_2)
}

func strings() {
	//string declaration
	var s1 string = "4 + 5 = 9"
	fmt.Printf("%s\n", s1);
	//Another string declaration
	var s2 = "4 + 5 = 9"
	fmt.Printf("%s\n", s2);
	//Yet another string declaration
	s3 := "4 + 5 = 9"
	fmt.Printf("%s\n", s3);
	fmt.Printf("%c\n", s3[2]);//Printing third character of s3
	//strings are immutable, the line below would generate the error:
	//cannot assign to s3[2]
	//s3[2] = '-'
}

func packages() {
	//Example of 
	fmt.Println(file1.ReturnString())
	//This line won't work because it is necessary to specify package name
	//fmt.Println(ReturnString())
}

//entry function of any go software
func main() {
	//Calling functions
	types()
	arrays()
	functions()
	structs()
	pointers()
	strings()
	packages()
}
