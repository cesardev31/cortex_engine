package menu

import (
	"fmt"

	"github.com/AllenDang/giu"
	"github.com/cesardev31/cortex_engine/pkg/core/database"
)

type ProjectLauncher struct {
	projects []database.Project
	db       *database.Database
}

func NewMainMenu(db *database.Database) *ProjectLauncher {
	return &ProjectLauncher{
		db:       db,
		projects: make([]database.Project, 0),
	}
}

func (m *ProjectLauncher) loadRecentProjects() error {
	projects, err := m.db.GetRecentProjects(10)
	if err != nil {
		return err
	}
	m.projects = projects
	return nil
}

func (m *ProjectLauncher) Show() {
	if err := m.loadRecentProjects(); err != nil {
		panic(err)
	}

	giu.SingleWindow().Layout(
		giu.Row(
			giu.Button("Crear Proyecto").OnClick(func() {
				fmt.Println("Abriendo diálogo de creación")
			}),
			giu.Button("Buscar Proyecto").OnClick(func() {
				fmt.Println("Abriendo navegador de proyectos")
			}),
		),
		giu.Label("Proyectos Recientes:"),
		giu.Custom(func() {
			if len(m.projects) == 0 {
				giu.Label("No hay proyectos recientes").Build()
			} else {
				for _, project := range m.projects {
					giu.Selectable(fmt.Sprintf("%s - Último acceso: %s",
						project.Name,
						project.LastOpen.Format("2006-01-02 15:04"))).
						OnClick(func() {
							fmt.Printf("Abriendo proyecto: %s\n", project.Name)
						}).Build()
				}
			}
		}),
	)
}
