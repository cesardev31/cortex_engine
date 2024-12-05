package window

import (
	"runtime"

	"github.com/go-gl/gl/v3.3-core/gl"
	"github.com/go-gl/glfw/v3.3/glfw"
)

type Window struct {
	glfwWindow *glfw.Window
	width      int
	height     int
}

func InitGLFW() {
	runtime.LockOSThread()
	if err := glfw.Init(); err != nil {
		panic(err)
	}

	// Configuración para OpenGL moderno
	glfw.WindowHint(glfw.OpenGLProfile, glfw.OpenGLAnyProfile)

}

func NewWindow(width, height int, title string) *Window {
	glfwWindow, err := glfw.CreateWindow(width, height, title, nil, nil)
	if err != nil {
		panic(err)
	}

	glfwWindow.MakeContextCurrent()

	// Inicializar OpenGL
	if err := gl.Init(); err != nil {
		panic(err)
	}

	window := &Window{
		glfwWindow: glfwWindow,
		width:      width,
		height:     height,
	}

	// Configurar callback de redimensionamiento
	glfwWindow.SetSizeCallback(window.resizeCallback)

	return window
}

func (w *Window) resizeCallback(_ *glfw.Window, width, height int) {
	w.width = width
	w.height = height
	gl.Viewport(0, 0, int32(width), int32(height))
}

func (w *Window) GetSize() (int, int) {
	return w.width, w.height
}

func (w *Window) Destroy() {
	w.glfwWindow.Destroy()
}

func (w *Window) ShouldClose() bool {
	return w.glfwWindow.ShouldClose()
}

func (w *Window) PollEvents() {
	glfw.PollEvents()
}

func (w *Window) SwapBuffers() {
	w.glfwWindow.SwapBuffers()
}

func (w *Window) Clear() {
	gl.Clear(gl.COLOR_BUFFER_BIT)
}

func (w *Window) SetClearColor(r, g, b, a float32) {
	gl.ClearColor(r, g, b, a)
}

func TerminateGLFW() {
	glfw.Terminate()
}

func (w *Window) GetGLFWWindow() *glfw.Window {
	return w.glfwWindow
}

// Nuevo método para manejar el bucle principal
func (w *Window) RunLoop(renderFunc func()) {
	for !w.ShouldClose() {
		w.Clear()
		renderFunc()
		w.SwapBuffers()
		w.PollEvents()
	}
}
