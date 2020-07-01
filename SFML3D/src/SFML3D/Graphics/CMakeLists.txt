
set(INCROOT ${PROJECT_SOURCE_DIR}/include/SFML3D/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/SFML3D/Graphics)

# all source files
set(SRC
    ${INCROOT}/BlendMode.hpp
    ${INCROOT}/Box.hpp
    ${INCROOT}/Box.inl
    ${SRCROOT}/Camera.cpp
    ${INCROOT}/Camera.hpp
    ${SRCROOT}/Color.cpp
    ${INCROOT}/Color.hpp
    ${INCROOT}/Export.hpp
    ${SRCROOT}/Font.cpp
    ${INCROOT}/Font.hpp
    ${INCROOT}/Glyph.hpp
    ${SRCROOT}/GLCheck.cpp
    ${SRCROOT}/GLCheck.hpp
    ${SRCROOT}/Image.cpp
    ${INCROOT}/Image.hpp
    ${SRCROOT}/ImageLoader.cpp
    ${SRCROOT}/ImageLoader.hpp
    ${SRCROOT}/Light.cpp
    ${INCROOT}/Light.hpp
    ${INCROOT}/PrimitiveType.hpp
    ${INCROOT}/Rect.hpp
    ${INCROOT}/Rect.inl
    ${SRCROOT}/RenderStates.cpp
    ${INCROOT}/RenderStates.hpp
    ${SRCROOT}/RenderTexture.cpp
    ${INCROOT}/RenderTexture.hpp
    ${SRCROOT}/RenderTarget.cpp
    ${INCROOT}/RenderTarget.hpp
    ${INCROOT}/RenderTarget.inl
    ${SRCROOT}/RenderWindow.cpp
    ${INCROOT}/RenderWindow.hpp
    ${SRCROOT}/Shader.cpp
    ${INCROOT}/Shader.hpp
    ${SRCROOT}/Texture.cpp
    ${INCROOT}/Texture.hpp
    ${SRCROOT}/TextureSaver.cpp
    ${SRCROOT}/TextureSaver.hpp
    ${SRCROOT}/Transform.cpp
    ${INCROOT}/Transform.hpp
    ${SRCROOT}/Transformable.cpp
    ${INCROOT}/Transformable.hpp
    ${SRCROOT}/View.cpp
    ${INCROOT}/View.hpp
    ${SRCROOT}/Vertex.cpp
    ${INCROOT}/Vertex.hpp
)
source_group("" FILES ${SRC})

# drawables sources
set(DRAWABLES_SRC
    ${SRCROOT}/Billboard.cpp
    ${INCROOT}/Billboard.hpp
    ${INCROOT}/Drawable.hpp
    ${SRCROOT}/Shape.cpp
    ${INCROOT}/Shape.hpp
    ${SRCROOT}/CircleShape.cpp
    ${INCROOT}/CircleShape.hpp
    ${SRCROOT}/RectangleShape.cpp
    ${INCROOT}/RectangleShape.hpp
    ${SRCROOT}/ConvexShape.cpp
    ${INCROOT}/ConvexShape.hpp
    ${SRCROOT}/Polyhedron.cpp
    ${INCROOT}/Polyhedron.hpp
    ${SRCROOT}/SphericalPolyhedron.cpp
    ${INCROOT}/SphericalPolyhedron.hpp
    ${SRCROOT}/Cuboid.cpp
    ${INCROOT}/Cuboid.hpp
    ${SRCROOT}/ConvexPolyhedron.cpp
    ${INCROOT}/ConvexPolyhedron.hpp
    ${SRCROOT}/Model.cpp
    ${INCROOT}/Model.hpp
    ${SRCROOT}/Sprite.cpp
    ${INCROOT}/Sprite.hpp
    ${SRCROOT}/Text.cpp
    ${INCROOT}/Text.hpp
    ${SRCROOT}/VertexArray.cpp
    ${INCROOT}/VertexArray.hpp
    ${SRCROOT}/VertexBuffer.cpp
    ${INCROOT}/VertexBuffer.hpp
    ${SRCROOT}/VertexContainer.cpp
    ${INCROOT}/VertexContainer.hpp
)
source_group("drawables" FILES ${DRAWABLES_SRC})

