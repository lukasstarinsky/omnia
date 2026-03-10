/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Common/Types.h>
#include <LibCore/Input.h>
#include <LibCore/Window.h>

#include <print>

class SandboxTesting final : public Core::Input::Listener {
public:
    SandboxTesting()
    {
        Core::Window::Configuration const window_config {
            .title = "Omnia Sandbox",
            .width = 800,
            .height = 600
        };
        auto window_ = Core::Window::create(window_config);
        if (!window_.has_value()) {
            std::println(stderr, "Failed to create window: {}", window_.error());
            return;
        }

        m_window = std::move(window_.value());
        m_window->input().add_listener(this);
    }

    void run()
    {
        while (m_window->is_running()) {
            if (m_window->input().is_key_down(Core::Input::Key::F10)) {
                std::println("Input polling: F10 is down!");
            }

            if (m_window->input().is_mouse_button_down(Core::Input::MouseButton::Left)) {
                std::println("Input polling: Left mouse button is down!");
            }

            m_window->poll_events();
        }
    }

    auto on_key_pressed(Core::Input::Key key) -> bool override
    {
        std::println("Sandbox Testing: Key pressed: {}", static_cast<u8>(key));
        return false;
    }

    auto on_key_released(Core::Input::Key key) -> bool override
    {
        std::println("Sandbox Testing: Key released: {}", static_cast<u8>(key));
        return false;
    }

    auto on_mouse_button_pressed(Core::Input::MouseButton button, Math::Vec2i const& /*unused*/) -> bool override
    {
        std::println("Sandbox Testing: Mouse button pressed: {}", static_cast<u8>(button));
        return false;
    }

    auto on_mouse_button_released(Core::Input::MouseButton button, Math::Vec2i const& /*unused*/) -> bool override
    {
        std::println("Sandbox Testing: Mouse button released: {}", static_cast<u8>(button));
        return false;
    }

    auto on_mouse_move(Math::Vec2i const& /*position*/) -> bool override
    {
//        std::println("Sandbox Testing: Mouse moved: ({}, {})", position.x, position.y);
        return false;
    }

    auto on_mouse_delta(Math::Vec2i const& /*delta*/) -> bool override
    {
//        std::println("Sandbox Testing: Mouse delta: ({}, {})", delta.x, delta.y);
        return false;
    }
private:
    std::unique_ptr<Core::Window> m_window {};
};

auto main() -> i32
{
    SandboxTesting sandbox {};
    sandbox.run();

    return 0;
}
