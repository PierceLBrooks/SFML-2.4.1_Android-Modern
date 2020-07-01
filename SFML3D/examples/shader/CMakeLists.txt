
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/shader)

# all source files
set(SRC
    ${SRCROOT}/Effect.hpp
    ${SRCROOT}/Shader.cpp)

# define the shader target
sfml3d_add_example(shader GUI_APP
                 SOURCES ${SRC}
                 DEPENDS sfml3d-graphics sfml3d-window sfml3d-system)
