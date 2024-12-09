use ggez::audio::Source;
use ggez::graphics::Image;
use ggez::Context;
use std::collections::HashMap;
use std::path::PathBuf;

pub struct AssetManager {
    textures: HashMap<String, Image>,
    sounds: HashMap<String, Source>,
    base_path: PathBuf,
}

impl AssetManager {
    pub fn new() -> Self {
        Self {
            textures: HashMap::new(),
            sounds: HashMap::new(),
            base_path: PathBuf::from("assets"),
        }
    }

    pub fn load_texture(
        &mut self,
        ctx: &mut Context,
        id: &str,
        path: &str,
    ) -> ggez::GameResult<()> {
        let full_path = self.base_path.join(path);
        let texture = Image::from_path(ctx, full_path)?;
        self.textures.insert(id.to_string(), texture);
        Ok(())
    }

    pub fn get_texture(&self, id: &str) -> Option<&Image> {
        self.textures.get(id)
    }
}
