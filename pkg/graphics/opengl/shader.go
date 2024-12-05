package renderer

import (
	"io/ioutil"
	"log"

	"github.com/go-gl/gl/v2.1/gl"
)

var shaderProgram uint32

func CreateShaderProgram(vertexPath, fragmentPath string) uint32 {
	// Leer los archivos del shader
	vertexShaderSource, err := ioutil.ReadFile(vertexPath)
	if err != nil {
		log.Fatalf("Error leyendo el archivo del vertex shader: %v", err)
	}

	fragmentShaderSource, err := ioutil.ReadFile(fragmentPath)
	if err != nil {
		log.Fatalf("Error leyendo el archivo del fragment shader: %v", err)
	}

	// Crear los shaders
	vertexShader := compileShaderFromSource(string(vertexShaderSource), gl.VERTEX_SHADER)
	fragmentShader := compileShaderFromSource(string(fragmentShaderSource), gl.FRAGMENT_SHADER)

	// Crear el programa shader
	program := gl.CreateProgram()
	gl.AttachShader(program, vertexShader)
	gl.AttachShader(program, fragmentShader)
	gl.LinkProgram(program)

	// Verificar errores en el enlace del programa
	var logLength int32
	gl.GetProgramiv(program, gl.INFO_LOG_LENGTH, &logLength)
	infoLog := make([]byte, logLength)
	var status int32
	gl.GetProgramiv(program, gl.LINK_STATUS, &status)
	if status == gl.FALSE {
		gl.GetProgramInfoLog(program, logLength, nil, &infoLog[0])
		log.Fatalf("Error al enlazar el shader program: %s", string(infoLog))
	}

	return program
}

func compileShaderFromSource(source string, shaderType uint32) uint32 {
	shader := gl.CreateShader(shaderType)
	// Usar gl.Strs para obtener el puntero al código del shader
	sourcePtr, free := gl.Strs(source)
	defer free()

	gl.ShaderSource(shader, 1, sourcePtr, nil)
	gl.CompileShader(shader)

	// Verificar errores en la compilación del shader
	var logLength int32
	gl.GetShaderiv(shader, gl.INFO_LOG_LENGTH, &logLength)
	infoLog := make([]byte, logLength)
	var status int32
	gl.GetShaderiv(shader, gl.COMPILE_STATUS, &status)
	if status == gl.FALSE {
		gl.GetShaderInfoLog(shader, logLength, nil, &infoLog[0])
		log.Fatalf("Error al compilar el shader: %s", string(infoLog))
	}

	return shader
}
