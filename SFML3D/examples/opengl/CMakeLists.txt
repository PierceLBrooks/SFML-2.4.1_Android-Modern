
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/opengl)

# all source files
set(SRC ${SRCROOT}/OpenGL.cpp)

# find OpenGL and GLU
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# define the opengl target
sfml3d_add_example(opengl GUI_APP
                 SOURCES ${SRC}
                 DEPENDS sfml3d-graphics sfml3d-window sfml3d-system ${OPENGL_LIBRARIES})
