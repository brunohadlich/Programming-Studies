struct Color {
    red: u8,
    green: u8,
    blue: u8
}

struct TupleColor(u8,u8,u8);

struct Person {
    first_name: String,
    last_name: String
}

impl Person {
    fn new(first: &str, last: &str) -> Person {
        Person {
            first_name: first.to_string(),
            last_name: last.to_string()
        }
    }

    fn full_name(&self) -> String {
        format!("{} {}", self.first_name, self.last_name)
    }

    fn set_last_name(&mut self, last: &str) {
        self.last_name = last.to_string();
    }
}

pub fn run() {
    let mut color = Color {
        red: 255,
        green: 0,
        blue: 0
    };

    color.red = 13;

    println!("Color - red: {}; green: {}; blue: {}", color.red, color.green, color.blue);
    let mut new_color = TupleColor(135, 7, 53);
    println!("Color - red: {}; green: {}; blue: {}", new_color.0, new_color.1, new_color.2);
    new_color.2 = 20;
    println!("Color - red: {}; green: {}; blue: {}", new_color.0, new_color.1, new_color.2);
    new_color.2 = 20;


    let mut p = Person::new("Olimar", "Fraciscóide");
    println!("Person {} {}", p.first_name, p.last_name);
    println!("Person {}", p.full_name());
    p.set_last_name("Baleieiro");
    println!("Person {}", p.full_name());
}
