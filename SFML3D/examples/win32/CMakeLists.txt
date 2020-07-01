
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/win32)

# all source files
set(SRC ${SRCROOT}/Win32.cpp)

# define the win32 target
sfml3d_add_example(win32 GUI_APP
                 SOURCES ${SRC}
                 DEPENDS sfml3d-graphics sfml3d-window sfml3d-system)
