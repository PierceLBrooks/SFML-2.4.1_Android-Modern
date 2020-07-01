////////////////////////////////////////////////////////////
//
// SFML3D - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)
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

#ifndef SFML3D_RENDERTEXTUREIMPL_HPP
#define SFML3D_RENDERTEXTUREIMPL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML3D/System/NonCopyable.hpp>


namespace sf3d
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Abstract base class for render-texture implementations
///
////////////////////////////////////////////////////////////
class RenderTextureImpl : NonCopyable
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~RenderTextureImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Create the render texture implementation
    ///
    /// \param width         Width of the texture to render to
    /// \param height        Height of the texture to render to
    /// \param textureId     OpenGL identifier of the target texture
    /// \param depthBuffer   Is a depth buffer requested?
    /// \param stencilBuffer Is a stencil buffer requested?
    ///
    /// \return True if creation has been successful
    ///
    ////////////////////////////////////////////////////////////
    virtual bool create(unsigned int width, unsigned int height, unsigned int textureId, bool depthBuffer, bool stencilBuffer) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Activate or deactivate the render texture for rendering
    ///
    /// \param active True to activate, false to deactivate
    ///
    /// \return True on success, false on failure
    ///
    ////////////////////////////////////////////////////////////
    virtual bool activate(bool active) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Update the pixels of the target texture
    ///
    /// \param textureId OpenGL identifier of the target texture
    ///
    ////////////////////////////////////////////////////////////
    virtual void updateTexture(unsigned int textureId) = 0;
};

} // namespace priv

} // namespace sf3d


#endif // SFML3D_RENDERTEXTUREIMPL_HPP