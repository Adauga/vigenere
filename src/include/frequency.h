#ifndef VIGENERE_FREQUENCY_H
#define VIGENERE_FREQUENCY_H

#include "alphabet_util.h"

#define MONO_LEN CURRENT_ALPHABET_LEN
#define DIA_LEN  CURRENT_ALPHABET_LEN * CURRENT_ALPHABET_LEN
#define TRI_LEN CURRENT_ALPHABET_LEN * CURRENT_ALPHABET_LEN * CURRENT_ALPHABET_LEN
#define TETRA_LEN CURRENT_ALPHABET_LEN * CURRENT_ALPHABET_LEN * CURRENT_ALPHABET_LEN * CURRENT_ALPHABET_LEN

#define ENGLISH_FITNESS -9.7

int frequency_init(const char *file_name);
void frequency_free(void);

int build_tetragram_frequency_table(const char *encrypted_text, size_t encrypted_text_len, double **tetra_frequency);
int calculate_fitness(const char *encrypted_text, size_t encrypted_text_len, double *score);
int variational_method_decrypt(const char *encrypted_text, size_t encrypted_text_len, char **key, size_t *key_len,
                               char **decrypted_text);

#endif //VIGENERE_FREQUENCY_H
