use std::io::{self, Write};
use crossterm::{
    execute, terminal::{self, ClearType},
    event::{self, Event, KeyCode, KeyEvent},
    queue, cursor, Result,
    style::{self, SetForegroundColor, SetBackgroundColor, Color},
};
use std::path::PathBuf;

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
    let cur_path = PathBuf::from(".");
    let cur_dir_files = read_dir(cur_path);
    let mut cur_cursor_pos = 0;
    loop {
        queue!(stdout, cursor::MoveTo(0, 0))?;
        for i in 0..cur_dir_files.len() {
            if i == cur_cursor_pos {
                queue!(
                    stdout,
                    SetForegroundColor(Color::Black),
                    SetBackgroundColor(Color::Blue),
                )?;
            }
            queue!(
                stdout,
                style::Print(&cur_dir_files[i]),
                cursor::MoveToNextLine(1),
                style::ResetColor
            )?;
        }
        stdout.flush()?;
        match read_char()? {
            'q' => break,
            'j' => {
                if cur_cursor_pos < cur_dir_files.len() - 1 {
                    cur_cursor_pos += 1;
                }
            },
            'k' => {
                if cur_cursor_pos > 0 {
                    cur_cursor_pos -= 1;
                }
            },
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

fn read_dir(path: PathBuf) -> Vec<String> {
    let mut ret = Vec::<String>::new();
    for entry in path.read_dir().expect("read_dir call failed") {
        if let Ok(entry) = entry {
            ret.push(String::from(entry.path().file_name().unwrap().to_str().unwrap()));
        }
    }
    ret
}
