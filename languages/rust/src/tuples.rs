pub fn run() {
    let a_tuple = ("a string", 23, true);
    println!("{:?}", a_tuple);
    let another_tuple: (&str, i8, bool) = ("a string", 23, true);
    println!("{:?}", another_tuple);
    let a_string = another_tuple.0;
    let a_number = another_tuple.1;
    let a_boolean = another_tuple.2;
    println!("{}, {}, {}", a_string, a_number, a_boolean);
}
