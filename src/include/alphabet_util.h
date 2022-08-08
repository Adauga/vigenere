#ifndef VIGENEREDECRYPTER_ALPHABET_UTIL_H
#define VIGENEREDECRYPTER_ALPHABET_UTIL_H

#include "stdbool.h"

#define ENGLISH_ALPHABET_LEN 26
#define CURRENT_ALPHABET_LEN ENGLISH_ALPHABET_LEN

char *read_file(const char *file_name, size_t *file_size);
int is_upper_case_letter(char letter, bool *is_upper);
int alphabet_letter_get_index(char letter, int *number, bool *is_upper);
int alphabet_letter_from_index(int index, bool is_upper, char *letter);

#endif //VIGENEREDECRYPTER_ALPHABET_UTIL_H
