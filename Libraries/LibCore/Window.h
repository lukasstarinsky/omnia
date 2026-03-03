/*
 *  Copyright (c) 2026, the Omnia developers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Common/Platform.h>

#ifdef OA_OS_WINDOWS
#    include "Win32Window.h"
#elifdef OA_OS_LINUX

#elifdef OA_OS_MACOS

#endif
