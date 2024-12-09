use ggez::graphics::Rect;

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
}
