#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "vigenere.h"
#include "alphabet_util.h"
#include "error_codes.h"
#include "macro.h"

static int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int vigenere_encrypt(const char *plain_text, size_t plain_text_len, const char *key, size_t key_len,
                     char **encrypted_text)
{
    int ret = RET_OK;
    char *encrypted_text_internal = NULL;

    CHECK_PARAM(plain_text);
    CHECK_PARAM(key);
    CHECK_PARAM(plain_text_len > 0 && key_len > 0)

    MALLOC_CHECKED(encrypted_text_internal, plain_text_len);

    for (int i = 0; i < plain_text_len; i++) {
        int p_index = 0;
        int k_index = 0;
        bool is_p_upper = false;

        DO(alphabet_letter_get_index(plain_text[i], &p_index, &is_p_upper));
        DO(alphabet_letter_get_index(key[i % key_len], &k_index, NULL));
        DO(alphabet_letter_from_index(mod(p_index + k_index, 26), is_p_upper, &encrypted_text_internal[i]))
    }

    *encrypted_text = encrypted_text_internal;

    cleanup:

    if (ret != RET_OK) {
        free(encrypted_text_internal);
    }

    return ret;
}

int vigenere_decrypt(const char *encrypted_text, size_t encrypted_text_len, const char *key,
                     size_t key_len, char **decrypted_text)
{
    int ret = RET_OK;
    char *decrypted_text_internal = NULL;

    CHECK_PARAM(encrypted_text);
    CHECK_PARAM(key);
    CHECK_PARAM(encrypted_text_len > 0 && key_len > 0);

    MALLOC_CHECKED(decrypted_text_internal, encrypted_text_len);

    for (int i = 0; i < encrypted_text_len; i++) {
        int e_index = 0;
        int k_index = 0;
        bool is_e_upper = false;

        DO(alphabet_letter_get_index(encrypted_text[i], &e_index, &is_e_upper));
        DO(alphabet_letter_get_index(key[i % key_len], &k_index, NULL));
        DO(alphabet_letter_from_index(mod(e_index - k_index, 26), is_e_upper, &decrypted_text_internal[i]));
    }

    *decrypted_text = decrypted_text_internal;

    cleanup:

    if (ret != RET_OK) {
        free(decrypted_text_internal);
    }

    return ret;
}