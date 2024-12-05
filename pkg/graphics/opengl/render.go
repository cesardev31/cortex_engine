package renderer

import (
	"github.com/go-gl/gl/v3.3-core/gl"
)

func RenderTexture(texture uint32, x, y, width, height int) {
	// Definir los vértices del quad (un rectángulo)
	vertices := []float32{
		// Posiciones        // Coordenadas de textura
		float32(x), float32(y), 0.0, 1.0, // Esquina inferior izquierda
		float32(x + width), float32(y), 1.0, 1.0, // Esquina inferior derecha
		float32(x), float32(y + height), 0.0, 0.0, // Esquina superior izquierda
		float32(x + width), float32(y + height), 1.0, 0.0, // Esquina superior derecha
	}

	var vao, vbo uint32
	gl.GenVertexArrays(1, &vao)
	gl.GenBuffers(1, &vbo)

	gl.BindVertexArray(vao)
	gl.BindBuffer(gl.ARRAY_BUFFER, vbo)
	gl.BufferData(gl.ARRAY_BUFFER, len(vertices)*4, gl.Ptr(vertices), gl.STATIC_DRAW)

	gl.VertexAttribPointer(0, 2, gl.FLOAT, false, 4*4, gl.PtrOffset(0))
	gl.EnableVertexAttribArray(0)
	gl.VertexAttribPointer(1, 2, gl.FLOAT, false, 4*4, gl.PtrOffset(2*4))
	gl.EnableVertexAttribArray(1)

	// Activar la textura y enlazarla
	gl.ActiveTexture(gl.TEXTURE0)
	gl.BindTexture(gl.TEXTURE_2D, texture)

	// Dibujar el cuadrado
	gl.DrawArrays(gl.TRIANGLE_STRIP, 0, 4)

	// Limpiar
	gl.BindVertexArray(0)
	gl.BindBuffer(gl.ARRAY_BUFFER, 0)
}
