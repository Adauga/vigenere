cmake_minimum_required(VERSION 3.19)
project(VigenereDecrypter C)

set(CMAKE_C_STANDARD 99)

set(SRC c/alphabet_util.c
        c/vigenere.c
        c/key.c
        c/frequency.c)

add_library(vigenere OBJECT ${SRC})
target_include_directories(vigenere PRIVATE include)
target_link_libraries(vigenere m)
