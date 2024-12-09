#[derive(Debug)]
pub struct Transform {
    pub position: Vector2,
    pub rotation: f32,
    pub scale: Vector2,
}

#[derive(Debug)]
pub struct Sprite {
    pub texture_id: String,
    pub width: f32,
    pub height: f32,
}

#[derive(Debug)]
pub struct Physics {
    pub velocity: Vector2,
    pub acceleration: Vector2,
    pub mass: f32,
}
