pub trait Renderer {
    fn draw_sprite(&mut self, sprite: &Sprite, position: Vector2) -> Result<(), RenderError>;
    fn draw_text(&mut self, text: &str, position: Vector2) -> Result<(), RenderError>;
    fn clear(&mut self, color: Color);
    fn present(&mut self) -> Result<(), RenderError>;
}

pub struct OpenGLRenderer {
    context: Context,
    // ... configuración específica de OpenGL
}

impl Renderer for OpenGLRenderer {
    // Implementación específica para OpenGL
}
