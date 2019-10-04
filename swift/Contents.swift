//import UIKit

func stringInterpolation() {
    let constant: Int = 87
    print("var constant = \(constant)")
}

func multilineString() {
    let multilineString = """
        Exemplo de
    string
          multiline
    

    """
    print(multilineString)
    print("As you can see print takes into account the black spaces at the end of a multiline string")
}

func preLoadedArrays() {
    var listExample = [1,2,3,4]
    print(listExample)
    listExample[1] = 5
    print(listExample)
    listExample.append(5)
    print(listExample)
    listExample.append(6)
    print(listExample)
    listExample.remove(at: 3)
    print(listExample)
    let listExample2 = [1,2,3,4]
    //Line below would not work, let makes a constant array
    //listExample2[1] = 5
}

func emptyinitializedArrays() {
    var l:[String] = [String]()
    
    l.append(String(1))
    l.append(String(3))
    l.append(String(5))
    
    print(l)
}

func arrays() {
    preLoadedArrays()
    emptyinitializedArrays()
}

func dictionaries() {
    var dict = [
        "key1": "value1",
        "key2": "value2"
    ]
    print(dict)
    dict["key1"] = "key1 has changed"
    print(dict)
    dict["key3"] = "now the dictionary has one more value"
    print(dict)
    dict.removeValue(forKey: "key2")
    print(dict)
    dict.removeAll()
    print(dict)
    
    var dict2: [Int: String] = [
        7: "seven",
        4: "four",
        -3: "minus three"
    ]
    print(dict2)
    dict2.removeValue(forKey: -3)
    print(dict2)
    dict2.removeAll()
    print(dict2)
}

func multipleReturns() {
    func foo() -> (Int, Float, Int, String) {
        return (2, 3.14, 7, "a string")
    }
    let result = foo()
    
    print(result)
}

func structs() {
    struct MyStruct {
        var i : Int
        var y : Int

        //swift struct's have synthesized initializers, that means we are not obligated
        //to define an initializers but in case we do it must set all properties values

        func foo() {
            print("foo")
        }
    }
    let kl: MyStruct = MyStruct(i: 9, y: 4)
    print(kl)
}

func optionalCall() {
    struct MyStruct {
        var i : Int
        var y : Int
        
        func foo() {
            print("foo")
        }
    }
    var kl: MyStruct? = MyStruct(i: 9, y: 4)
    print(kl)
    kl?.foo()//Prints because kl holds an object
    kl = nil
    kl?.foo()//Does not call foo because kl is nil
}

func returnFunction() {
    func returnFunc() -> ((Int, Float) -> (String, Int)) {
        func f(a : Int, b : Float) -> (String, Int) {
            return ("teste", a)
        }
        return f
    }

    print(returnFunc()(3,4))

    func receivesFunc(_ f: ((Int, Float) -> (String, Int))) {
        print(f(7,9))
    }

    receivesFunc(returnFunc())
}

func classes() {
    class MyClass {
        var i : Int
        func foo() {
            print(self.i)
        }

        //The only case in which init is not necessary is when
        //all properties are defined with default values

        init(x l: Int) {
            self.i = l
        }
    }
    
    let c = MyClass(x: 8)
    c.foo()
}

func classSynthesizedInitializer() {
    class ClassWithSynthesizedInitializer {
        var i : Int = 8//default value on property definition
        func foo() {
            print(self.i)
        }
        
        //The only case in which init is not necessary is when
        //all properties are defined with default values
    }

    let c2 = ClassWithSynthesizedInitializer()
    c2.foo()
}

func multipleInits() {
    class MyClass {
        var i : Int = 7
        var y: Int
        
        init(i : Int) {
            self.i = 98
            self.y = i
            print("Passing by init(Int)")
        }
        
        init(i : Int, f : Float) {
            self.y = Int(f)
            print("Passing by init(Int, Float)")
        }
        
        init(i : Int, i2 : Int) {
            self.i = i
            self.y = i2
            print("Passing by init(Int, Int)")
        }
    }
    print(MyClass(i: 7))
    print(MyClass(i: 4, f: 4.34))
    print(MyClass(i: 2, i2: 9))
}

func classInheritance() {
    class MyClass {
        var i : Int = 0
        func foo() {
            print("foo: \(self.i)")
        }
        
        init(x l: Int) {
            self.i = l
        }
    }
    
    class MyClass2: MyClass {
        func bar() {
            print("bar")
        }
    }
    
    let m: MyClass = MyClass2(x: 8)
    m.foo()
    //Line below would not work because although MyClass2 instance was assigned
    //to m, the type of m is MyClass and it does not have such function
    //m.bar()
    let m2: MyClass2 = MyClass2(x: 5)
    m2.foo()
    m2.bar()
}

