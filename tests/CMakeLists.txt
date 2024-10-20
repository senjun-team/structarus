cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

macro(add_tests PREFIX TESTS)
    foreach (TEST ${TESTS})
        add_executable("${PREFIX}_${TEST}" ${TEST}.cpp)
        target_link_libraries(
            "${PREFIX}_${TEST}"
            GTest::gtest_main
            )
        target_include_directories("${PREFIX}_${TEST}" PUBLIC ${PROJECT_SOURCE_DIR})
        add_test(NAME "${PREFIX}_${TEST}" COMMAND "${PREFIX}_${TEST}")
    endforeach ()
endmacro()

add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(tar)
