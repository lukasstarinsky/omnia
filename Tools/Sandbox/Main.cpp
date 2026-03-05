/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Common/Types.h>
#include <LibCore/Window.h>

#include <print>

auto main() -> i32
{
    Core::Window::Configuration const window_config {
        .title = "Omnia Sandbox",
        .width = 800,
        .height = 600
    };
    auto window_optional = Core::Window::create(window_config);
    if (!window_optional.has_value()) {
        std::println(stderr, "Failed to create window: {}", window_optional.error());
        return 1;
    }

    auto window = std::move(window_optional.value());
    while (window->is_running()) {
        window->poll_events();
    }

    return 0;
}
