use crossterm::{
    cursor,
    event::{self, Event, KeyCode, KeyEvent},
    execute, queue,
    style::{self, Color, SetBackgroundColor, SetForegroundColor},
    terminal::{self, ClearType},
    Result,
};
use std::{
    io::{self, Write},
    process::Command,
    thread, time,
};

fn main() -> Result<()> {
    let mut stdout = io::stdout();
    execute!(stdout, terminal::EnterAlternateScreen)?;
    terminal::enable_raw_mode()?;
    queue!(
        stdout,
        style::ResetColor,
        terminal::Clear(ClearType::All),
        cursor::Hide,
        cursor::MoveTo(0, 0)
    )?;

    let mut cur_cursor_pos = 0;
    loop {
        queue!(stdout, cursor::MoveTo(0, 0))?;
        for i in 0..10 {
            if i == cur_cursor_pos {
                queue!(
                    stdout,
                    SetForegroundColor(Color::Black),
                    SetBackgroundColor(Color::Blue),
                )?;
            }
            queue!(
                stdout,
                style::Print(format!("some thing {}", i)),
                cursor::MoveToNextLine(1),
                style::ResetColor
            )?;
        }
        stdout.flush()?;
        match read_char()? {
            'q' => break,
            'j' => {
                if cur_cursor_pos < 10 - 1 {
                    cur_cursor_pos += 1;
                }
            }
            'k' => {
                if cur_cursor_pos > 0 {
                    cur_cursor_pos -= 1;
                }
            }
            'o' => {
                execute!(stdout, terminal::LeaveAlternateScreen)?;
                open();
                execute!(stdout, terminal::EnterAlternateScreen, cursor::Hide)?;
            }
            _ => {}
        }
    }

    execute!(
        stdout,
        style::ResetColor,
        cursor::Show,
        terminal::LeaveAlternateScreen
    )?;

    terminal::disable_raw_mode()?;

    Ok(())
}

fn open() {
    let mut cmd = Command::new("sh");
    cmd.arg("-c").arg(format!("vim {}", "/home/jsj/lf.log"));
    cmd.status().unwrap();
}

fn read_char() -> Result<char> {
    loop {
        if let Ok(Event::Key(KeyEvent {
            code: KeyCode::Char(c),
            ..
        })) = event::read()
        {
            return Ok(c);
        }
    }
}
