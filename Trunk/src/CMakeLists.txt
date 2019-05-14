set(INC ${CMAKE_CURRENT_LIST_DIR}/../include)
set(SRC ${CMAKE_CURRENT_LIST_DIR})
set(LIBRARIES )

find_library(log-lib log)
list(APPEND ${log-lib})

list(APPEND sfml-system)
list(APPEND sfml-window)
list(APPEND sfml-graphics)
list(APPEND sfml-audio)
list(APPEND sfml-network)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../../SFML-2.4.1/include)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

set(PROJECT_FILES
	${SRC}/main.cpp
	${SRC}/native-lib.cpp
	${INC}/native-lib.hpp
	${SRC}/Log.cpp
	${INC}/Log.hpp
)

add_library(sfml_android ${PROJECT_FILES})
target_link_libraries(sfml_android ${LIBRARIES})
