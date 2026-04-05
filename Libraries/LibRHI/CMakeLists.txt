set(SOURCES
        Device.cpp

        Vulkan/VkBuffer.cpp
        Vulkan/VkDevice.cpp
        Vulkan/VkPhysicalDevice.cpp
        Vulkan/VkShader.cpp
        Vulkan/VkSwapchain.cpp
        Vulkan/VkTexture.cpp

        Metal/MTLBuffer.cpp
        Metal/MTLDevice.cpp
        Metal/MTLShader.cpp
        Metal/MTLSwapchain.cpp
        Metal/MTLTexture.cpp

        D3D12/DX12Buffer.cpp
        D3D12/DX12Device.cpp
        D3D12/DX12Shader.cpp
        D3D12/DX12Swapchain.cpp
        D3D12/DX12Texture.cpp
)

find_package(Vulkan REQUIRED)

if (WIN32)
    add_compile_definitions(VK_USE_PLATFORM_WIN32_KHR)
endif()

omnia_lib(LibRHI
        SOURCES ${SOURCES}
        LIBS LibUI
        THIRD_PARTY PRIVATE Vulkan::Vulkan
)
