use ggez::graphics::{self, Color, DrawParam};
use ggez::{Context, GameResult};

pub trait Renderer {
    fn clear(&mut self, color: Color);
    fn draw_mesh(&mut self, mesh: &graphics::Mesh, param: DrawParam) -> GameResult;
    fn draw_text(&mut self, text: &graphics::Text, param: DrawParam) -> GameResult;
    fn draw_image(&mut self, image: &graphics::Image, param: DrawParam) -> GameResult;
    fn present(&mut self, ctx: &mut Context) -> GameResult;
}

pub struct GgezRenderer {
    color: Color,
}

impl GgezRenderer {
    pub fn new(_ctx: &mut Context) -> Self {
        Self {
            color: Color::BLACK,
        }
    }
}

impl Renderer for GgezRenderer {
    fn clear(&mut self, color: Color) {
        self.color = color;
    }

    fn draw_mesh(&mut self, mesh: &graphics::Mesh, param: DrawParam) -> GameResult {
        Ok(()) // Se dibujará en present
    }

    fn draw_text(&mut self, text: &graphics::Text, param: DrawParam) -> GameResult {
        Ok(()) // Se dibujará en present
    }

    fn draw_image(&mut self, image: &graphics::Image, param: DrawParam) -> GameResult {
        Ok(()) // Se dibujará en present
    }

    fn present(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, self.color);

        // Aquí iría la lógica de dibujo acumulada
        // Por ahora solo limpiamos y presentamos

        canvas.finish(ctx)
    }
}
