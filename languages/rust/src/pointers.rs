pub fn run() {
    let array1:[i32; 4] = [1,2,3,4];
    let array2 = array1;

    println!("{:?}", (array1, array2));

    let vec1 = vec![1, 2, 3];
    let vec2 = &vec1;

    println!("{:?}", (&vec1, vec2));
}
