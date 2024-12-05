package launcher

import (
	"github.com/AllenDang/giu"
	"github.com/cesardev31/cortex_engine/pkg/core/database"
	"github.com/cesardev31/cortex_engine/pkg/ui/menu"
)

type Launcher struct {
	MainMenu *menu.ProjectLauncher
	DB       *database.Database
}

func NewLauncher(db *database.Database) *Launcher {
	mainMenu := menu.NewMainMenu(db)

	return &Launcher{
		MainMenu: mainMenu,
		DB:       db,
	}
}

func (l *Launcher) Run() {
	// Crear la ventana de giu
	wnd := giu.NewMasterWindow("Cortex Engine", 800, 600, giu.MasterWindowFlagsNotResizable)

	// Ejecutar el bucle principal usando giu
	wnd.Run(func() {
		l.MainMenu.Show()
	})
}
