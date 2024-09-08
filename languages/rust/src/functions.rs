pub fn run() {
    greeting("Hello", "Trotsky");
    let v1 = 3;
    let v2 = 7;
    println!("v1 + v2 = {}", add(v1, v2));
    println!("v1 + v2 = {}", add2(v1, v2));

    //Closure
    let sum = |n1: i32, n2: i32| n1 + n2;
    println!("v1 + v2 = {}", sum(v1, v2));
}

fn greeting(greet: &str, name: &str) {
    println!("{} {}", greet, name);
}

fn add(v1: i32, v2: i32) -> i32 {
    return v1 + v2;
}
fn add2(v1: i32, v2: i32) -> i32 {
    v1 + v2
}