# render-texture sources
set(RENDER_TEXTURE_SRC
    ${SRCROOT}/RenderTextureImpl.cpp
    ${SRCROOT}/RenderTextureImpl.hpp
    ${SRCROOT}/RenderTextureImplFBO.cpp
    ${SRCROOT}/RenderTextureImplFBO.hpp
    ${SRCROOT}/RenderTextureImplDefault.cpp
    ${SRCROOT}/RenderTextureImplDefault.hpp
)
source_group("render texture" FILES ${RENDER_TEXTURE_SRC})

# stb_image sources
include_directories("${PROJECT_SOURCE_DIR}/extlibs/headers/stb_image")

# let CMake know about our additional graphics libraries paths
if(SFML3D_OS_WINDOWS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/jpeg")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/freetype2")
elseif(SFML3D_OS_MACOSX)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/jpeg")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/freetype2")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-osx/Frameworks")
elseif(SFML3D_OS_IOS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/jpeg")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/freetype2")
elseif(SFML3D_OS_ANDROID)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/jpeg")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers/freetype2")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-android/${ANDROID_ABI}")
endif()

# find external libraries
if(NOT SFML3D_OPENGL_ES)
    find_package(OpenGL REQUIRED)
    if(SFML3D_OS_LINUX)
        find_package(X11 REQUIRED)
    endif()
    include_directories(${FREETYPE_INCLUDE_DIRS} ${JPEG_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
endif()
if(SFML3D_OPENGL_ES AND SFML3D_OS_LINUX)
    find_package(EGL REQUIRED)
    find_package(GLES REQUIRED)
    include_directories(${EGL_INCLUDE_DIR} ${GLES_INCLUDE_DIR})
endif()
if(SFML3D_OS_ANDROID)
    find_host_package(JPEG REQUIRED)
    find_host_package(Freetype REQUIRED)
else()
    find_package(JPEG REQUIRED)
    find_package(Freetype REQUIRED)
endif()
include_directories(${FREETYPE_INCLUDE_DIRS} ${JPEG_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/extlibs/headers)

# build the list of external libraries to link
if(NOT SFML3D_OPENGL_ES)
    list(APPEND GRAPHICS_EXT_LIBS ${OPENGL_gl_LIBRARY})
    if(SFML3D_OS_LINUX)
        list(APPEND GRAPHICS_EXT_LIBS ${X11_LIBRARIES})
    endif()
endif()
if(SFML3D_OPENGL_ES AND SFML3D_OS_LINUX)
    list(APPEND GRAPHICS_EXT_LIBS ${EGL_LIBRARY} ${GLES_LIBRARY})
endif()
if(SFML3D_OS_IOS)
    list(APPEND GRAPHICS_EXT_LIBS "-framework OpenGLES")
elseif(SFML3D_OS_ANDROID)
    list(APPEND GRAPHICS_EXT_LIBS z)
endif()
list(APPEND GRAPHICS_EXT_LIBS ${FREETYPE_LIBRARY} ${JPEG_LIBRARY})

# add preprocessor symbols
add_definitions(-DSTBI_FAILURE_USERMSG)

# ImageLoader.cpp must be compiled with the -fno-strict-aliasing
# when gcc is used; otherwise saving PNGs may crash in stb_image_write
if(SFML3D_COMPILER_GCC)
    set_source_files_properties(${SRCROOT}/ImageLoader.cpp PROPERTIES COMPILE_FLAGS -fno-strict-aliasing)
endif()

# define the sfml3d-graphics target
sfml3d_add_library(sfml3d-graphics
                 SOURCES ${SRC} ${DRAWABLES_SRC} ${RENDER_TEXTURE_SRC} ${STB_SRC}
                 DEPENDS sfml3d-window sfml3d-system
                 EXTERNAL_LIBS ${GRAPHICS_EXT_LIBS})
