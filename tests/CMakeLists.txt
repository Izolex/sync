project(sync_tests)

find_path(CMOCKA_INCLUDE_DIR NAMES cmocka.h PATHS include)
set(CMOCKA_INCLUDE_DIRS "${CMOCKA_INCLUDE_DIR}")

find_library(CMOCKA_LIBRARY NAMES cmocka PATHS lib)
set(CMOCKA_LIBRARIES "${CMOCKA_LIBRARY}")

find_package(Threads REQUIRED)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CMOCKA_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} libsync)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMOCKA_INCLUDE_DIRS}")
