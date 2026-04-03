/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "VkDevice.h"
#include "VkBuffer.h"
#include "VkShader.h"
#include "VkSwapchain.h"
#include "VkTexture.h"
#ifdef OA_OS_WINDOWS
#   include <LibUI/Platform/Win32/WindowWin32.h>
#endif

#include <format>
#include <vector>

namespace RHI {

auto VkDevice::create(Configuration const& config) -> std::expected<std::unique_ptr<VkDevice>, std::string>
{
    std::unique_ptr<VkDevice> device(new VkDevice);

    VkApplicationInfo const app_info {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .pApplicationName = "Omnia App",
        .applicationVersion = VK_MAKE_VERSION(0, 1, 0),
        .pEngineName = "Omnia Engine",
        .engineVersion = VK_MAKE_VERSION(0, 1, 0),
        .apiVersion = VK_API_VERSION_1_3,
    };

    std::vector<char const*> const required_extensions {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_PLATFORM_SURFACE_EXTENSION_NAME,
    };

    VkInstanceCreateInfo const instance_info {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .pApplicationInfo = &app_info,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = static_cast<uint32_t>(required_extensions.size()),
        .ppEnabledExtensionNames = required_extensions.data(),
    };

    if (auto result = vkCreateInstance(&instance_info, nullptr, &device->m_instance); result != VK_SUCCESS) {
        return std::unexpected(std::format("Failed to create Vulkan instance: {}", string_VkResult(result)));
    }

#ifdef OA_OS_WINDOWS
    auto const* window = static_cast<UI::WindowWin32 const*>(config.window);

    VkWin32SurfaceCreateInfoKHR const surface_info {
        .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .hinstance = window->instance(),
        .hwnd = window->handle()
    };

    if (auto result = vkCreateWin32SurfaceKHR(device->m_instance, &surface_info, nullptr, &device->m_surface); result != VK_SUCCESS) {
        return std::unexpected(std::format("Failed to create Vulkan surface: {}", string_VkResult(result)));
    }
#endif

    return device;
}

VkDevice::~VkDevice()
{
    vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
    vkDestroyInstance(m_instance, nullptr);
}

auto VkDevice::create_buffer(Buffer::Configuration const& config) const -> std::expected<std::unique_ptr<Buffer>, std::string>
{
    return VkBuffer::create(config);
}

auto VkDevice::create_shader(Shader::Configuration const& config) const -> std::expected<std::unique_ptr<Shader>, std::string>
{
    return VkShader::create(config);
}

auto VkDevice::create_swapchain(Swapchain::Configuration const& config) const -> std::expected<std::unique_ptr<Swapchain>, std::string>
{
    return VkSwapchain::create(config);
}

auto VkDevice::create_texture(Texture::Configuration const& config) const -> std::expected<std::unique_ptr<Texture>, std::string>
{
    return VkTexture::create(config);
}

}