func overrideFunction() {
    class MyClass {
        var i : Int = 0
        func foo() {
            print("foo: \(self.i)")
        }
        
        init(x l: Int) {
            self.i = l
        }
    }
    class MyClass2 : MyClass {
        override func foo() {
            print("override version of foo func() in MyClass2")
        }
        
        func foo(f: Int) {
            print("Foo func(Int) of MyClass2")
        }
    }
    
    
    let myClass2: MyClass2 = MyClass2(x: 3)
    myClass2.foo()
    myClass2.foo(f: 8)
    let myClass: MyClass = myClass2
    //Although myClass is of type MyClass, it is holding an instance of MyClass2 and so the function
    //foo prints "override version of foo func() in MyClass2" instead of "foo: \(self.i)"
    myClass.foo()
}

func storedProperties() {
    //Stored properties are properties that occupy space at memory to
    //store their own values, below are examples of stored values
    class MyClass {
        var i : Int = 0
        
        init(x l: Int) {
            self.i = l
        }
    }
    class MyClass2 : MyClass {
        var z: Int = 3
        let y: Double = 9
    }
    
    let myClass2: MyClass2 = MyClass2(x: 317)

    struct MyStruct {
        var v1: String
        let v2: Int = 9
        var v3: Double
    }
    var m = MyStruct(v1: "a string", v3: 7.666667)
    m.v3 = 4.5
    var mm = m
    //The line below would throw an error because mm was defined as a constant with let
    //struct's are value types so mm is not a reference to m but an exact copy of their
    //values and that is why we cannot change mm values
    mm.v3 = 7
}

func lazyStoredProperties() {
    //Lazy variables are only instantiated at the first time they are referenced
    class MyClass {
        let i = 8
    }
    class MyClass2 {
        lazy var v1: MyClass = MyClass()
    }
    let m: MyClass2 = MyClass2()
    //m has been instantiated but its property v1 has not been initialized yet
    print(m.v1.i)//Now that v1 was referenced it is in fact initialized with MyClass()
}

func computedProperties() {
    class MyClass {
        var i : Int = 0
        
        init(x l: Int) {
            self.i = l
        }
    }
    class MyClass2 : MyClass {
        var z: Int {
            get {
                //The line below would generate a recursion because the reference to self.z
                //would call get that would reference self.z that would call get and so on
                //return self.z
                i+=1
                return i
            }
            
            //optional setter
            //it is not possible to have a setter without a getter
            set {
                i = newValue//newValue is the default name of the set parameter, this is known as shorthand setter
            }
        }

        var l: Int {
            get {
                return 4
            }
            set(aParameter) {
                i = aParameter
            }
        }
        
        var g: Int {
            return 13//Example of read-only computed property without get keyword
        }
        
        var k: Int = 9 {
            //didSet and willSet are NOT executed when atribution happens inside init
            didSet {// run after variable has been set
                self.i = 56
                //Line below would throw error because y is a get-only property
                //self.y = 9.3
                
                self.z = 87
            }
            willSet {// run before variable is set
                print(i)
                self.i = 987
                print(i)
            }
        }
    }

    let myClass2: MyClass2 = MyClass2(x: 317)
    print(myClass2.z)
    print(myClass2.l)
    print(myClass2.g)
    print(myClass2.i)
    print(myClass2.k)
}

func propertyOberservers() {
    class MyClass {
        var i : Int = 0
        
        init(x l: Int) {
            self.i = l
        }
    }
    class MyClass2 : MyClass {
        var k: Int = 9 {
            //didSet and willSet are NOT executed when atribution happens inside init
            didSet {// run after variable has been set
                self.i -= 1
                self.i -= 1
                print(i)
            }
            willSet {// run before variable is set
                self.i += 1
                print(i)
            }
        }
    }
    
    let myClass2: MyClass2 = MyClass2(x: 317)
    myClass2.k += 1
    myClass2.k += 1
    myClass2.k += 1
    myClass2.k += 1
    myClass2.k += 1
}

func typeProperties() {
    class MyClass {
        static var i: Int = 8
    }
    print(MyClass.i)
    MyClass.i = 3
    print(MyClass.i)
    MyClass.i = 7
    print(MyClass.i)
}

func enumeration() {
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
}

