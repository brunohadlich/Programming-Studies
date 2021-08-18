pub fn run() {
    let a_array: [i32; 4] = [1,2,3,4];
    let a_array_2: [i32; 4];
    a_array_2 = [1,2,3,4];
    let mut a_array_3: [i32; 4];
    a_array_3 = [1,2,3,4];
    a_array_3 = [2,3,4,5];
    let another_array = [1,2,3,4];
    println!("{}", another_array[3]);
    a_array_3[3] = 6;
    println!("{}", a_array_3[3]);
    println!("Length: {}", a_array_3.len());
    println!("Size in bytes: {}", std::mem::size_of_val(&a_array_3));
    let slice: &[i32] = &a_array_2[0..2];
    println!("Slice 0..2: {:?}", slice)
}
