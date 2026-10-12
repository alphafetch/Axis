include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(axis_tests
    test_vector3.cpp
    test_matrix3.cpp
    test_matrix4.cpp
)
target_link_libraries(axis_tests PRIVATE axis GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(axis_tests)