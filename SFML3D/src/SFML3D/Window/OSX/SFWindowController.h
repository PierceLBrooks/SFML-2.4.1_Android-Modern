////////////////////////////////////////////////////////////
//
// SFML3D - Simple and Fast Multimedia Library
// Copyright (C) 2007-2016 Marco Antognini (antognini.marco@gmail.com),
//                         Laurent Gomila (laurent@sfml-dev.org)
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
#include <SFML3D/Window/VideoMode.hpp>

#import <SFML3D/Window/OSX/WindowImplDelegateProtocol.h>

////////////////////////////////////////////////////////////
/// Predefine some classes
////////////////////////////////////////////////////////////
namespace sf3d {
    namespace priv {
        class WindowImplCocoa;
    }
}

@class SFOpenGLView;

////////////////////////////////////////////////////////////
/// \brief Implementation of WindowImplDelegateProtocol for window management
///
/// Key, mouse and Window focus events are delegated to its view, SFOpenGLView.
///
/// Used when SFML3D handle everything and when a NSWindow* is given
/// as handle to WindowImpl.
///
/// When grabbing the cursor, if the window is resizeable, m_restoreResize is
/// set to YES and the window is marked as not resizeable. This is to prevent
/// accidental resize by the user. When the cursor is released, the window
/// style is restored.
///
////////////////////////////////////////////////////////////
@interface SFWindowController : NSResponder <WindowImplDelegateProtocol, NSWindowDelegate>
{
    NSWindow*                   m_window;           ///< Underlying Cocoa window to be controlled
    SFOpenGLView*               m_oglView;          ///< OpenGL view for rendering
    sf3d::priv::WindowImplCocoa*  m_requester;        ///< Requester
    BOOL                        m_fullscreen;       ///< Indicate whether the window is fullscreen or not
    BOOL                        m_restoreResize;    ///< See note above
}

////////////////////////////////////////////////////////////
/// \brief Create the SFML3D window with an external Cocoa window
///
/// \param window Cocoa window to be controlled
///
/// \return an initialized controller
///
////////////////////////////////////////////////////////////
-(id)initWithWindow:(NSWindow*)window;

////////////////////////////////////////////////////////////
/// \brief Create the SFML3D window "from scratch" (SFML3D handle everything)
///
/// \param mode Video mode
/// \param style Window's style, as described by sf3d::Style
///
/// \return an initialized controller
///
////////////////////////////////////////////////////////////
-(id)initWithMode:(const sf3d::VideoMode&)mode andStyle:(unsigned long)style;

@end
