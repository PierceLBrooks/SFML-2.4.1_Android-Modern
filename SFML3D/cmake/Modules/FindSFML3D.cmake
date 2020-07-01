# This script locates the SFML3D library
# ------------------------------------
#
# Usage
# -----
#
# When you try to locate the SFML3D libraries, you must specify which modules you want to use (system, window, graphics, network, audio, main).
# If none is given, the SFML3D_LIBRARIES variable will be empty and you'll end up linking to nothing.
# example:
#   find_package(SFML3D COMPONENTS graphics window system) // find the graphics, window and system modules
#
# You can enforce a specific version, either MAJOR.MINOR or only MAJOR.
# If nothing is specified, the version won't be checked (ie. any version will be accepted).
# example:
#   find_package(SFML3D COMPONENTS ...)     // no specific version required
#   find_package(SFML3D 2 COMPONENTS ...)   // any 2.x version
#   find_package(SFML3D 2.4 COMPONENTS ...) // version 2.4 or greater
#
# By default, the dynamic libraries of SFML3D will be found. To find the static ones instead,
# you must set the SFML3D_STATIC_LIBRARIES variable to TRUE before calling find_package(SFML3D ...).
# Since you have to link yourself all the SFML3D dependencies when you link it statically, the following
# additional variables are defined: SFML3D_XXX_DEPENDENCIES and SFML3D_DEPENDENCIES (see their detailed
# description below).
# In case of static linking, the SFML3D_STATIC macro will also be defined by this script.
# example:
#   set(SFML3D_STATIC_LIBRARIES TRUE)
#   find_package(SFML3D 2 COMPONENTS network system)
#
# On Mac OS X if SFML3D_STATIC_LIBRARIES is not set to TRUE then by default CMake will search for frameworks unless
# CMAKE_FIND_FRAMEWORK is set to "NEVER" for example. Please refer to CMake documentation for more details.
# Moreover, keep in mind that SFML3D frameworks are only available as release libraries unlike dylibs which
# are available for both release and debug modes.
#
# If SFML3D is not installed in a standard path, you can use the SFML3D_ROOT CMake (or environment) variable
# to tell CMake where SFML3D is.
#
# Output
# ------
#
# This script defines the following variables:
# - For each specified module XXX (system, window, graphics, network, audio, main):
#   - SFML3D_XXX_LIBRARY_DEBUG:   the name of the debug library of the xxx module (set to SFML3D_XXX_LIBRARY_RELEASE is no debug version is found)
#   - SFML3D_XXX_LIBRARY_RELEASE: the name of the release library of the xxx module (set to SFML3D_XXX_LIBRARY_DEBUG is no release version is found)
#   - SFML3D_XXX_LIBRARY:         the name of the library to link to for the xxx module (includes both debug and optimized names if necessary)
#   - SFML3D_XXX_FOUND:           true if either the debug or release library of the xxx module is found
#   - SFML3D_XXX_DEPENDENCIES:    the list of libraries the module depends on, in case of static linking
# - SFML3D_LIBRARIES:    the list of all libraries corresponding to the required modules
# - SFML3D_FOUND:        true if all the required modules are found
# - SFML3D_INCLUDE_DIR:  the path where SFML3D headers are located (the directory containing the SFML3D/Config.hpp file)
# - SFML3D_DEPENDENCIES: the list of libraries SFML3D depends on, in case of static linking
#
# example:
#   find_package(SFML3D 2 COMPONENTS system window graphics audio REQUIRED)
#   include_directories(${SFML3D_INCLUDE_DIR})
#   add_executable(myapp ...)
#   target_link_libraries(myapp ${SFML3D_LIBRARIES})

# define the SFML3D_STATIC macro if static build was chosen
if(SFML3D_STATIC_LIBRARIES)
    add_definitions(-DSFML3D_STATIC)
endif()

# deduce the libraries suffix from the options
set(FIND_SFML3D_LIB_SUFFIX "")
if(SFML3D_STATIC_LIBRARIES)
    set(FIND_SFML3D_LIB_SUFFIX "${FIND_SFML3D_LIB_SUFFIX}-s")
endif()

# define the list of search paths for headers and libraries
set(FIND_SFML3D_PATHS
    ${SFML3D_ROOT}
    $ENV{SFML3D_ROOT}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt)

