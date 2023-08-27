use std::io::{stdin, stdout, BufWriter, Stdout, Write};

use termion::{
    clear, color, cursor,
    event::Key,
    input::TermRead,
    raw::{IntoRawMode, RawTerminal},
    screen::{AlternateScreen, IntoAlternateScreen},
    terminal_size,
};

fn main() {
    let stdin = stdin();
    let (w, h) = terminal_size().unwrap();
    let mut stdout = BufWriter::with_capacity(
        256 * 1024,
        stdout()
            .into_raw_mode()
            .unwrap()
            .into_alternate_screen()
            .unwrap(),
    );
    write!(stdout, "{}", cursor::Hide).unwrap();
    draw_border(&mut stdout);
    stdout.flush().unwrap();

    for key in stdin.keys() {
        // clear(&mut stdout);
        write!(stdout, "{}", clear::All).unwrap();
        draw_border(&mut stdout);
        match key.unwrap() {
            Key::Char('q') => break,
            Key::Char('j') => {
                // write!(stdout, "{}", color::Fg(color::Red)).unwrap();
                // for r in 1..=h {
                //     write!(stdout, "{}", cursor::Goto(1, r)).unwrap();
                //     write!(stdout, "{}", "j".repeat(w as usize)).unwrap();
                //     // "j".repeat()
                // }
                for c in 1..=w {
                    for r in 1..=h {
                        write!(stdout, "{}{}{}", color::Fg(color::Red), cursor::Goto(c, r), 'j').unwrap();
                    }
                }
            }
            Key::Char('k') => {
                for i in 1..h {
                    write!(stdout, "{}k", cursor::Goto(1, i),).unwrap();
                    write!(stdout, "{}k", cursor::Goto(2, i),).unwrap();
                    write!(stdout, "{}k", cursor::Goto(3, i),).unwrap();
                    write!(stdout, "{}k", cursor::Goto(4, i),).unwrap();
                    write!(stdout, "{}k", cursor::Goto(5, i),).unwrap();
                }
            }
            _ => {
                for i in 1..w {
                    write!(stdout, "{}D", cursor::Goto(i, 1),).unwrap();
                }
                for i in 1..h {
                    write!(stdout, "{}D", cursor::Goto(1, i),).unwrap();
                }
            }
        }
        stdout.flush().unwrap();
    }

    // std::thread::sleep(std::time::Duration::from_secs(2));
    write!(stdout, "{}", cursor::Show).unwrap();
}

fn draw_border(stdout: &mut BufWriter<AlternateScreen<RawTerminal<Stdout>>>) {
    let (w, h) = terminal_size().unwrap();
    let wins: [u16; 3] = [1, w / 6, w / 2];
    write!(
        stdout,
        "{}{}",
        color::Fg(color::Reset),
        color::Bg(color::Reset)
    )
    .unwrap();
    for i in 2..w {
        write!(stdout, "{}─{}─", cursor::Goto(i, 2), cursor::Goto(i, h - 1)).unwrap();
    }

    for i in 3..h - 1 {
        write!(
            stdout,
            "{}│{}│{}│{}│",
            cursor::Goto(1, i),
            cursor::Goto(w, i),
            cursor::Goto(wins[1], i),
            cursor::Goto(wins[2], i),
        )
        .unwrap();
    }

    write!(
        stdout,
        "{}┌{}┬{}┬{}┐{}└{}┴{}┴{}┘",
        cursor::Goto(1, 2),
        cursor::Goto(wins[1], 2),
        cursor::Goto(wins[2], 2),
        cursor::Goto(w, 2),
        cursor::Goto(1, h - 1),
        cursor::Goto(wins[1], h - 1),
        cursor::Goto(wins[2], h - 1),
        cursor::Goto(w, h - 1),
    )
    .unwrap();
}

#[allow(dead_code)]
fn clear(stdout: &mut BufWriter<AlternateScreen<RawTerminal<Stdout>>>) {
    write!(
        stdout,
        "{}{}",
        color::Fg(color::Reset),
        color::Bg(color::Reset)
    )
    .unwrap();
    let (w, h) = terminal_size().unwrap();
    for c in 1..=w {
        for r in 1..=h {
            write!(stdout, "{} ", cursor::Goto(c, r)).unwrap();
        }
    }
}
