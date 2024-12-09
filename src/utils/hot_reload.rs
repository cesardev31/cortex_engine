use notify::{Config, Event, RecommendedWatcher, RecursiveMode, Watcher};
use std::path::Path;
use std::sync::mpsc::{channel, Receiver};

pub struct HotReload {
    _watcher: RecommendedWatcher,
}

impl HotReload {
    pub fn new(path: &str) -> notify::Result<(Self, Receiver<()>)> {
        let (tx, rx) = channel();
        let config = Config::default().with_poll_interval(std::time::Duration::from_secs(1));

        let mut watcher = RecommendedWatcher::new(
            move |res: Result<Event, notify::Error>| {
                if res.is_ok() {
                    let _ = tx.send(());
                }
            },
            config,
        )?;

        watcher.watch(Path::new(path), RecursiveMode::Recursive)?;

        Ok((Self { _watcher: watcher }, rx))
    }
}
