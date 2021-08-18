pub fn run() {
    let a = 543;
    if a > 10 && a < 1000 {
        println!("value is higher than 10.");
    } else if a < 1000 || a > 900 {
        println!("value between 900 and 1000.");
    } else {
        println!("asd");
    }

    let b = if a > 10 { 20 } else { 5 };
    println!("{}", b);
}
