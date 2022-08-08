include_directories(../src/include)

add_executable(utest_alphabet c/utest_alphabet.c)
add_executable(utest_vigenere c/utest_vigenere.c)
add_executable(utest_key c/utest_key.c)
add_executable(utest_frequency c/utest_frequency.c)

file(GLOB_RECURSE data resource/*)
file(COPY ${data} DESTINATION .)

target_link_libraries(utest_alphabet vigenere)
target_link_libraries(utest_vigenere vigenere)
target_link_libraries(utest_key vigenere)
target_link_libraries(utest_frequency vigenere)

add_test(NAME utest_alphabet COMMAND utest_alphabet)
add_test(NAME utest_vigenere COMMAND utest_vigenere)
add_test(NAME utest_key COMMAND utest_key)
add_test(NAME utest_frequency COMMAND utest_frequency)

