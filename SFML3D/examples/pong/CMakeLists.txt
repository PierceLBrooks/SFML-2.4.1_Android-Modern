
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/pong)

# all source files
set(SRC ${SRCROOT}/Pong.cpp)

# define the pong target
sfml3d_add_example(pong GUI_APP
                 SOURCES ${SRC}
                 DEPENDS sfml3d-audio sfml3d-graphics sfml3d-window sfml3d-system)
