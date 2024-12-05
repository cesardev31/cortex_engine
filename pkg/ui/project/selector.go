package project

import (
	"log"

	"github.com/go-gl/gl/v3.3-core/gl"
	"github.com/go-gl/glfw/v3.3/glfw"
)

func ShowProjectSelector() {
	// Inicializar GLFW
	if err := glfw.Init(); err != nil {
		log.Fatalf("No se pudo inicializar GLFW: %v", err)
	}
	defer glfw.Terminate() // Asegurarse de que GLFW se termine correctamente al salir

	// Crear ventana
	window, err := glfw.CreateWindow(800, 600, "Seleccionar Proyecto", nil, nil)
	if err != nil {
		log.Fatalf("No se pudo crear la ventana: %v", err)
	}
	defer window.Destroy()

	// Establecer el contexto de OpenGL
	window.MakeContextCurrent()

	// Inicializar OpenGL
	if err := gl.Init(); err != nil {
		log.Fatalf("No se pudo inicializar OpenGL: %v", err)
	}

	// Configurar el color de fondo
	gl.ClearColor(0.1, 0.1, 0.1, 1.0) // Fondo oscuro
	// Esperar a que el usuario cierre la ventana
	for !window.ShouldClose() {
		gl.Clear(gl.COLOR_BUFFER_BIT)
		window.SwapBuffers()
		glfw.PollEvents()
	}
}
