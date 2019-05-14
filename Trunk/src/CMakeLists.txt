set(INC ${CMAKE_CURRENT_LIST_DIR}/../include)
set(SRC ${CMAKE_CURRENT_LIST_DIR})
set(LIBRARIES )
set(DEFINES )
set(DEBUG_SUFFIX "")

if("CMAKE_BUILD_TYPE" STREQUAL "DEBUG")
	set(DEBUG_SUFFIX "-d")
endif()

find_library(log-lib log)
list(APPEND "${log-lib}")

list(APPEND LIBRARIES "sfml-system${DEBUG_SUFFIX}")
list(APPEND LIBRARIES "sfml-window${DEBUG_SUFFIX}")
list(APPEND LIBRARIES "sfml-graphics${DEBUG_SUFFIX}")
list(APPEND LIBRARIES "sfml-audio${DEBUG_SUFFIX}")
list(APPEND LIBRARIES "sfml-network${DEBUG_SUFFIX}")
list(APPEND LIBRARIES "sfml-main${DEBUG_SUFFIX}")
include_directories(${CMAKE_CURRENT_LIST_DIR}/../../SFML-2.4.1/include)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

list(APPEND DEFINES "SFML_JNI_CLASS=\"com/piercelbrooks/sfml/app/MainActivity\"")

set(PROJECT_FILES
	${SRC}/main.cpp
	${SRC}/native-lib.cpp
	${INC}/native-lib.hpp
	${SRC}/Log.cpp
	${INC}/Log.hpp
)

message(${LIBRARIES})

add_library(sfml_android SHARED ${PROJECT_FILES})
target_link_libraries(sfml_android ${LIBRARIES})
target_compile_definitions(sfml_android PRIVATE ${DEFINES})