# find the SFML3D include directory
find_path(SFML3D_INCLUDE_DIR SFML3D/Config.hpp
          PATH_SUFFIXES include
          PATHS ${FIND_SFML3D_PATHS})

# check the version number
set(SFML3D_VERSION_OK TRUE)
if(SFML3D_FIND_VERSION AND SFML3D_INCLUDE_DIR)
    # extract the major and minor version numbers from SFML3D/Config.hpp
    # we have to handle framework a little bit differently :
    if("${SFML3D_INCLUDE_DIR}" MATCHES "SFML3D.framework")
        set(SFML3D_CONFIG_HPP_INPUT "${SFML3D_INCLUDE_DIR}/Headers/Config.hpp")
    else()
        set(SFML3D_CONFIG_HPP_INPUT "${SFML3D_INCLUDE_DIR}/SFML3D/Config.hpp")
    endif()
    FILE(READ "${SFML3D_CONFIG_HPP_INPUT}" SFML3D_CONFIG_HPP_CONTENTS)
    STRING(REGEX MATCH ".*#define SFML3D_VERSION_MAJOR ([0-9]+).*#define SFML3D_VERSION_MINOR ([0-9]+).*" SFML3D_CONFIG_HPP_CONTENTS "${SFML3D_CONFIG_HPP_CONTENTS}")
    STRING(REGEX REPLACE ".*#define SFML3D_VERSION_MAJOR ([0-9]+).*" "\\1" SFML3D_VERSION_MAJOR "${SFML3D_CONFIG_HPP_CONTENTS}")
    STRING(REGEX REPLACE ".*#define SFML3D_VERSION_MINOR ([0-9]+).*" "\\1" SFML3D_VERSION_MINOR "${SFML3D_CONFIG_HPP_CONTENTS}")
    math(EXPR SFML3D_REQUESTED_VERSION "${SFML3D_FIND_VERSION_MAJOR} * 10 + ${SFML3D_FIND_VERSION_MINOR}")

    # if we could extract them, compare with the requested version number
    if (SFML3D_VERSION_MAJOR)
        # transform version numbers to an integer
        math(EXPR SFML3D_VERSION "${SFML3D_VERSION_MAJOR} * 10 + ${SFML3D_VERSION_MINOR}")

        # compare them
        if(SFML3D_VERSION LESS SFML3D_REQUESTED_VERSION)
            set(SFML3D_VERSION_OK FALSE)
        endif()
    else()
        # SFML3D version is < 2.0
        if (SFML3D_REQUESTED_VERSION GREATER 19)
            set(SFML3D_VERSION_OK FALSE)
            set(SFML3D_VERSION_MAJOR 1)
            set(SFML3D_VERSION_MINOR x)
        endif()
    endif()
endif()

# find the requested modules
set(SFML3D_FOUND TRUE) # will be set to false if one of the required modules is not found
foreach(FIND_SFML3D_COMPONENT ${SFML3D_FIND_COMPONENTS})
    string(TOLOWER ${FIND_SFML3D_COMPONENT} FIND_SFML3D_COMPONENT_LOWER)
    string(TOUPPER ${FIND_SFML3D_COMPONENT} FIND_SFML3D_COMPONENT_UPPER)
    set(FIND_SFML3D_COMPONENT_NAME sfml-${FIND_SFML3D_COMPONENT_LOWER}${FIND_SFML3D_LIB_SUFFIX})

    # no suffix for sfml-main, it is always a static library
    if(FIND_SFML3D_COMPONENT_LOWER STREQUAL "main")
        set(FIND_SFML3D_COMPONENT_NAME sfml-${FIND_SFML3D_COMPONENT_LOWER})
    endif()

    # debug library
    find_library(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG
                 NAMES ${FIND_SFML3D_COMPONENT_NAME}-d
                 PATH_SUFFIXES lib64 lib
                 PATHS ${FIND_SFML3D_PATHS})

    # release library
    find_library(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE
                 NAMES ${FIND_SFML3D_COMPONENT_NAME}
                 PATH_SUFFIXES lib64 lib
                 PATHS ${FIND_SFML3D_PATHS})

    if (SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG OR SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE)
        # library found
        set(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_FOUND TRUE)
        
        # if both are found, set SFML3D_XXX_LIBRARY to contain both
        if (SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG AND SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE)
            set(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY debug     ${SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG}
                                                          optimized ${SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE})
        endif()

        # if only one debug/release variant is found, set the other to be equal to the found one
        if (SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG AND NOT SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE)
            # debug and not release
            set(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE ${SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG})
            set(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY         ${SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG})
        endif()
        if (SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE AND NOT SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG)
            # release and not debug
            set(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG ${SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE})
            set(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY       ${SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE})
        endif()
    else()
        # library not found
        set(SFML3D_FOUND FALSE)
        set(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_FOUND FALSE)
        set(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY "")
        set(FIND_SFML3D_MISSING "${FIND_SFML3D_MISSING} SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY")
    endif()

    # mark as advanced
    MARK_AS_ADVANCED(SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY
                     SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_RELEASE
                     SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY_DEBUG)

    # add to the global list of libraries
    set(SFML3D_LIBRARIES ${SFML3D_LIBRARIES} "${SFML3D_${FIND_SFML3D_COMPONENT_UPPER}_LIBRARY}")
