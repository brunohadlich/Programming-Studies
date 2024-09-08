pub fn run() {
    let mut count = 0;

    //infinite loop
    loop {
        println!("count is: {}", count);
        count += 1;
        if count == 10 { break };
    }

    count = 0;

    while count <= 100 {
        let divisible_by_3 = count % 3 == 0;
        let divisible_by_5 = count % 5 == 0;
        if divisible_by_3 && divisible_by_5 {
            println!("fizz buzz");
        } else if divisible_by_3 {
            println!("fizz");
        } else if divisible_by_5 {
            println!("buzz");
        } else {
            println!("{}", count);
        }
        count += 1;
    }

    for count in 0..100 {
        let divisible_by_3 = count % 3 == 0;
        let divisible_by_5 = count % 5 == 0;
        if divisible_by_3 && divisible_by_5 {
            println!("fizz buzz");
        } else if divisible_by_3 {
            println!("fizz");
        } else if divisible_by_5 {
            println!("buzz");
        } else {
            println!("{}", count);
        }
    }
}
