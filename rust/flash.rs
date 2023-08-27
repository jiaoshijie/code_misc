use crossterm::{
    cursor,
    event::{self, Event, KeyCode, KeyEvent, KeyModifiers},
    execute, queue,
    style::{self, ResetColor},
    terminal::{self, Clear, ClearType},
};
use std::{
    io::{self, Stdout, Write},
    time,
};

macro_rules! draw_box {
    ($out:expr, $symbol:expr, $($position:expr),+ $(,)?) => {
        queue!(
            $out,
            $(cursor::MoveTo($position.0, $position.1), style::Print($symbol),)+
        )
        .unwrap();
    }
}

fn main() {
    let mut stdout = io::stdout();
    execute!(stdout, terminal::EnterAlternateScreen)
        .expect("EnterAlternateScreen failed in ui.init()");
    terminal::enable_raw_mode().expect("enable raw mode failed in ui.init()");
    execute!(
        stdout,
        style::ResetColor,
        terminal::Clear(ClearType::All),
        cursor::Hide,
    )
    .unwrap();

    // NOTICE: do something
    draw_border(&mut stdout);
    stdout.flush().unwrap();

    'Exit: loop {
        if event::poll(time::Duration::from_millis(50)).unwrap() {
            match event::read().unwrap() {
                Event::Key(k) => {
                    // queue!(stdout, Clear(ClearType::All)).unwrap();
                    clear(&mut stdout);
                    if k == KeyEvent::new(KeyCode::Char('q'), KeyModifiers::NONE) {
                        break 'Exit;
                    } else if k == KeyEvent::new(KeyCode::Char('j'), KeyModifiers::NONE) {
                        queue!(stdout, cursor::MoveTo(0, 0), style::Print('j')).unwrap();
                    } else if k == KeyEvent::new(KeyCode::Char('k'), KeyModifiers::NONE) {
                        queue!(stdout, cursor::MoveTo(1, 0), style::Print('k')).unwrap();
                    } else {
                        queue!(stdout, cursor::MoveTo(2, 0), style::Print('D')).unwrap();
                    }
                    draw_border(&mut stdout);
                    stdout.flush().unwrap();
                }
                _ => {}
            }
        }
    }

    execute!(
        stdout,
        style::ResetColor,
        cursor::Show,
        terminal::LeaveAlternateScreen
    )
    .expect("reset terminal failed in ui.clear()");

    terminal::disable_raw_mode().expect("disable raw mode failed in ui.clear()");
}

fn clear(stdout: &mut Stdout) {
    queue!(stdout, ResetColor).unwrap();
    let (w, h) = terminal::size().unwrap();
    for c in 0..w {
        for r in 0..h {
            queue!(stdout, cursor::MoveTo(c, r), style::Print(' ')).unwrap();
        }
    }
}

fn draw_border(stdout: &mut Stdout) {
    let (w, h) = terminal::size().unwrap();
    let wins: [u16; 3] = [1, w / 6, w / 2];
    for i in 1..w - 1 {
        draw_box!(stdout, '─', (i, 1), (i, h - 2));
    }
    for i in 2..h - 2 {
        draw_box!(stdout, '│', (0, i), (w - 1, i), (wins[1], i), (wins[2], i),);
    }
    draw_box!(stdout, '┴', (wins[1], h - 2), (wins[2], h - 2));
    draw_box!(stdout, '┬', (wins[1], 1), (wins[2], 1));

    queue!(
        stdout,
        cursor::MoveTo(0, 1),
        style::Print('┌'),
        cursor::MoveTo(w - 1, 1),
        style::Print('┐'),
        cursor::MoveTo(0, h - 2),
        style::Print('└'),
        cursor::MoveTo(w - 1, h - 2),
        style::Print('┘'),
    )
    .unwrap();
}
