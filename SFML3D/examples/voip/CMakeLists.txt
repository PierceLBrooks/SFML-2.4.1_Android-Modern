
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/voip)

# all source files
set(SRC ${SRCROOT}/VoIP.cpp
        ${SRCROOT}/Client.cpp
        ${SRCROOT}/Server.cpp)

# define the voip target
sfml3d_add_example(voip
                 SOURCES ${SRC}
                 DEPENDS sfml3d-audio sfml3d-network sfml3d-system)
