/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibRHI/D3D12/DX12Swapchain.h>

namespace RHI {

auto DX12Swapchain::create(Configuration const& config) -> std::expected<std::unique_ptr<DX12Swapchain>, std::string>
{
    (void)config;
    std::unique_ptr<DX12Swapchain> swapchain(new DX12Swapchain);
    return swapchain;
}

DX12Swapchain::~DX12Swapchain()
{
}

auto DX12Swapchain::width() const -> u32
{
    return 0;
}

auto DX12Swapchain::height() const -> u32
{
    return 0;
}

auto DX12Swapchain::format() const -> Graphics::TextureFormat
{
    return Graphics::TextureFormat::Unknown;
}

auto DX12Swapchain::textures() const -> std::vector<std::unique_ptr<Texture>> const&
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-stack-address"
    return {};
#pragma GCC diagnostic pop
}

auto DX12Swapchain::is_dirty() const -> bool
{
    return false;
}

auto DX12Swapchain::recreate(const RHI::Swapchain::Configuration& config) -> std::expected<void, std::string>
{
    (void)config;
    return {};
}

void DX12Swapchain::wait_idle() const
{
}

auto DX12Swapchain::begin_frame() -> std::optional<Frame>
{
    return {};
}

void DX12Swapchain::end_frame(Frame const& frame)
{
    (void)frame;
}

}
