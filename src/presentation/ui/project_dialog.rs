use crate::domain::entities::project::ProjectInfo;
use crate::presentation::ui::button::Button;
use ggez::graphics::{self, Canvas, Color, DrawParam, Rect, Text, TextFragment};
use ggez::mint::Point2;
use ggez::Context;
use ggez::GameResult;
use rfd::FileDialog;
use std::path::PathBuf;

pub struct ProjectDialog {
    pub visible: bool,
    pub rect: Rect,
    name_input: String,
    path_input: String,
    create_button: Button,
    cancel_button: Button,
    browse_button: Button,
    is_name_focused: bool,
    is_path_focused: bool,
}

impl ProjectDialog {
    pub fn new() -> Self {
        Self {
            visible: false,
            rect: Rect::new(200.0, 100.0, 400.0, 300.0),
            name_input: String::new(),
            path_input: String::new(),
            create_button: Button::new(350.0, 320.0, 100.0, 30.0, "Crear"),
            cancel_button: Button::new(240.0, 320.0, 100.0, 30.0, "Cancelar"),
            browse_button: Button::new(520.0, 220.0, 60.0, 30.0, "..."),
            is_name_focused: false,
            is_path_focused: false,
        }
    }

    pub fn draw(&self, ctx: &mut Context, canvas: &mut Canvas) -> GameResult {
        if !self.visible {
            return Ok(());
        }

        // Fondo del diálogo
        canvas.draw(
            &graphics::Mesh::new_rectangle(
                ctx,
                graphics::DrawMode::fill(),
                self.rect,
                Color::new(0.2, 0.2, 0.2, 1.0),
            )?,
            DrawParam::default(),
        );

        // Título
        let title = Text::new(TextFragment::new("Crear Nuevo Proyecto").color(Color::WHITE));
        canvas.draw(
            &title,
            Point2 {
                x: self.rect.x + 20.0,
                y: self.rect.y + 20.0,
            },
        );

        // Campos de entrada
        self.draw_input_field(
            ctx,
            canvas,
            "Nombre del Proyecto:",
            &self.name_input,
            self.rect.y + 80.0,
            self.is_name_focused,
        )?;

        self.draw_input_field(
            ctx,
            canvas,
            "Ubicación:",
            &self.path_input,
            self.rect.y + 160.0,
            self.is_path_focused,
        )?;

        // Botones
        self.create_button.draw(ctx, canvas)?;
        self.cancel_button.draw(ctx, canvas)?;
        self.browse_button.draw(ctx, canvas)?;

        Ok(())
    }

    fn draw_input_field(
        &self,
        ctx: &mut Context,
        canvas: &mut Canvas,
        label: &str,
        value: &str,
        y: f32,
        is_focused: bool,
    ) -> GameResult {
        // Etiqueta
        let label_text = Text::new(TextFragment::new(label).color(Color::WHITE));
        canvas.draw(
            &label_text,
            Point2 {
                x: self.rect.x + 20.0,
                y,
            },
        );

        // Campo de entrada
        let input_bg_color = if is_focused {
            Color::new(0.3, 0.3, 0.3, 1.0)
        } else {
            Color::new(0.15, 0.15, 0.15, 1.0)
        };

        canvas.draw(
            &graphics::Mesh::new_rectangle(
                ctx,
                graphics::DrawMode::fill(),
                Rect::new(self.rect.x + 20.0, y + 25.0, 300.0, 30.0),
                input_bg_color,
            )?,
            DrawParam::default(),
        );

        let input_text = Text::new(TextFragment::new(value).color(Color::WHITE));
        canvas.draw(
            &input_text,
            Point2 {
                x: self.rect.x + 25.0,
                y: y + 32.0,
            },
        );

        Ok(())
    }

    pub fn handle_input(&mut self, text: char) {
        if self.is_name_focused {
            if text == '\u{8}' {
                // Backspace
                self.name_input.pop();
            } else {
                self.name_input.push(text);
            }
        } else if self.is_path_focused {
            if text == '\u{8}' {
                // Backspace
                self.path_input.pop();
            } else {
                self.path_input.push(text);
            }
        }
    }

    pub fn handle_click(&mut self, x: f32, y: f32) -> Option<ProjectInfo> {
        if !self.visible {
            return None;
        }

        // Verificar clicks en campos de entrada
        let name_input_rect = Rect::new(self.rect.x + 20.0, self.rect.y + 105.0, 300.0, 30.0);
        let path_input_rect = Rect::new(self.rect.x + 20.0, self.rect.y + 185.0, 300.0, 30.0);

        self.is_name_focused = name_input_rect.contains(Point2 { x, y });
        self.is_path_focused = path_input_rect.contains(Point2 { x, y });

        // Manejar botones
        if self.browse_button.is_clicked(x, y) {
            if let Some(path) = FileDialog::new()
                .set_title("Seleccionar ubicación del proyecto")
                .set_directory("/")
                .pick_folder()
            {
                self.path_input = path.to_string_lossy().to_string();
            }
        }

        if self.create_button.is_clicked(x, y) {
            if !self.name_input.is_empty() && !self.path_input.is_empty() {
                let project = ProjectInfo::new(
                    self.name_input.clone(),
                    PathBuf::from(&self.path_input).join(&self.name_input),
                );
                self.visible = false;
                return Some(project);
            }
        }

        if self.cancel_button.is_clicked(x, y) {
            self.visible = false;
        }

        None
    }

    pub fn show(&mut self) {
        self.visible = true;
        self.name_input.clear();
        self.path_input.clear();
        self.is_name_focused = false;
        self.is_path_focused = false;
    }
}
