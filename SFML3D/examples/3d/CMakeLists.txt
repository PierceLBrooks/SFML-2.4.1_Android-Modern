
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/3d)

# all source files
set(SRC ${SRCROOT}/3d.cpp)

# define the 3d target
sfml3d_add_example(3d GUI_APP
                 SOURCES ${SRC}
                 DEPENDS sfml3d-graphics sfml3d-window sfml3d-system)
