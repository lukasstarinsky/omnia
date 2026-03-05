/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Noncopyable.h>
#include <Common/Types.h>
#include <LibCore/Window.h>

#include <expected>
#include <memory>
#include <string>

struct HWND__;
struct HINSTANCE__;

using HWND = HWND__*;
using HINSTANCE = HINSTANCE__*;

namespace Core {

class Win32Window final : public Window {
    OA_MAKE_NONCOPYABLE(Win32Window);
    OA_MAKE_NONMOVABLE(Win32Window);

public:
    ~Win32Window() override;

    void poll_events() override;
    auto is_running() const -> bool override;
    auto title() const -> std::string const& override;
    auto width() const -> i32 override;
    auto height() const -> i32 override;

    static auto create(Configuration const& config) -> std::expected<std::unique_ptr<Win32Window>, std::string>;
private:
    Win32Window() = default;

    static auto window_procedure(HWND window_handle, u32 message, u64 first_param, i64 second_param) -> i64;
    auto handle_message(u32 message, u64 first_param, i64 second_param) -> bool;
private:
    HWND m_handle {};
    HINSTANCE m_instance {};
    bool m_is_running = true;
    Configuration m_config {};
};

}
