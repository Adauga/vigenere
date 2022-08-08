#ifndef VIGENERE_KEY_H
#define VIGENERE_KEY_H

#include <stddef.h>

#define MAX_KEY_LEN 13
#define MIN_KEY_LEN 2

#define ENGLISH_IOC 1.6 //1.52?

int find_key_len(const char *encrypted_text, size_t encrypted_text_len, size_t *period);
int slicing(const char *text, size_t text_len, size_t slice_len, char ***slices);

#endif //VIGENERE_KEY_H
