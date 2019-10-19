import UIKit

var str = "Hello, playground"
var constant = 1
print(constant)
constant = 3
print(constant)
print("var constant = " + String(constant))
print("var constant = \(constant)")
let multilineString = """
Exemplo de
string
  multiline
"""
print(multilineString)
var listExample = [1,2,3,4]
print(listExample)
listExample[1] = 5
print(listExample)
let listExample2 = [1,2,3,4]
//Line below would not work, let makes a constant array
//listExample2[1] = 5
print(listExample)
var dict = [
    "key1": "value1",
    "key2": "value2"
]

print(dict)
var emptyList = [String]()
for i in listExample {
    print(String(i))
}

for i in 0..<4 {
    print(i)
}

struct myStruct {
    var i : Int
    var y : Int

    func foo() {
        print("foo")
    }
}

func myFunc() -> (Int, Int) {
    return (7,9)
}

var m : myStruct? = myFunc() as? myStruct
print(m)
m?.foo()

func returnFunc() -> ((Int, Float) -> String) {
    func f(a : Int, b : Float) -> String {
        return "teste"
    }
    return f
}

print(returnFunc()(3,4))

func receivesFunc(_ f: ((Int, Float) -> String)) {
    print(f(7,9))
}

receivesFunc(returnFunc())

class MyClass {
    var i : Int = 0
    func foo() {
        print(self.i)
    }
    
    init(x i : Int) {
        self.i = i
    }
}

var myClass = MyClass(x: 8)
myClass.foo()

class MyClass2 : MyClass {
    var x: Int
    init(i : Int) {
        self.x = i
        self.k = 98
        super.init(x: i)
    }

    init(i : Int, f : Float) {
        self.x = i
        self.k = 98
        super.init(x: i)
        print("Passing by init(Int, Float)")
    }
    
    init(i : Int, f : Int) {
        self.x = i
        self.k = 98
        super.init(x: i)
        print("Passing by init(Int, Int)")
    }

    func bar() {
        print("Bar func of MyClass2")
    }

    override func foo() {
        print("Foo func() of MyClass2")
    }

    func foo(f: Int) {
        print("Foo func(Int) of MyClass2")
    }
    
    var z: Int {
        get {
            return 23
        }
        
        set {
            i = newValue
        }
    }
    
    func printI() {
        print(i)
    }

    //read-only value
    var y: Double {
        get {
            return 7
        }
    }

    var k: Int {
        //didSet and willSet are NOT executed when atribution happens inside init
        didSet {// run after variable has been set
            self.i = 56
        }
        willSet {// run before variable is set
            printI()
            self.i = 987
            printI()
        }
    }
}


var myClass2 = MyClass2(i: 3, f: 7)
myClass2.foo()
myClass2.foo(f: 8)
myClass2 = MyClass2(i: 3, f: 7.0)
//Line below would fail because
//myClass2.y = 4
myClass2.k = 34
print(myClass2.i)
print(myClass2.i)
print(myClass2.k)

func f() {
    //The line below would not work because a constant cannot be assigned with nil
    //let string: String = nil
    //This one works because of the optinal symbol ? that means the constant optionally will not hold any value
    let stringOptional: String? = nil
    let sizeStringOptional : Int = stringOptional?.count ?? 7
    let string: String = "teste"
    let sizeString : Int = string.count
    print(sizeStringOptional)
    print(sizeString)
}

f()

enum Sequence : Int {
    case first = 0
    case second, third, fourth, fifth
    case banana, potato
    
    func description() -> String {
        switch self {
        case .third:
            return "terceiro"
        case .banana:
            return "banana"
        default:
            return "something else \(self.rawValue)"
        }
    }
}
print(Sequence.first.rawValue)
print(Sequence.first)
print(Sequence.second)
print(Sequence.second.rawValue)
print(Sequence.third.description())
print(Sequence.banana.description())
print(Sequence.fourth.description())

if let banana = Sequence(rawValue: 5) {
    print(banana.description())
}
let potato = Sequence.potato
print(potato.description())

protocol MyProtocol {
    var aString : String { get set }
    mutating func foo()
}

class AClassImplementsMyProtocol: MyProtocol {
    var aString: String
    func foo() {
        aString = "Modified by foo function"
    }
    init() {
        aString = "A simple string"
    }
}

