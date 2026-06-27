set(SOURCES
    codec.cpp
    serialization.cpp
)

add_library(acp ${SOURCES})

target_link_libraries(acp PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(acp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)