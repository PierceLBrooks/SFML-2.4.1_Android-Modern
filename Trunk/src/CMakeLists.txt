#https://github.com/android-ndk/ndk/issues/381
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

set(INC ${CMAKE_CURRENT_LIST_DIR}/../include)
set(SRC ${CMAKE_CURRENT_LIST_DIR})
set(LIBRARIES )
set(DEFINES )

find_library(log-lib log)
list(APPEND "${log-lib}")

list(APPEND LIBRARIES sfml-system)
list(APPEND LIBRARIES sfml-window)
list(APPEND LIBRARIES sfml-graphics)
list(APPEND LIBRARIES sfml-audio)
list(APPEND LIBRARIES sfml-network)
list(APPEND LIBRARIES sfml-main)
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
