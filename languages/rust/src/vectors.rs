pub fn run() {
    let mut a_vector: Vec<i32> = vec![1,2,3,4];
    println!("a_vector: {:?}", a_vector);
    a_vector.push(5);
    println!("a_vector: {:?}", a_vector);
    a_vector.pop();
    println!("a_vector: {:?}", a_vector);
    println!("a_vector length: {}", a_vector.len());
    println!("a_vector capacity: {}", a_vector.capacity());
    println!("a_vector size in bytes: {}", std::mem::size_of_val(&a_vector));
    for x in a_vector {
        println!("Value: {}", x);
    }
    /*
    for x in a_vector.iter() {
        println!("Value: {}", x);
    }
    for x in a_vector.iter_mut() {
        *x += 4;
        println!("Value: {}", x);
    }
    */
}
