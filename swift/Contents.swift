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

//PROTOCOL

protocol MyProtocol {
    var aString : String { get set }
    //Defined as mutating because otherwise the function foo of the implementor
    //of MyProtocol would not be allowed to change its properties.
    //Value types like Enumerations and Structures require the mutating
    //keyword to be able to change their own properties
    mutating func foo()
}

//PROTOCOL

//EXTENSION

extension MyProtocol {
    //making foo function of MyProtocol an optional
    func foo() {
        
    }
}

//EXTENSION

//PROTOCOL IMPLEMENTATION

class AClassImplementsMyProtocol: MyProtocol {
    var aString: String
    //foo is not implemented because it was made optional by the above extension
    init() {
        aString = "A simple string"
    }
}

//PROTOCOL IMPLEMENTATION

//MUTATING

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
    //if mutating was not present self.aString would not be allowed to be changed
    //methods of value types like Structures and Enumerations require the mutating
    //keyword to be able to change their properties
    mutating func foo() {
        self.teste = "Modified by foo function, " + returnSomething()
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

//MUTATING

//PROTOCOL and EXTENSION
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

//PROTOCOL and EXTENSION



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











//VARIABLES var

//can be changed during execution flow
var variable = 4
variable = 2

//Line below would not work because variables must be initialized
//var variable2

//VARIABLES var

//CONSTANTS let

let aConstant = 4

//let makes a constant, constants cannot be changed that is why line below is commented, it would cause a compilation error
//aConstant = 2

//Line below would not work because constants must be initialized
//let aConstant2

//CONSTANTS let

//OPTIONALS ?

//These statements are possible because optionals using ? symbol accept nil values
let a: String? = nil
var b2: String? = nil
b2 = "test"
b2 = nil

//OPTIONALS ?

//FORCE UNWRAPPING !

b2 = "foo bar"

//This would not work because b2 is an optional not a String and its value must be unwrapped with ! symbol
//var b3: String = b2

//This works because we are assigning the optinal b2 to the optional defined variable b5
//In this case it is like assigning a pointer to another pointer in C, so no issue at all

var b5: String? = b2

//symbol ! is used for unwrapping optionals, it is like dereference in C
var b3: String = b2!

b2 = nil
    
//In the example below b2 is forcedly unwrapped, basically it is saying to the compiler that b2 is not nil and can be
//safely unwrapped, in case it contains a nil the assignment will throw a fatal error, this is the situation here
//var b3: String = b2!

//Even if we make var b4 an optional like below, it will not work because the issue here is that
//optionals work like pointers in C and we are trying to dereference nil/null pointer/optional b2
//var b4: String? = b2!

//FORCE UNWRAPPING !

//IMPLICITLY UNWRAPPED OPTIONAL type!

//Implicitly unwrapped optionals are created with ! after the type instead of ?
//This means the variable is an optional that when used implicitly unwraps the value

var b9: String? = "testttttttt"//normal optional
print(b9)//prints Optional("testttttttt")

var b10: String! = "testttttttt"//implicitly unwrapped optional
print(b10!)//prints testttttttt

//IMPLICITLY UNWRAPPED OPTIONAL type!

//NIL COALESCING OPERATOR ??

//This kind of operation will check for the left side of ?? operand to identify if it is nil, in case it is, the right side is returned
//in case it is not nil, b2 will be unwrapped/dereferenced like with b2:
var b7: String = nil ?? "b2 is nil"
print(b7)

b2 = "now b2 is not nil and can be chosen by the nil coalescing operator ??"
b7 = b2 ?? "b2 is nil"
print(b7)

//In case variable is implicitly unwrapped optinal swift first checks if it in fact is NOT nil
//if it is nil the right side of the operand is returned, in case it is not nil variable is then
//dereferenced and returned
var b11: String!
print(b11 ?? "b11 is nil")

b11 = "b11 is not nil anymore"
print(b11 ?? "b11 is nil")

/* Equals to
 if b11 == nil {
    print("b11 is nil")
 } else {
    print(b11)
 }
 */

//NIL COALESCING OPERATOR ??

//OPTIONAL BINDING if let

var b8: String?

if let tmpB8 = b8 {
    print(tmpB8)
} else {
    print("b8 is nil")
}

//the line below would not work because tmpB8 only exists inside the if conditional
//print(tmpB8)

//Works with forced unrapped var too, just like happened with nil coalescing operator
var b12: String!

if let tmpB12 = b12 {
    print(tmpB12)
} else {
    print("b12 is nil")
}

//OPTIONAL BINDING if let

//OPTIONAL CHAINING if let, if let, if let

class Dog {
    var age: Int?
    var height: Int?
}

var bulldog: Dog?
//Using more than one optional binding, one inside the other constitutes an optional chaining
if let tmpBulldog = bulldog {
    if let tmpAge = tmpBulldog.age {
        print("bulldog's age: \(tmpAge)")
    }
}

//OPTIONAL CHAINING if let, if let, if let

//FAILABLE INITIALIZER init?

class AClass {

    var p1: Int
    //The use of ? after init means that this initializer may fail and return nil
    init?(p: Int) {
        if p < 0 {
            return nil
        } else {
            p1 = p
        }
    }
}

//FAILABLE INITIALIZER init?

//CONVENIENCE INITIALIZER convenience

class BClass {
    var p1, p2, p3, p4: Int

    init(p1: Int, p2: Int, p3: Int, p4: Int) {
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
        self.p4 = p4
    }
    //There can be a single initializer, in case you want to create another initializer with lets say
    //less parameters you can use the keyword convenience and then call the designated initializer
    convenience init(p3: Int) {
        self.init(p1: 0, p2: 0, p3: p3, p4: 0)
    }

    //Failable convenience intializer
    convenience init?(p2: Int) {
        if p2 < 0 {
            return nil
        }
        self.init(p1: 0, p2: p2, p3: 0, p4: 0)
    }
}

//CONVENIENCE INITIALIZER convenience

//FORCED TYPE CAST OPERATOR as!

class CClass {
    var p1, p2, p3: Int
    
    init(p1: Int, p2: Int, p3: Int) {
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
    }
}

class DClass: CClass {
    var p4, p5: Int
    
    init(p3: Int, p4: Int, p5: Int) {
        self.p4 = p4
        self.p5 = p5
        super.init(p1: 0, p2: 0, p3: p3)
    }
}

var dClass: DClass = DClass(p3: 1, p4: 2, p5: 3)
var cClass: CClass = dClass
//allows to force a downcast
var anotherDClass = cClass as! DClass

//FORCED TYPE CAST OPERATOR as!

//OPTIONAL TYPE CAST OPERATOR as?

class EClass {
    var p1, p2, p3: Int
    
    init(p1: Int, p2: Int, p3: Int) {
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
    }
}

class FClass: EClass {
    var p4, p5: Int
    
    init(p3: Int, p4: Int, p5: Int) {
        self.p4 = p4
        self.p5 = p5
        super.init(p1: 0, p2: 0, p3: p3)
    }
}

class GClass: EClass {
    
}

var fClass: FClass = FClass(p3: 1, p4: 2, p5: 3)
var eClass: EClass = fClass
//The line below would fail because it is trying to force a cast from FClass to GClass
//var gClass: GClass? = eClass as! GClass

//This line will try to cast from eClass to GClass, this operation will fail and then return nil because eClass holds an instance of FClass
var gClass: GClass? = eClass as? GClass
print("gClass is \(gClass)")

gClass = GClass(p1: 1, p2: 2, p3: 3)
eClass = gClass!
//Now the cast works because eClass is holding an instance of GClass
gClass = eClass as? GClass
print("Now gClass is \(gClass)")

//OPTIONAL TYPE CAST OPERATOR as?



//swift structures: class, enumeration, protocol, structure
