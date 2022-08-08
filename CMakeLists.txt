set(PROJECT_NAME "vigenere")

cmake_minimum_required(VERSION 3.12)
project(${PROJECT_NAME} LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(src)

if (WITH_MEMCHECK)
    set(MEMCHECK_FLAG -T memcheck)
endif ()
include(CTest)
add_subdirectory(utest)

add_executable(vigenere_run ./src/c/entry_point.c)

include_directories(./src/include)
file(COPY ./utest/resource/novel_freq_blob.txt DESTINATION ${CMAKE_BINARY_DIR}/)
target_link_libraries(vigenere_run vigenere)

add_custom_target(${PROJECT_NAME}-run-tests
        COMMAND make utest_alphabet
        COMMAND make utest_frequency
        COMMAND make utest_key
        COMMAND make utest_vigenere
        COMMAND ctest ${MEMCHECK_FLAG} --output-on-failure)
