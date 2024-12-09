use ggez::graphics::{self, Canvas, Color, DrawParam, Rect, Text, TextFragment};
use ggez::mint::Point2;
use ggez::Context;
use ggez::GameResult;

pub struct Button {
    pub rect: Rect,
    pub active: bool,
    pub text: String,
    pub recent_projects: Vec<String>,
}

impl Button {
    pub fn new(x: f32, y: f32, width: f32, height: f32, text: &str) -> Self {
        Button {
            rect: Rect::new(x, y, width, height),
            active: false,
            text: text.to_string(),
            recent_projects: Vec::new(),
        }
    }

    pub fn is_clicked(&self, x: f32, y: f32) -> bool {
        x >= self.rect.x
            && x <= self.rect.x + self.rect.w
            && y >= self.rect.y
            && y <= self.rect.y + self.rect.h
    }

    pub fn draw(&self, ctx: &mut Context, canvas: &mut Canvas) -> GameResult {
        // Dibuja el fondo del botón
        let button_color = if self.active {
            Color::new(0.3, 0.3, 0.3, 1.0)
        } else {
            Color::new(0.2, 0.2, 0.2, 1.0)
        };

        canvas.draw(
            &graphics::Mesh::new_rectangle(
                ctx,
                graphics::DrawMode::fill(),
                self.rect,
                button_color,
            )?,
            DrawParam::default(),
        );

        // Dibuja el texto del botón
        let text = Text::new(TextFragment::new(&self.text).color(Color::WHITE));
        let text_dimensions = text.measure(ctx)?;
        let text_pos = Point2 {
            x: self.rect.x + (self.rect.w - text_dimensions.x) / 2.0,
            y: self.rect.y + (self.rect.h - text_dimensions.y) / 2.0,
        };
        canvas.draw(&text, text_pos);

        Ok(())
    }
}
