package database

import (
	"database/sql"
	"time"

	_ "github.com/mattn/go-sqlite3"
)

type Project struct {
	ID        int64
	Name      string
	Path      string
	LastOpen  time.Time
	CreatedAt time.Time
}

type Database struct {
	db *sql.DB
}

func NewDatabase(dbPath string) (*Database, error) {
	db, err := sql.Open("sqlite3", dbPath)
	if err != nil {
		return nil, err
	}

	// Crear tabla si no existe
	_, err = db.Exec(`
        CREATE TABLE IF NOT EXISTS projects (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            path TEXT NOT NULL,
            last_open DATETIME,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    `)
	if err != nil {
		return nil, err
	}

	return &Database{db: db}, nil
}

func (d *Database) Close() error {
	return d.db.Close()
}

func (d *Database) GetRecentProjects(limit int) ([]Project, error) {
	rows, err := d.db.Query(`
        SELECT id, name, path, last_open, created_at 
        FROM projects 
        ORDER BY last_open DESC 
        LIMIT ?
    `, limit)
	if err != nil {
		return nil, err
	}
	defer rows.Close()

	var projects []Project
	for rows.Next() {
		var p Project
		err := rows.Scan(&p.ID, &p.Name, &p.Path, &p.LastOpen, &p.CreatedAt)
		if err != nil {
			return nil, err
		}
		projects = append(projects, p)
	}

	return projects, nil
}

func (d *Database) AddProject(name, path string) error {
	_, err := d.db.Exec(`
        INSERT INTO projects (name, path, last_open) 
        VALUES (?, ?, ?)
    `, name, path, time.Now())
	return err
}

func (d *Database) UpdateProjectLastOpen(id int64) error {
	_, err := d.db.Exec(`
        UPDATE projects 
        SET last_open = ? 
        WHERE id = ?
    `, time.Now(), id)
	return err
}
