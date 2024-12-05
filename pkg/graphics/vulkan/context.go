package renderer

import (
	"fmt"
	"log"

	"github.com/vulkan-go/vulkan"
)

type VulkanContext struct {
	Instance vulkan.Instance
}

func NewVulkanContext() *VulkanContext {
	ctx := &VulkanContext{}
	if err := ctx.initVulkan(); err != nil {
		log.Fatalf("Error inicializando Vulkan: %v", err)
	}
	return ctx
}

func (ctx *VulkanContext) initVulkan() error {
	// Inicializar Vulkan
	if err := vulkan.SetDefaultGetInstanceProcAddr(); err != nil {
		return fmt.Errorf("fallo al configurar el proc addr por defecto: %v", err)
	}
	vulkan.Init()

	// Crear instancia de Vulkan
	appInfo := vulkan.ApplicationInfo{
		SType:              vulkan.StructureTypeApplicationInfo,
		PApplicationName:   "Go Vulkan Engine\x00",
		ApplicationVersion: vulkan.MakeVersion(1, 0, 0),
		PEngineName:        "Game Engine\x00",
		EngineVersion:      vulkan.MakeVersion(1, 0, 0),
		ApiVersion:         vulkan.MakeVersion(1, 3, 0),
	}

	createInfo := vulkan.InstanceCreateInfo{
		SType:            vulkan.StructureTypeInstanceCreateInfo,
		PApplicationInfo: &appInfo,
	}

	var instance vulkan.Instance
	if result := vulkan.CreateInstance(&createInfo, nil, &instance); result != vulkan.Success {
		return fmt.Errorf("fallo al crear la instancia de Vulkan: %v", result)
	}

	ctx.Instance = instance
	fmt.Println("Instancia Vulkan creada correctamente")
	return nil
}

func (ctx *VulkanContext) Destroy() {
	if ctx.Instance != nil {
		//vulkan.DestroyInstance(ctx.Instance, nil)
		fmt.Println("Instancia Vulkan destruida correctamente")
	}
}