//Protocols may not be defined inside other structures,
//that is why this protocol is defined globally
protocol MyProtocol {
    //Protocols can only specify computed properties
    var aString : String { get set }
    //Defined as mutating because otherwise the function foo of the implementor
    //of MyProtocol would not be allowed to change its properties.
    //Value types like Enumerations and Structures require the mutating
    //keyword to be able to change their own properties
    mutating func foo()
}
func protocols() {
    class MyClass: MyProtocol {
        var myClassString: String = "Initial value"
        var aString: String {
            get {
                return "\(myClassString), value modified by setter required by MyProtocol"
            }
            set {
                myClassString = newValue
            }
        }
        func foo() {
            print("foo")
        }
    }
    
    MyClass().foo()
}

protocol convert {
    func toFloat() -> Float
}

//Adds toFloat function to type Int through the protocol convert
extension Int: convert {
    func toFloat() -> Float {
        return Float(self)
    }
}

//This is an example of a trick to make a protocol function not obligatory
//With the code below the class, struct or enumeration that adopts this
//protocol will not be forced to implement the foo function
extension MyProtocol {
    //making foo function of MyProtocol an optional
    func foo() {
        
    }
}
func extensions() {
    //extensions are a way of adding new features to classes,
    //structs, enumerations and protocols previouly defined
    //extensions can only be defined at file scope, that is
    //why it is defined above

    var b = 2
    print(b.toFloat())//Int was extended with function toFloat

    //Example of a class that adopts MyProtocol and does not implement the foo function
    class AClassImplementsMyProtocol: MyProtocol {
        var aString: String
        //foo is not implemented because it was made optional by the above extension
        init() {
            aString = "A simple string"
        }
    }
    
}

func mutatingStruct() {
    struct AStructImplementsMyProtocol: MyProtocol {
        var i: Int
        var aString: String {
            get {
                return "\(i), computed property"
            }
            set {
                
            }
        }
        //if mutating was not present self.aString would not be allowed to be changed,
        //methods of value types like Structures and Enumerations require the mutating
        //keyword to be able to change their properties
        mutating func foo() {
            i += 1
        }
        init() {
            self.i = 0
        }
    }

    var varImplementsMyProtocol: MyProtocol = AStructImplementsMyProtocol()
    print(varImplementsMyProtocol.aString)
    varImplementsMyProtocol.foo()
    print(varImplementsMyProtocol.aString)
    varImplementsMyProtocol.foo()
    print(varImplementsMyProtocol.aString)
}

func errorHandling() {
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
    //try? will return nil if the right statement throws an error
    //otherwise the result of the right statement will be returned
    var value: Int? = try? aFunctionThatThrowsError(value: -17)
    print(value)
    if let tmpValue = try? aFunctionThatThrowsError(value: 17) {
        print(tmpValue)
    } else {
        print("nil")
    }
}

func deferExample() {
    func bar() -> Int {
        var a: Int = 1
        print(a)
        defer {//defer is a block of code that will be the last thing to be executed at the function,
               //in case there is return it will be executed right before return statement
            a = 5
            print(a)
        }
        a = 4
        print(a)
        return 7
    }

    print(bar())
}

func generics() {
    func copy<T>(element: T, n: Int) -> [T] {
        var copies : [T] = [T]()
        for _ in 0..<n {
            copies.append(element)
        }
        return copies
    }
    
    var copies : [String] = copy(element: "test", n: 5)
    print(copies)
}

protocol prot_count {
    var count : Int { get }
}
func generics_inheritance() {
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
    //Although struct_count1, 2 and 3 inherit from prot_count, in this case there must be created
    //three kind of generics, T, U and I. This happens because swift understands that the type that
    //will be passed as argument has the type that will represent such generic, so if I pass an
    //instance of struct_count1 to s1, it would assume that T only supports struct_count1 instances
    //and that way s2 and s3 would not accept struct_count2 and 3 if T was used as the generics for
    //these parameters too. That is why it was created three generics, so the instance that is passed
    //as argument to s1 will not affect the allowed types for s2 and s3
    func sum_counts<T: prot_count, U: prot_count, I: prot_count>(_ s1: T, _ s2: U, _ s3: I) -> Int {
        return s1.count + s2.count + s3.count
    }

    let s1 = struct_count1()
    let s2 = struct_count2()
    let s3 = struct_count3()

    let i = sum_counts(s1, s2, s3)
    print(i)
}

func variables() {//var
    //can be changed during execution flow
    var variable = 4
    variable = 2
    
    //Line below would not work because variables must be initialized
    //var variable2
}

func constants() {//let
    let aConstant = 4
    
    //let makes a constant, constants cannot be changed that is why line below is commented, it would cause a compilation error
    //aConstant = 2
    
    //Line below would not work because constants must be initialized
    //let aConstant2
}

