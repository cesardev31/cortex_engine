use chrono::{DateTime, Local};
use std::path::PathBuf;

#[derive(Clone, Debug)]
pub struct ProjectInfo {
    pub name: String,
    pub path: PathBuf,
    pub created_at: DateTime<Local>,
}

impl ProjectInfo {
    pub fn new(name: String, path: PathBuf) -> Self {
        Self {
            name,
            path,
            created_at: Local::now(),
        }
    }
}
