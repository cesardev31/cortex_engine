use std::any::{Any, TypeId};
use std::collections::HashMap;

pub type EventCallback = Box<dyn Fn(&dyn Any) + 'static>;

pub struct EventSystem {
    listeners: HashMap<TypeId, Vec<EventCallback>>,
}

impl EventSystem {
    pub fn new() -> Self {
        Self {
            listeners: HashMap::new(),
        }
    }

    pub fn subscribe<T: 'static>(&mut self, callback: impl Fn(&T) + 'static) {
        let type_id = TypeId::of::<T>();
        let callback = Box::new(move |event: &dyn Any| {
            if let Some(event) = event.downcast_ref::<T>() {
                callback(event);
            }
        });

        self.listeners
            .entry(type_id)
            .or_insert_with(Vec::new)
            .push(callback);
    }

    pub fn emit<T: 'static>(&self, event: T) {
        if let Some(callbacks) = self.listeners.get(&TypeId::of::<T>()) {
            for callback in callbacks {
                callback(&event);
            }
        }
    }
}
