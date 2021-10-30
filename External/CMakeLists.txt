set(    HEADER_LIST
        "${engine_SOURCE_DIR}/External/include/KHR/khrplatform.h"
        "${engine_SOURCE_DIR}/External/include/glad/gl.h"
        "${engine_SOURCE_DIR}/External/include/date/date.h")

add_library(
        External

        STATIC

        src/gl.cpp

        ${HEADER_LIST})

target_include_directories(External PUBLIC ${HEADER_LIST})