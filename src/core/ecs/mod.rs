use std::any::{Any, TypeId};
use std::collections::HashMap;

pub type EntityId = u64;

pub struct World {
    entities: HashMap<EntityId, Entity>,
    next_entity_id: EntityId,
}

pub struct Entity {
    id: EntityId,
    components: HashMap<TypeId, Box<dyn Any>>,
}

impl World {
    pub fn new() -> Self {
        Self {
            entities: HashMap::new(),
            next_entity_id: 0,
        }
    }

    pub fn create_entity(&mut self) -> EntityId {
        let entity_id = self.next_entity_id;
        self.next_entity_id += 1;

        let entity = Entity {
            id: entity_id,
            components: HashMap::new(),
        };

        self.entities.insert(entity_id, entity);
        entity_id
    }

    pub fn add_component<T: 'static>(&mut self, entity_id: EntityId, component: T) {
        if let Some(entity) = self.entities.get_mut(&entity_id) {
            entity
                .components
                .insert(TypeId::of::<T>(), Box::new(component));
        }
    }

    pub fn get_component<T: 'static>(&self, entity_id: EntityId) -> Option<&T> {
        self.entities
            .get(&entity_id)
            .and_then(|entity| entity.components.get(&TypeId::of::<T>()))
            .and_then(|component| component.downcast_ref::<T>())
    }
}
