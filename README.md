# Cortex Engine

Cortex Engine es un motor de juegos 2D desarrollado en Rust, utilizando GGEZ como framework base.

## 🚀 Características

- 🎮 Motor de juegos 2D
- 🔄 Hot Reload integrado
- 🎨 Interfaz gráfica estilo Godot
- 📁 Gestión de proyectos
- 🔍 Explorador de archivos nativo
- 📋 Lista de proyectos recientes

## 🛠️ Requisitos previos

- Rust (última versión estable)
- Cargo (incluido con Rust)
- Dependencias del sistema para GGEZ:
  - Linux: `libasound2-dev pkg-config`
  - Windows: No requiere dependencias adicionales
  - macOS: No requiere dependencias adicionales

## 📥 Instalación

1. Clona el repositorio:

```
git clone https://github.com/tu-usuario/cortex_engine.git
cd cortex_engine
```

2. Compila el proyecto:

```bash
cargo build --release
```

## 🎮 Uso

Para ejecutar el motor:

```bash
cargo run
```

Para desarrollo con hot reload:

```bash
cargo watch -x run
```

## 🔧 Desarrollo

El proyecto está estructurado de la siguiente manera:

```
src/
├── main.rs           # Punto de entrada
├── game/
│   ├── mod.rs       # Módulo del juego
│   ├── state.rs     # Estado del juego
│   └── button.rs    # Componente de botón
└── utils/
    ├── mod.rs       # Utilidades
    └── hot_reload.rs # Sistema de hot reload
```

## 🤝 Contribuir

1. Haz fork del proyecto
2. Crea una rama para tu característica (`git checkout -b feature/AmazingFeature`)
3. Haz commit de tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## 📝 Licencia

Este proyecto está bajo la Licencia MIT - ver el archivo [LICENSE](LICENSE) para más detalles.

## 🙋‍♂️ Autor

cesardev31 - [@cesardev31](https://twitter.com/cesardev31)

## 🙏 Agradecimientos

- [GGEZ](https://ggez.rs/) - Framework de juegos
