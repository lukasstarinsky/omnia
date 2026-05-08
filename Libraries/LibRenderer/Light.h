/*
*  Copyright (c) 2026, the Omnia developers
*
* SPDX-License-Identifier: BSD-2-Clause
*/

#pragma once

#include <LibMath/Vec3.h>

namespace Renderer {

struct DirectionalLight {
    Math::Vec3f direction;
    f32 pad {};
    Math::Vec3f color;
    f32 intensity = 1.0F;
};

}