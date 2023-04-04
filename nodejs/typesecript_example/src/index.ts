console.log("Union type")

function print_union_parameter(value: string | number) {
	console.log(value)
}

print_union_parameter(23)
print_union_parameter("abc")

console.log("Alias type")

type alias_type_example = string | { bar: number }

function print_alias_type(value: alias_type_example) {
	console.log(value)
}

print_alias_type("xpto")
print_alias_type({bar: 2})

console.log("Tuples")

type myTuple = [string, number]

const aasdqwe: myTuple = ['asd', 23];

function return_tuple(): myTuple {
	return aasdqwe
}

console.log(return_tuple())

console.log("Narrowing")

function print_modified_value(value: number | string | boolean) {
	// Following line would error because at this point value can be a number
	// console.log(value.toUpperCase())
	if (typeof value === 'string')
		// This line won't fail because at this point the type checker knows that value is a string
		console.log(value.toUpperCase())
	else if (typeof value === 'number')
		console.log(value + 1)
	else
		console.log(!value)
}

print_modified_value('abc')
print_modified_value('2')
print_modified_value(2)
print_modified_value(true)

console.log("Literal types")

let literal_type_var: 123 | 2
// This would error because literal_type_var is of type 123 | 2 and can only receive the values 123 and 2
// literal_type_var = 3
literal_type_var = 123
console.log(literal_type_var)
literal_type_var = 2
console.log(literal_type_var)

console.log("Types with same structure but different names")

type foo = {
	bar: number
	baz: string
}

type foo2 = {
	baz: string
	bar: number
}

function print_different_name_same_type(value: foo) {
	console.log(value)
}

let argument: foo2 = {bar: 3, baz: "abc"}

print_different_name_same_type(argument)