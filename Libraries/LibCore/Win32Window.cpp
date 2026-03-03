/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Win32Window.h"

#include <print>

namespace Core {

Window::Window()
{
    std::println("Hello World!");
}

Window::~Window()
{
    std::println("Goodbye World!");
}

}