func optionals() {//?
    //These statements are possible because optionals using ? symbol accept nil values
    let a: String? = nil
    var b2: String? = nil
    b2 = "test"
    b2 = nil
}

func forceUnwrapping() {//!
    var b2: String? = "foo bar"
    
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
}

func implicitlyUnwrappedOptional() {// var aVariable: type!
    //Implicitly unwrapped optionals are created with ! after the type instead of ?
    //This means the variable is an optional that when used implicitly unwraps the value
    
    var b9: String? = "testttttttt"//normal optional
    print(b9)//prints Optional("testttttttt")
    
    var b10: String! = "testttttttt"//implicitly unwrapped optional
    print(b10!)//prints testttttttt
}

func nilCoalescingOperator() {//??
    //This kind of operation will check for the left side of ?? operand to identify if it is nil, in case it is, the right side is returned
    //in case it is not nil, b2 will be unwrapped/dereferenced like with b2:
    var b7: String = nil ?? "b2 is nil"
    print(b7)
    
    let b2 = "now b2 is not nil and can be chosen by the nil coalescing operator ??"
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
}

func optionalBinding() {//if let
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
}

func optionalChaining() {//if let, if let, if let
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
}

func failableInitializer() {//init?
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
}

func convenienceInitializer() {//convenience
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
}

func forcedTypeCastOperator() {//as!
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
    
    let dClass: DClass = DClass(p3: 1, p4: 2, p5: 3)
    let cClass: CClass = dClass
    //allows to force a downcast
    var _ = cClass as! DClass
}

func optionalTypeCastOperator() {//as?
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
}

func closures() {
    let names = ["Bob", "Jake", "Biroliro", "Arnold"]
    //the by argument is a closure expression
    let sortedNames = names.sorted(by: {(s1: String, s2: String) -> Bool in
        return s1 < s2
    })
    print(sortedNames)
}

func shorthandClosure() {
    let names = ["Bob", "Jake", "Biroliro", "Arnold"]
    //Shorthand closures allow the development of inline closures, in such case the arguments are accessed
    //by an index like $0, $1, $2... and their type are infered based on the expected defined type
    //In the example below swift compiler knows that names is an array of Strings and so the comparison
    //function for sorted function requires two strings, that way it infers that $0 and $1 are Strings
    print(names.sorted(by: {$0 < $1}))

    //shorhand closures work with multiple statements too
    print(names.sorted(by: {
        if $1 == "Bob" {
            return true
        }
        
        return $0 < $1
        
    }))

    //It is possible to simply pass the operator that will be applied to the parameters
    print(names.sorted(by: <))
}

func closureGenerator() {
    func makeIncrementer(forIncrement amount: Int) -> () -> Int {
        var runningTotal = 0
        func incrementer() -> Int {
            runningTotal += amount
            return runningTotal
        }
        return incrementer
    }

    let sum4 = makeIncrementer(forIncrement: 4)
    print(sum4())
    print(sum4())
    print(sum4())
    let sum7 = makeIncrementer(forIncrement: 7)
    print(sum7())
    print(sum7())

    print(sum4())
    print(sum7())
}

func subscripts() {
    struct TimesTable {
        let multiplier: Int
        subscript(index: Int) -> Int {
            return multiplier * index
        }
    }
    let threeTimesTable = TimesTable(multiplier: 3)
    print("6 times three is \(threeTimesTable[6])")
    print("417 times three is \(threeTimesTable[417])")
    print("23 times three is \(threeTimesTable[23])")
    print("-8 times three is \(threeTimesTable[-8])")
    
    class MyClass {
        var i: Float = 0
        //This example uses two parameters but it is completely possible to use more than two,
        //it could be subscript(f1: Float, f2: Int, f3: String, f4: Int)
        subscript(f1: Float, f2: Int) -> Float {
            get {
                return Float(i) * f1 + Float(f2) - i
            }
            
            set(increment) {
                i += f1 * Float(f2) + increment
            }
        }
    }
    
    let m = MyClass()
    print(m.i)
    m[5.4, 8] = 9
    print(m.i)
    print(m[5.4, 8])
    m[3.1, 23] = 2
    print(m.i)
    print(m[3.1, 23])
}

func deinitExample() {
    //deinit is executed when instance is not usable, accessible anymore
    class MyClass {
        init() {
            print("init")
        }
        deinit {
            print("deinit")
        }
    }

    let _ = MyClass()
}

func guardExample() {
    //guard is used when it is necessary to assure that a variable/constant is not nil
    //and in case it is nil the execution flow must stop. That is why inside the else
    //part of a guard statement you use return or throw, to guarantee there will be no
    //execution after the statement
    var v: Int? = 9
    
    guard v != nil else {
        print("var v is nil")
        return
    }
    v = nil
    guard let tmpV = v else {
        print("v is nil")
        return
    }
    print("v is not nil. v = \(tmpV)")
}

