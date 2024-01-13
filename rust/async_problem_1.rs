use std::time::Duration;
use tokio::sync::watch;
use tokio::{sync::oneshot, time::sleep};

// https://www.reddit.com/r/rust/comments/16sihj6/how_does_async_work/
// #[tokio::main]
// async fn main() {
//     let (_, mut killer_rx) = oneshot::channel::<()>();
//     let (_, mut switch_rx) = watch::channel(false);
//
//     let cannot_send = async move {
//         'outer: loop {
//             tokio::select! {
//                 _ = &mut killer_rx => break 'outer,
//                 _ = switch_rx.wait_for(|x| *x) => {},
//             };
//             // switch_rx.wait_for(|x| *x).await;
//             'active: loop {
//                 tokio::select! {
//                     _ = &mut killer_rx => break 'outer,
//                     _ = async { drop(switch_rx.wait_for(|x| !*x).await) } => break 'active,
//                     _ = sleep(Duration::from_secs(1)) => {
//                         // async {}.await;
//                         oneplusone().await;
//                     },
//                 };
//             }
//         }
//     };
//
//     tokio::spawn(cannot_send);
// }

#[tokio::main]
async fn main() {
    let (_, mut killer_rx) = oneshot::channel::<()>();
    let (_, mut switch_rx) = watch::channel(false);

    let cannot_send = async move {
        'outer: loop {
            tokio::select! {
                _ = &mut killer_rx => break 'outer,
                else => {}
            };
            // switch_rx.wait_for(|x| *x).await;
            'active: loop {
                tokio::select! {
                    _ = &mut killer_rx => break 'outer,
                    _ = sleep(Duration::from_secs(1)) => {
                        // async {}.await;
                        oneplusone().await;
                    },
                };
                let res = switch_rx.wait_for(|x| *x).await;
                if res.is_ok() || res.is_err() {
                    println!("if-condition switch_rx wait_for");
                    break 'active;
                }
            }
        }
    };

    tokio::spawn(cannot_send);
}

async fn oneplusone() -> i32 {
    2
}
