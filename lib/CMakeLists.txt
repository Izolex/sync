project(libsync LANGUAGES C)

set(HEADERS
    ../include/spin_lock.h
)

set(ARCHIVE_OUTPUT_NAME ${PROJECT_NAME})
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCES)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME sync PUBLIC_HEADER "${HEADERS}")

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../include)

