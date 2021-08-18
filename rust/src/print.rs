pub fn print() {
    println!("print from print.rs");
    println!("{} {} + {} = {}", "Hey", 4, 3, 7);
    println!("{0} are better than {1}, {0}!!!", "Potatoes", "lettuce");
    println!("{var1} are better than {var2}, {var1}!!!", var1="Potatoes", var2="lettuce");
    println!("{:?}", (13,true,"potatoe"));
}
