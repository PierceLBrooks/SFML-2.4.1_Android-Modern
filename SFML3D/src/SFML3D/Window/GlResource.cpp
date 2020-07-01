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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML3D/Window/GlResource.hpp>
#include <SFML3D/Window/GlContext.hpp>
#include <SFML3D/Window/Context.hpp>
#include <SFML3D/System/Mutex.hpp>
#include <SFML3D/System/Lock.hpp>


namespace
{
    // OpenGL resources counter and its mutex
    unsigned int count = 0;
    sf3d::Mutex mutex;
}


namespace sf3d
{
////////////////////////////////////////////////////////////
GlResource::GlResource()
{
    // Protect from concurrent access
    Lock lock(mutex);

    // If this is the very first resource, trigger the global context initialization
    if (count == 0)
        priv::GlContext::globalInit();

    // Increment the resources counter
    count++;
}


////////////////////////////////////////////////////////////
GlResource::~GlResource()
{
    // Protect from concurrent access
    Lock lock(mutex);

    // Decrement the resources counter
    count--;

    // If there's no more resource alive, we can trigger the global context cleanup
    if (count == 0)
        priv::GlContext::globalCleanup();
}


////////////////////////////////////////////////////////////
void GlResource::ensureGlContext()
{
    // Empty function for ABI compatibility, use acquireTransientContext instead
}


////////////////////////////////////////////////////////////
GlResource::TransientContextLock::TransientContextLock() :
m_context(0)
{
    Lock lock(mutex);

    if (count == 0)
    {
        m_context = new Context;
        return;
    }

    priv::GlContext::acquireTransientContext();
}


////////////////////////////////////////////////////////////
GlResource::TransientContextLock::~TransientContextLock()
{
    if (m_context)
    {
        delete m_context;
        return;
    }

    priv::GlContext::releaseTransientContext();
}

} // namespace sf3d