func finalClasses() {
    //Final classes cannot be subclassed
    //Final prevents other classes from inherit from the final class
    final class AFinalClass {
        
    }
    //If uncommented the lines below will present a compilation error
    //class SubClass: AFinalClass {
    //
    //}
}

protocol Protocol: class {//Protocol can only be adopted by classes
    func foo()
}
class MyClass: Protocol {
    func foo() {
        print("foo from class C")
    }
}

MyClass().foo()
func classOnlyProtocol() {
    class MyClass: Protocol {
        func foo() {
            print("foo from class C")
        }
    }
    
    MyClass().foo()
    //Lines below would not run because Protocol can
    //only be adopted by classes and not structs
    /*
    struct S: Protocol {
        func foo() {
            print("foo from struct S")
        }
    }
    
    S().foo()
    */
}

protocol ProtocolRequired {
    init(p1: Int, p2: Double)
    func foo()
}
func requiredExample() {
    class MyClass: ProtocolRequired {
        //This required keyword is necessary because init was defined at protocol
        //only initializers defined at protocols need required keyword
        required init(p1: Int, p2: Double) {
            print("MyClass.init(\(p1), \(p2))")
        }
        //In foo function it is not necessary to use required
        //keyword because it is not an initializer
        func foo() { }
    }
    let m = MyClass(p1: 3, p2: 5.4)
}

func structsCannotBeChanged() {
    struct AStruct {
        var a: Int
        var b: Double
    }
    
    class AClass{
        var a: Int
        var b: Double
        init(a: Int, b: Double) {
            self.a = a
            self.b = b
        }
    }
    
    //The following code won't compile because parameters of type struct and enum
    //cannot be modified, they are value types and value types cannot be changed
    //by other
    /*
     func modifyStruct(s: AStruct) {
     s.a = 23
     s.b = 21.4
     }
     */
    
    //On the other hand classes are reference types
    //and can be changed when passed as parameter
    func modifyClass(s: AClass) {
        s.a = 23
        s.b = 21.4
    }
    var c = AClass(a: 6, b: 7.5)
    print(c)
    modifyClass(s: c)
    print(c)
}

print("variables:")
variables()
print("constants:")
constants()
print("arrays:")
arrays()
print("dictionaries:")
dictionaries()
print("structs:")
structs()
print("multipleReturns:")
multipleReturns()
print("stringInterpolation:")
stringInterpolation()
print("multilineString:")
multilineString()
print("optionals:")
optionals()
print("optionalCall:")
optionalCall()
print("forceUnwrapping:")
forceUnwrapping()
print("implicitlyUnwrappedOptional:")
implicitlyUnwrappedOptional()
print("nilCoalescingOperator:")
nilCoalescingOperator()
print("optionalBinding:")
optionalBinding()
print("optionalChaining:")
optionalChaining()
print("failableInitializer:")
failableInitializer()
print("convenienceInitializer:")
convenienceInitializer()
print("forcedTypeCastOperator:")
forcedTypeCastOperator()
print("optionalTypeCastOperator:")
optionalTypeCastOperator()
print("returnFunction:")
returnFunction()
print("classes:")
classes()
print("classSynthesizedInitializer:")
classSynthesizedInitializer()
print("multipleInits:")
multipleInits()
print("storedProperties:")
storedProperties()
print("computedProperties:")
computedProperties()
print("propertyOberservers:")
propertyOberservers()
print("typeProperties:")
typeProperties()
print("lazyStoredProperties:")
lazyStoredProperties()
print("classInheritance:")
classInheritance()
print("overrideFunction:")
overrideFunction()
print("enumeration:")
enumeration()
print("protocols:")
protocols()
print("extensions:")
extensions()
print("mutatingStruct:")
mutatingStruct()
print("errorHandling:")
errorHandling()
print("deferExample:")
deferExample()
print("generics:")
generics()
print("generics_inheritance:")
generics_inheritance()
print("closures:")
closures()
print("shorthandClosures:")
shorthandClosure()
print("closureGenerator:")
closureGenerator()
print("subscripts:")
subscripts()
print("deinitExample:")
deinitExample()
print("guardExample:")
guardExample()
print("finalClasses:")
finalClasses()
print("classOnlyProtocol:")
classOnlyProtocol()
print("requiredExample:")
requiredExample()
print("structsCannotBeChanged:")
structsCannotBeChanged()
//swift structures: class, enum and struct
//protocols and extensions can only be defined at file scope
