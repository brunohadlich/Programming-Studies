pub fn run() {
    let name = "Zéca";
    let mut age = 23;
    println!("{} is {} years old.", name, age);
    age = 24;
    println!("Now {} is {} years old.", name, age);
    const PI: f32 = 3.14;
    println!("Pi = {}", PI);
    let (var1, var2, var3) = ("Trotsky", 21, false);
    println!("{}, {}, {}", var1, var2, var3);
}
