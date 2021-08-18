pub fn run() {
    //types: u8, i8, u16, i16, u32, i32, u64, i64, u128, i128
    //char
    //tuples
    //arrays
    println!("u8: min: {} - max: {}", std::u8::MIN, std::u8::MAX);
    println!("i8: min: {} - max: {}", std::i8::MIN, std::i8::MAX);
    println!("u16: min: {} - max: {}", std::u16::MIN, std::u16::MAX);
    println!("i16: min: {} - max: {}", std::i16::MIN, std::i16::MAX);
    println!("u32: min: {} - max: {}", std::u32::MIN, std::u32::MAX);
    println!("i32: min: {} - max: {}", std::i32::MIN, std::i32::MAX);
    println!("u64: min: {} - max: {}", std::u64::MIN, std::u64::MAX);
    println!("i64: min: {} - max: {}", std::i64::MIN, std::i64::MAX);
    println!("u128: min: {} - max: {}", std::u128::MIN, std::u128::MAX);
    println!("i128: min: {} - max: {}", std::i128::MIN, std::i128::MAX);
    println!("f32: min: {} - max: {}", std::f32::MIN, std::f32::MAX);
    println!("f64: min: {} - max: {}", std::f64::MIN, std::f64::MAX);
    let a_char: char = '\u{1F600}';
    let a_bool: bool = false;
    println!("{:?}", (a_char, a_bool));
}