endforeach()

# in case of static linking, we must also define the list of all the dependencies of SFML3D libraries
if(SFML3D_STATIC_LIBRARIES)

    # detect the OS
    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(FIND_SFML3D_OS_WINDOWS 1)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(FIND_SFML3D_OS_LINUX 1)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
        set(FIND_SFML3D_OS_FREEBSD 1)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(FIND_SFML3D_OS_MACOSX 1)
    endif()

    # start with an empty list
    set(SFML3D_DEPENDENCIES)
    set(FIND_SFML3D_DEPENDENCIES_NOTFOUND)

    # macro that searches for a 3rd-party library
    macro(find_sfml3d_dependency output friendlyname)
        find_library(${output} NAMES ${ARGN} PATHS ${FIND_SFML3D_PATHS} PATH_SUFFIXES lib)
        if(${${output}} STREQUAL "${output}-NOTFOUND")
            unset(output)
            set(FIND_SFML3D_DEPENDENCIES_NOTFOUND "${FIND_SFML3D_DEPENDENCIES_NOTFOUND} ${friendlyname}")
        endif()
    endmacro()

    # sfml-system
    list(FIND SFML3D_FIND_COMPONENTS "system" FIND_SFML3D_SYSTEM_COMPONENT)
    if(NOT ${FIND_SFML3D_SYSTEM_COMPONENT} EQUAL -1)

        # update the list -- these are only system libraries, no need to find them
        if(FIND_SFML3D_OS_LINUX OR FIND_SFML3D_OS_FREEBSD OR FIND_SFML3D_OS_MACOSX)
            set(SFML3D_SYSTEM_DEPENDENCIES "pthread")
        endif()
        if(FIND_SFML3D_OS_LINUX)
            set(SFML3D_SYSTEM_DEPENDENCIES "rt")
        endif()
        if(FIND_SFML3D_OS_WINDOWS)
            set(SFML3D_SYSTEM_DEPENDENCIES "winmm")
        endif()
        set(SFML3D_DEPENDENCIES ${SFML3D_DEPENDENCIES} ${SFML3D_SYSTEM_DEPENDENCIES})
    endif()

    # sfml-network
    list(FIND SFML3D_FIND_COMPONENTS "network" FIND_SFML3D_NETWORK_COMPONENT)
    if(NOT ${FIND_SFML3D_NETWORK_COMPONENT} EQUAL -1)

        # update the list -- these are only system libraries, no need to find them
        if(FIND_SFML3D_OS_WINDOWS)
            set(SFML3D_NETWORK_DEPENDENCIES "ws2_32")
        endif()
        set(SFML3D_DEPENDENCIES ${SFML3D_DEPENDENCIES} ${SFML3D_NETWORK_DEPENDENCIES})
    endif()

    # sfml-window
    list(FIND SFML3D_FIND_COMPONENTS "window" FIND_SFML3D_WINDOW_COMPONENT)
    if(NOT ${FIND_SFML3D_WINDOW_COMPONENT} EQUAL -1)

        # find libraries
        if(FIND_SFML3D_OS_LINUX)
            find_sfml3d_dependency(X11_LIBRARY "X11" X11)
            find_sfml3d_dependency(XRANDR_LIBRARY "Xrandr" Xrandr)
        endif()

        # update the list
        if(FIND_SFML3D_OS_WINDOWS)
            set(SFML3D_WINDOW_DEPENDENCIES ${SFML3D_WINDOW_DEPENDENCIES} "opengl32" "winmm" "gdi32")
        elseif(FIND_SFML3D_OS_LINUX OR FIND_SFML3D_OS_FREEBSD)
            set(SFML3D_WINDOW_DEPENDENCIES ${SFML3D_WINDOW_DEPENDENCIES} "GL" ${X11_LIBRARY} ${XRANDR_LIBRARY})
            if(FIND_SFML3D_OS_FREEBSD)
                set(SFML3D_WINDOW_DEPENDENCIES ${SFML3D_WINDOW_DEPENDENCIES} "usbhid")
            endif()
        elseif(FIND_SFML3D_OS_MACOSX)
            set(SFML3D_WINDOW_DEPENDENCIES ${SFML3D_WINDOW_DEPENDENCIES} "GL" "-framework Foundation -framework AppKit -framework IOKit -framework Carbon")
        endif()
        set(SFML3D_DEPENDENCIES ${SFML3D_DEPENDENCIES} ${SFML3D_WINDOW_DEPENDENCIES})
    endif()

    # sfml-graphics
    list(FIND SFML3D_FIND_COMPONENTS "graphics" FIND_SFML3D_GRAPHICS_COMPONENT)
    if(NOT ${FIND_SFML3D_GRAPHICS_COMPONENT} EQUAL -1)
    
        # find libraries
        find_sfml3d_dependency(FREETYPE_LIBRARY "FreeType" freetype)
        find_sfml3d_dependency(GLEW_LIBRARY "GLEW" glew GLEW glew32 glew32s glew64 glew64s)
        find_sfml3d_dependency(JPEG_LIBRARY "libjpeg" jpeg)

        # update the list
        set(SFML3D_GRAPHICS_DEPENDENCIES ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${JPEG_LIBRARY})
        set(SFML3D_DEPENDENCIES ${SFML3D_DEPENDENCIES} ${SFML3D_GRAPHICS_DEPENDENCIES})
    endif()

    # sfml-audio
    list(FIND SFML3D_FIND_COMPONENTS "audio" FIND_SFML3D_AUDIO_COMPONENT)
    if(NOT ${FIND_SFML3D_AUDIO_COMPONENT} EQUAL -1)

        # find libraries
        find_sfml3d_dependency(OPENAL_LIBRARY "OpenAL" openal openal32)
        find_sfml3d_dependency(SNDFILE_LIBRARY "libsndfile" sndfile)

        # update the list
        set(SFML3D_AUDIO_DEPENDENCIES ${OPENAL_LIBRARY} ${SNDFILE_LIBRARY})
        set(SFML3D_DEPENDENCIES ${SFML3D_DEPENDENCIES} ${SFML3D_AUDIO_DEPENDENCIES})
    endif()