struct AStructImplementsMyProtocol: MyProtocol {
    var teste: String
    var aString: String {
        get {
            return self.teste
        }
        set {
            self.teste = newValue
        }
    }
    mutating func foo() {
        self.aString = "Modified by foo function, " + returnSomething()
    }
    func returnSomething() -> String {
        return "something"
    }
    init() {
        self.teste = "Initialized by init"
    }
}

var varImplementsMyProtocol : MyProtocol = AClassImplementsMyProtocol()
print(varImplementsMyProtocol.aString)
varImplementsMyProtocol.foo()
print(varImplementsMyProtocol.aString)

varImplementsMyProtocol = AStructImplementsMyProtocol()
print(varImplementsMyProtocol.aString)
varImplementsMyProtocol.foo()
print(varImplementsMyProtocol.aString)

protocol convert {
    func toFloat() -> Float
}
//Adds toFloat function to type Int through the protocol convert
extension Int: convert {
    func toFloat() -> Float {
        return Float(self)
    }
}

var b = 2
print(b.toFloat())

enum enumErrors: Error {
    case error1, error2, error3
}

func aFunctionThatThrowsError(value: Int) throws -> Int {
    if value < 0 {
        throw enumErrors.error1
    } else if value > 1000 {
        throw enumErrors.error2
    } else if value == 666 {
        throw enumErrors.error3
    }
    return 2 * value
}

func double(_ value: Int) -> Int {
    do {
        return try aFunctionThatThrowsError(value: value)
    } catch enumErrors.error1 {
        print("value must be greater or equals to 0")
    } catch enumErrors.error2 {
        print("value must be lower or equals to 1000")
    } catch {
        print("A random error")
    }
    return -1
}

print(double(-5))
print(double(1005))
print(double(666))
print(double(500))
let value: Int? = try? aFunctionThatThrowsError(value: -17)
print(value)

func deferExample() {
    var a: Int = 1
    print(a)
    defer {//defer is a block of code that will the last thing to be executed at the function,
           //in case there is return it will be executed right before return statement
        a = 5
        print(a)
    }
    a = 4
    print(a)
}
deferExample()

func copy<T>(element: T, n: Int) -> [T] {
    var copies : [T] = [T]()
    for _ in 0..<n {
        copies.append(element)
    }
    return copies
}

var copies : [String] = copy(element: "test", n: 5)
print(copies)

protocol prot_count {
    var count : Int { get }
}

struct struct_count1: prot_count {
    var count : Int {
        get {
            return 1
        }
    }
}

struct struct_count2: prot_count {
    var count : Int {
        get {
            return 2
        }
    }
}

struct struct_count3: prot_count {
    var count : Int {
        get {
            return 3
        }
    }
}

func sum_counts<T: prot_count, U: prot_count, I: prot_count>(_ s1: T, _ s2: U, _ s3: I) -> Int {
    return s1.count + s2.count + s3.count
}

let s1 = struct_count1()
let s2 = struct_count2()
let s3 = struct_count3()

let i = sum_counts(s1, s2, s3)
print(i)

//This fails because constants cannot be initialized with nil
//let a: String = nil

//This is possible because variable a is defined as a optional using ? symbol
let a: String? = nil
//The line below is not possible because let made a to be a constant and even though it was initialized with nil, it cannot be changed
//a = 2

//Again it won't work because variables also cannot be initialized with nil
//var b2: String = nil

//This works for the same reason that it worked with let
var b2: String? = nil
b2 = "test"
b2 = nil

//This would not work because b2 is an optional and its value must be unwrapped with ! symbol
//var b3: String = b2

//In the example below b2 is forcedly unwrapped, basically it is saying to the compiler that b2 does not contain a nil
//in case it contains a nil the assignment will throw a fatal error, this is the situation here
//var b3: String = b2!

//Even if we make b3 optional like below, it will not work because the issue here is that b2 works like a pointer in C
//and we are trying to dereference a nil/null pointer
//var b3: String? = b2!

//This works because we are assigning the optinal b2 to the optional defined variable b3
//In this case it is like assigning a pointer to another pointer in C, so no issue at all
var b3: String? = b2

//This would not work neither because we are trying to assign optional b2 to no optional b4, incompatible types
//var b4: String = b2

//This kind of operation will check for the left side of ?? operand to identify if it is nil, in case it is, the right side is returned
//in case it is not nil, b2 will be dereferenced like with b2! This is simples thank writing:
/*
var b4: String
if b2 == nil {
    b4 = "testeee"
} else {
    b4 = b2!
}
 */

var b4: String = b2 ?? "testeee"
