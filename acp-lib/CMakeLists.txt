set(SOURCES
    main.cpp
)

add_library(acp ${SOURCES})

target_include_directories(acp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)