////////////////////////////////////////////////////////////
//
// SFML3D - Simple and Fast Multimedia Library
// Copyright (C) 2007-2016 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML3D_INPUTIMPL_HPP
#define SFML3D_INPUTIMPL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML3D/Config.hpp>

#if defined(SFML3D_SYSTEM_WINDOWS)
    #include <SFML3D/Window/Win32/InputImpl.hpp>
#elif defined(SFML3D_SYSTEM_LINUX) || defined(SFML3D_SYSTEM_FREEBSD)
    #include <SFML3D/Window/Unix/InputImpl.hpp>
#elif defined(SFML3D_SYSTEM_MACOS)
    #include <SFML3D/Window/OSX/InputImpl.hpp>
#elif defined(SFML3D_SYSTEM_IOS)
    #include <SFML3D/Window/iOS/InputImpl.hpp>
#elif defined(SFML3D_SYSTEM_ANDROID)
    #include <SFML3D/Window/Android/InputImpl.hpp>
#endif


#endif // SFML3D_INPUTIMPL_HPP
