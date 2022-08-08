#ifndef VIGENERE_VIGINERE_H
#define VIGENERE_VIGINERE_H

int vigenere_encrypt(const char *plain_text, size_t plain_text_len, const char *key, size_t key_len,
                     char **encrypted_text);

int vigenere_decrypt(const char *encrypted_text, size_t encrypted_text_len, const char *key,
                     size_t key_len, char **decrypted_text);

#endif //VIGENERE_VIGINERE_H
