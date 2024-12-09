use ggez::{conf, event, ContextBuilder, GameResult};

mod core;
mod domain;
mod game;
mod infrastructure;
mod presentation;
mod utils;

use game::state::GameState;

fn main() -> GameResult {
    let cb = ContextBuilder::new("cortex_engine", "yo")
        .window_setup(conf::WindowSetup::default().title("Cortex Engine"))
        .window_mode(
            conf::WindowMode::default()
                .dimensions(800.0, 600.0)
                .resizable(true)
                .min_dimensions(400.0, 300.0),
        );

    let (ctx, event_loop) = cb.build()?;
    let state = GameState::new();
    event::run(ctx, event_loop, state)
}
