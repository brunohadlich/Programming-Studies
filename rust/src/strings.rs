pub fn run() {
    //Keyword mut won't work on the following line.
    let immutable_string = "This string is immutable.";
    //But works on this line.
    let mut mutable_string = String::from("This string is mutable.");
    println!("{}", immutable_string);
    println!("{}", mutable_string);
    println!("immutable_string length: {}", immutable_string.len());
    println!("mutable_string length: {}", mutable_string.len());
    mutable_string.push_str(" Nice isn't it?");
    println!("{}", mutable_string);
    println!("Capacity of mutable_string in bytes: {}", mutable_string.capacity());
    println!("Is mutable_string empty? {}", mutable_string.is_empty());
    println!("Does mutable_string contains 'string'? {}", mutable_string.contains("string"));
    let new_mutable_string = mutable_string.replace("This", "Such");
    println!("{}", new_mutable_string);
    for word in mutable_string.split_whitespace() {
        println!("{}", word);
    }

    let mut string_with_capacity_20 = String::with_capacity(20);
    println!("string_with_capacity_20 capacity: {}", string_with_capacity_20.capacity());
    string_with_capacity_20.push('a');
    string_with_capacity_20.push('b');
    println!("string_with_capacity_20 capacity: {}", string_with_capacity_20.capacity());
    assert_eq!(2, string_with_capacity_20.len());
}
