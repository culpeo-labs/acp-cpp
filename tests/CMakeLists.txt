add_executable(acp_tests
    serialization_test.cpp
    json_value_test.cpp
)

target_link_libraries(acp_tests PRIVATE
    acp
    Catch2::Catch2WithMain
)

target_include_directories(acp_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/acp-lib
)

include(CTest)
include(Catch)
catch_discover_tests(acp_tests)