endif()

# handle errors
if(NOT SFML3D_VERSION_OK)
    # SFML3D version not ok
    set(FIND_SFML3D_ERROR "SFML3D found but version too low (requested: ${SFML3D_FIND_VERSION}, found: ${SFML3D_VERSION_MAJOR}.${SFML3D_VERSION_MINOR})")
    set(SFML3D_FOUND FALSE)
elseif(SFML3D_STATIC_LIBRARIES AND FIND_SFML3D_DEPENDENCIES_NOTFOUND)
    set(FIND_SFML3D_ERROR "SFML3D found but some of its dependencies are missing (${FIND_SFML3D_DEPENDENCIES_NOTFOUND})")
    set(SFML3D_FOUND FALSE)
elseif(NOT SFML3D_FOUND)
    # include directory or library not found
    set(FIND_SFML3D_ERROR "Could NOT find SFML3D (missing: ${FIND_SFML3D_MISSING})")
endif()
if (NOT SFML3D_FOUND)
    if(SFML3D_FIND_REQUIRED)
        # fatal error
        message(FATAL_ERROR ${FIND_SFML3D_ERROR})
    elseif(NOT SFML3D_FIND_QUIETLY)
        # error but continue
        message("${FIND_SFML3D_ERROR}")
    endif()
endif()

# handle success
if(SFML3D_FOUND)
    message(STATUS "Found SFML3D ${SFML3D_VERSION_MAJOR}.${SFML3D_VERSION_MINOR} in ${SFML3D_INCLUDE_DIR}")
endif()
