# Cortex Engine

Cortex Engine es un proyecto de código abierto personal, nacido como un pasatiempo y reto de aprendizaje para comprender mejor el lenguaje Go y el desarrollo de motores de juego. Este motor está siendo desarrollado de manera incremental, combinando el proceso de aprendizaje con la implementación de características modernas de renderizado.

## Acerca del Proyecto

Este proyecto comenzó como una iniciativa personal para:

- Profundizar en el entendimiento de Go y sus capacidades
- Explorar la arquitectura de motores de juego modernos
- Aprender sobre sistemas de renderizado como OpenGL y Vulkan
- Compartir el proceso de aprendizaje con la comunidad

## Características

- **Renderizado Multiplataforma**: Soporte para OpenGL y Vulkan, permitiendo flexibilidad y rendimiento en diferentes plataformas.
- **Interfaz de Usuario Intuitiva**: Herramientas de UI integradas para facilitar la creación de menús y HUDs.
- **Sistema de Base de Datos**: Gestión eficiente de datos para almacenar y recuperar información del juego.
- **Arquitectura Modular**: Componentes desacoplados que permiten una fácil extensión y personalización.
- **Shaders Personalizables**: Incluye shaders básicos y soporte para crear shaders personalizados.

## Requisitos Previos

- Go 1.20 o superior
- OpenGL compatible con tu sistema
- Vulkan SDK (opcional)

## Instalación

1. Clona el repositorio:

   ```bash
   git clone https://github.com/tu_usuario/cortex_engine.git
   ```

2. Navega al directorio del proyecto:

   ```bash
   cd cortex_engine
   ```

3. Instala las dependencias:
   ```bash
   go mod tidy
   ```

## Uso

### Desarrollo con Hot Reload

El proyecto incluye configuración para Air, que permite hot-reload durante el desarrollo:

1. Instala Air (si no lo tienes):

   ```bash
   go install github.com/cosmtrek/air@latest
   ```

2. Ejecuta el proyecto con Air:
   ```bash
   air
   ```

### Ejecución Normal

Para ejecutar el proyecto sin hot-reload:

```bash
go run cmd/main.go
```

## Estructura del Proyecto

```
cortex_engine/
├── assets/           # Recursos gráficos y multimedia
├── cmd/             # Punto de entrada de la aplicación
├── internal/        # Código interno del motor
├── pkg/             # Paquetes públicos
│   ├── core/        # Funcionalidades principales
│   ├── graphics/    # Sistemas de renderizado
│   └── ui/          # Componentes de interfaz
└── .air.toml        # Configuración para desarrollo
```

## Estado Actual

Este es un proyecto en desarrollo activo que evoluciona según mi tiempo disponible y proceso de aprendizaje. Las características se implementan de manera incremental, priorizando la calidad del código y la comprensión profunda de cada componente.

## Contribuciones

¡Las contribuciones y sugerencias son bienvenidas! Este proyecto es una oportunidad de aprendizaje colaborativo. Si estás interesado en el desarrollo de motores de juego o quieres aprender Go, no dudes en:

1. Abrir issues con preguntas o sugerencias
2. Proponer mejoras mediante pull requests
3. Compartir conocimientos y experiencias
4. Fork el proyecto para tu propio aprendizaje

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - ver el archivo [LICENSE](LICENSE) para más detalles.

## Topics

- Game Engine
- OpenGL
- Vulkan
- Graphics
- Go
- GUI
- Modular Architecture
- Game Development
  El proyecto incluye configuración para Air, que permite hot-reload durante el desarrollo:
