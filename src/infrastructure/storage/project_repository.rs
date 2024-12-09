use crate::domain::entities::project::ProjectInfo;
use chrono::{DateTime, Local};
use directories::ProjectDirs;
use rusqlite::{params, Connection, Result as SqlResult};
use std::fs;
use std::io;
use std::path::PathBuf;

pub struct ProjectRepository {
    conn: Connection,
}

impl ProjectRepository {
    pub fn new() -> SqlResult<Self> {
        let db_path = Self::get_database_path()
            .map_err(|e| rusqlite::Error::InvalidPath(e.to_string().into()))?;

        // Verificar si el archivo existe
        let db_exists = db_path.exists();

        // Crear conexión
        let conn = Connection::open(&db_path)?;

        // Si es una nueva base de datos, inicializarla
        if !db_exists {
            Self::initialize_database(&conn)?;
        }

        Ok(Self { conn })
    }

    fn initialize_database(conn: &Connection) -> SqlResult<()> {
        // Crear tabla de proyectos
        conn.execute(
            "CREATE TABLE IF NOT EXISTS recent_projects (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL,
                path TEXT NOT NULL UNIQUE,
                created_at TEXT NOT NULL,
                last_opened TEXT NOT NULL
            )",
            [],
        )?;

        // Crear índices
        conn.execute(
            "CREATE INDEX IF NOT EXISTS idx_last_opened 
             ON recent_projects(last_opened DESC)",
            [],
        )?;

        conn.execute(
            "CREATE UNIQUE INDEX IF NOT EXISTS idx_path 
             ON recent_projects(path)",
            [],
        )?;

        Ok(())
    }

    fn get_database_path() -> io::Result<PathBuf> {
        let proj_dirs = ProjectDirs::from("com", "cortex", "engine").ok_or_else(|| {
            io::Error::new(
                io::ErrorKind::NotFound,
                "No se pudo obtener directorio de datos",
            )
        })?;

        let data_dir = proj_dirs.data_dir();
        fs::create_dir_all(data_dir)?;

        Ok(data_dir.join("projects.db"))
    }

    pub fn add_project(&self, project: &ProjectInfo) -> SqlResult<()> {
        self.conn.execute(
            "INSERT OR REPLACE INTO recent_projects (name, path, created_at, last_opened)
             VALUES (?1, ?2, ?3, ?4)",
            params![
                project.name,
                project.path.to_string_lossy().to_string(),
                project.created_at.to_rfc3339(),
                Local::now().to_rfc3339(),
            ],
        )?;
        Ok(())
    }

    pub fn get_recent_projects(&self, limit: i64) -> SqlResult<Vec<ProjectInfo>> {
        let mut stmt = self.conn.prepare(
            "SELECT name, path, created_at 
             FROM recent_projects 
             ORDER BY last_opened DESC 
             LIMIT ?",
        )?;

        let projects = stmt.query_map([limit], |row| {
            Ok(ProjectInfo {
                name: row.get(0)?,
                path: PathBuf::from(row.get::<_, String>(1)?),
                created_at: DateTime::parse_from_rfc3339(&row.get::<_, String>(2)?)
                    .unwrap()
                    .with_timezone(&Local),
            })
        })?;

        projects.collect()
    }

    pub fn update_last_opened(&self, path: &PathBuf) -> SqlResult<()> {
        self.conn.execute(
            "UPDATE recent_projects 
             SET last_opened = ? 
             WHERE path = ?",
            params![
                Local::now().to_rfc3339(),
                path.to_string_lossy().to_string(),
            ],
        )?;
        Ok(())
    }

    pub fn remove_project(&self, path: &PathBuf) -> SqlResult<()> {
        self.conn.execute(
            "DELETE FROM recent_projects WHERE path = ?",
            params![path.to_string_lossy().to_string()],
        )?;
        Ok(())
    }

    pub fn exists(&self, path: &PathBuf) -> SqlResult<bool> {
        let count: i64 = self.conn.query_row(
            "SELECT COUNT(*) FROM recent_projects WHERE path = ?",
            params![path.to_string_lossy().to_string()],
            |row| row.get(0),
        )?;

        Ok(count > 0)
    }
}
