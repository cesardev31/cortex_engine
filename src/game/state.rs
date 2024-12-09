use crate::utils::hot_reload::HotReload;
use ggez::event::{EventHandler, MouseButton};
use ggez::graphics::{self, Color, DrawParam, Text, TextFragment};
use ggez::mint::Point2;
use ggez::{Context, GameResult};
use rfd::FileDialog;
use std::sync::mpsc::Receiver;

use super::button::Button;

pub struct GameState {
    create_button: Button,
    open_button: Button,
    recent_projects: Vec<String>,
    _hot_reload: Option<HotReload>,
    reload_receiver: Option<Receiver<()>>,
}

impl GameState {
    pub fn new() -> Self {
        let (hot_reload, rx) = HotReload::new("src").ok().unzip();

        GameState {
            create_button: Button::new(50.0, 50.0, 200.0, 40.0, "Crear Proyecto"),
            open_button: Button::new(50.0, 120.0, 200.0, 40.0, "Abrir Proyecto"),
            recent_projects: vec![],
            _hot_reload: hot_reload,
            reload_receiver: rx,
        }
    }

    fn draw_button(
        &self,
        ctx: &mut Context,
        canvas: &mut graphics::Canvas,
        button: &Button,
    ) -> GameResult {
        // Dibuja el fondo del botón
        let button_color = if button.active {
            Color::new(0.3, 0.3, 0.3, 1.0)
        } else {
            Color::new(0.2, 0.2, 0.2, 1.0)
        };

        canvas.draw(
            &graphics::Mesh::new_rectangle(
                ctx,
                graphics::DrawMode::fill(),
                button.rect,
                button_color,
            )?,
            DrawParam::default(),
        );

        // Dibuja el texto del botón
        let text = Text::new(TextFragment::new(&button.text).color(Color::WHITE));
        let text_dimensions = text.measure(ctx)?;
        let text_pos = Point2 {
            x: button.rect.x + (button.rect.w - text_dimensions.x) / 2.0,
            y: button.rect.y + (button.rect.h - text_dimensions.y) / 2.0,
        };
        canvas.draw(&text, text_pos);

        Ok(())
    }
}

impl EventHandler for GameState {
    fn update(&mut self, _ctx: &mut Context) -> GameResult {
        // Verificar si hay cambios en los archivos
        if let Some(rx) = &self.reload_receiver {
            if rx.try_recv().is_ok() {
                println!("¡Detectados cambios! Recargando...");
                // Aquí puedes implementar la lógica de recarga
            }
        }
        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::new(0.15, 0.15, 0.15, 1.0));

        // Dibuja los botones
        self.draw_button(ctx, &mut canvas, &self.create_button)?;
        self.draw_button(ctx, &mut canvas, &self.open_button)?;

        // Dibuja la sección de proyectos recientes
        let text = Text::new(TextFragment::new("Proyectos Recientes").color(Color::WHITE));
        canvas.draw(&text, Point2 { x: 50.0, y: 200.0 });

        if self.recent_projects.is_empty() {
            let no_projects = Text::new(
                TextFragment::new("No hay proyectos recientes")
                    .color(Color::new(0.5, 0.5, 0.5, 1.0)),
            );
            canvas.draw(&no_projects, Point2 { x: 50.0, y: 240.0 });
        } else {
            // Dibujar lista de proyectos recientes
            for (i, project) in self.recent_projects.iter().enumerate() {
                let project_text = Text::new(TextFragment::new(project).color(Color::WHITE));
                canvas.draw(
                    &project_text,
                    Point2 {
                        x: 50.0,
                        y: 240.0 + (i as f32 * 30.0),
                    },
                );
            }
        }

        canvas.finish(ctx)?;
        Ok(())
    }

    fn mouse_button_down_event(
        &mut self,
        _ctx: &mut Context,
        button: MouseButton,
        x: f32,
        y: f32,
    ) -> GameResult {
        if button == MouseButton::Left {
            if self.create_button.is_clicked(x, y) {
                self.create_button.active = !self.create_button.active;
                println!("¡Crear proyecto!");
            }

            if self.open_button.is_clicked(x, y) {
                self.open_button.active = !self.open_button.active;
                if let Some(path) = FileDialog::new()
                    .set_title("Seleccionar proyecto")
                    .set_directory("/")
                    .add_filter("Proyecto Cortex", &["cortex"])
                    .pick_file()
                {
                    println!("Proyecto seleccionado: {:?}", path);
                    self.recent_projects
                        .push(path.to_string_lossy().to_string());
                }
            }
        }
        Ok(())
    }
}
