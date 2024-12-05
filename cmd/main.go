package main

import (
	"log"
	"path/filepath"

	"github.com/cesardev31/cortex_engine/internal/launcher"
	"github.com/cesardev31/cortex_engine/pkg/core/database"
)

func main() {
	// Inicializar la base de datos
	dbPath := filepath.Join(".", "cortex.db")
	db, err := database.NewDatabase(dbPath)
	if err != nil {
		log.Fatalf("Error al inicializar la base de datos: %v", err)
	}
	defer db.Close()

	// Crear y ejecutar el launcher con la base de datos
	app := launcher.NewLauncher(db)
	app.Run()
}
