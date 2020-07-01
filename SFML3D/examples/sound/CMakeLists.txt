
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/sound)

# all source files
set(SRC ${SRCROOT}/Sound.cpp)

# define the sound target
sfml3d_add_example(sound
                 SOURCES ${SRC}
                 DEPENDS sfml3d-audio sfml3d-system)
