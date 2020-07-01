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

#ifndef SFML3D_THREADLOCAL_HPP
#define SFML3D_THREADLOCAL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML3D/System/Export.hpp>
#include <SFML3D/System/NonCopyable.hpp>
#include <cstdlib>


namespace sf3d
{
namespace priv
{
    class ThreadLocalImpl;
}

////////////////////////////////////////////////////////////
/// \brief Defines variables with thread-local storage
///
////////////////////////////////////////////////////////////
class SFML3D_SYSTEM_API ThreadLocal : NonCopyable
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param value Optional value to initalize the variable
    ///
    ////////////////////////////////////////////////////////////
    ThreadLocal(void* value = NULL);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~ThreadLocal();

    ////////////////////////////////////////////////////////////
    /// \brief Set the thread-specific value of the variable
    ///
    /// \param value Value of the variable for the current thread
    ///
    ////////////////////////////////////////////////////////////
    void setValue(void* value);

    ////////////////////////////////////////////////////////////
    /// \brief Retrieve the thread-specific value of the variable
    ///
    /// \return Value of the variable for the current thread
    ///
    ////////////////////////////////////////////////////////////
    void* getValue() const;

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    priv::ThreadLocalImpl* m_impl; ///< Pointer to the OS specific implementation
};

} // namespace sf3d


#endif // SFML3D_THREADLOCAL_HPP


////////////////////////////////////////////////////////////
/// \class sf3d::ThreadLocal
/// \ingroup system
///
/// This class manipulates void* parameters and thus is not
/// appropriate for strongly-typed variables. You should rather
/// use the sf3d::ThreadLocalPtr template class.
///
////////////////////////////////////////////////////////////
