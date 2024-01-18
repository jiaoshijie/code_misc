// TODO:

fn priority(ch: char) -> usize {
    match ch {
        '-' | '+' => 0,
        '/' | '*' => 1,
        _ => panic!("Unknown operator in priority()!!!"),
    }
}

fn calc(oprand1: i32, oprand2: i32, op: char) -> i32 {
    match op {
        '-' => oprand1 - oprand2,
        '+' => oprand1 + oprand2,
        '/' => oprand1 / oprand2,
        '*' => oprand1 * oprand2,
        _ => panic!("Unknown operator in calc()!!!"),
    }
}

fn main() {
    let expression: String = "-1+1-9/-3".to_string();
    let (mut operand, mut operator): (Vec<i32>, Vec<char>) = (Vec::new(), Vec::new());
    let mut chars = expression.chars();
    let mut number = String::new();
    let mut negative = false;
    while let Some(ch) = chars.next() {
        if ch.is_ascii_digit() {
            number.push(ch);
        } else {
            if number.is_empty() {
                negative = true;
            } else {
                let mut num: i32 = number.parse().unwrap();
                if negative {
                    negative = false;
                    num *= -1;
                }
                number.clear();
                if operator.is_empty() {
                    operand.push(num);
                    operator.push(ch);
                } else {
                    let prev_op = *operator.last().unwrap();
                    if priority(ch) <= priority(prev_op) {
                        operator.pop();
                        let prev_num = operand.pop().unwrap();
                        operand.push(calc(prev_num, num, prev_op));
                    } else {
                        operand.push(num);
                    }
                    operator.push(ch);
                }
            }
        }
    }

    let mut last_num: i32 = number.parse().unwrap();
    while let Some(op) = operator.pop() {
        last_num = calc(operand.pop().unwrap(), last_num, op);
    }

    println!("{last_num}");
}
