use std::collections::HashMap;
use std::path::PathBuf;

pub struct AssetManager {
    textures: HashMap<String, Texture>,
    sounds: HashMap<String, Sound>,
    fonts: HashMap<String, Font>,
}

impl AssetManager {
    pub fn new() -> Self {
        Self {
            textures: HashMap::new(),
            sounds: HashMap::new(),
            fonts: HashMap::new(),
        }
    }

    pub fn load_texture(&mut self, id: &str, path: PathBuf) -> Result<(), AssetError> {
        let texture = Texture::load(path)?;
        self.textures.insert(id.to_string(), texture);
        Ok(())
    }

    pub fn get_texture(&self, id: &str) -> Option<&Texture> {
        self.textures.get(id)
    }
}
