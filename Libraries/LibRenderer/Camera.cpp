/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibRenderer/Camera.h>

namespace Renderer {

Camera::Camera(Configuration const& config)
    : m_config(config)
{
    if (m_config.projection_type == ProjectionType::Perspective) {
        auto const& perspective = m_config.perspective;
        m_projection = Math::Mat4f::perspective(DEG_TO_RAD(perspective.field_of_view_degrees), perspective.aspect_ratio, perspective.near_plane, perspective.far_plane);
        m_view = Math::Mat4f::look_at(m_config.position, m_config.look_at, m_config.up);
    } else {
    }
}

auto Camera::projection() const -> Math::Mat4f
{
    return m_projection;
}

auto Camera::view() const -> Math::Mat4f
{
    return m_view;
}

void Camera::translate(Math::Vec3f const& translation)
{
    m_config.position += translation;
    m_view = Math::Mat4f::look_at(m_config.position, m_config.position + m_config.look_at, m_config.up);
}

void Camera::set_aspect_ratio(f32 aspect_ratio)
{
    if (m_config.projection_type == ProjectionType::Perspective) {
        auto& perspective = m_config.perspective;
        perspective.aspect_ratio = aspect_ratio;
        m_projection = Math::Mat4f::perspective(DEG_TO_RAD(perspective.field_of_view_degrees), perspective.aspect_ratio, perspective.near_plane, perspective.far_plane);
    }
}

}
