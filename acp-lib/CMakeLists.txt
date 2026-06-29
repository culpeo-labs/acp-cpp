set(SOURCES
    codec.cpp
    json_value.cpp
    serialization.cpp
)

add_library(acp ${SOURCES})

target_link_libraries(acp PRIVATE glaze::glaze)

target_include_directories(acp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)