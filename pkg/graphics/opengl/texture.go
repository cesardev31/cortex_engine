package renderer

import (
	"image"
	_ "image/png" // El import vacío asegura que Go use el paquete de PNG, aunque no lo uses explícitamente
	"log"
	"os"

	"github.com/go-gl/gl/v3.3-core/gl"
	"github.com/nfnt/resize"
)

func CreateTextureFromFile(file string, width, height uint) (uint32, error) {
	// Abrir archivo de imagen
	imgFile, err := os.Open(file)
	if err != nil {
		return 0, err
	}
	defer imgFile.Close()

	// Decodificar imagen (Go decidirá el formato de imagen según el contenido del archivo)
	img, _, err := image.Decode(imgFile)
	if err != nil {
		return 0, err
	}

	// Redimensionar la imagen
	img = resize.Resize(width, height, img, resize.Lanczos3)

	// Convertir imagen a formato OpenGL
	return createTexture(img), nil
}

func createTexture(img image.Image) uint32 {
	rgba := image.NewRGBA(img.Bounds())
	for y := 0; y < rgba.Rect.Dy(); y++ {
		for x := 0; x < rgba.Rect.Dx(); x++ {
			rgba.Set(x, y, img.At(x, y))
		}
	}

	var texture uint32
	gl.GenTextures(1, &texture)
	gl.BindTexture(gl.TEXTURE_2D, texture)

	gl.TexImage2D(gl.TEXTURE_2D, 0, gl.RGBA, int32(rgba.Rect.Size().X), int32(rgba.Rect.Size().Y), 0, gl.RGBA, gl.UNSIGNED_BYTE, gl.Ptr(rgba.Pix))
	gl.GenerateMipmap(gl.TEXTURE_2D)

	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_LINEAR)
	gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR)

	log.Println("Textura generada correctamente")
	return texture
}
