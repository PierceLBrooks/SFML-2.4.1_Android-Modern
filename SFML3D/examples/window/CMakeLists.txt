
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/window)

# all source files
set(SRC ${SRCROOT}/Window.cpp)

# find OpenGL and GLU
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# define the window target
sfml3d_add_example(window GUI_APP
                 SOURCES ${SRC}
                 DEPENDS sfml3d-window sfml3d-system ${OPENGL_LIBRARIES})
