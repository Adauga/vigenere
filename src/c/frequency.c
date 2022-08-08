#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "error_codes.h"
#include "macro.h"
#include "frequency.h"
#include "alphabet_util.h"
#include "key.h"
#include "vigenere.h"

static double *tetra_freq_trained = NULL;

int frequency_init(const char *file_name)
{
    int ret = RET_OK;
    char *text = NULL;
    size_t file_size = 0;

    CHECK_PARAM(file_name);

    text = read_file(file_name, &file_size);
    DO(build_tetragram_frequency_table(text, strlen(text), &tetra_freq_trained));

    cleanup:;

    free(text);

    return ret;
}

void frequency_free(void)
{
    if (tetra_freq_trained) free(tetra_freq_trained);
}

int build_tetragram_frequency_table(const char *encrypted_text, size_t encrypted_text_len, double **tetra_frequency)
{
    int ret = RET_OK;
    double *tetra_frequency_internal = NULL;
    int i = 0;

    CHECK_PARAM(encrypted_text);
    CHECK_PARAM(encrypted_text_len > 0);

    MALLOC_CHECKED(tetra_frequency_internal, sizeof(double) * TETRA_LEN);
    memset(tetra_frequency_internal, 0, sizeof(double) * TETRA_LEN);

    for (i = 0; i < encrypted_text_len - 3; i++) {
        int a_let_idx = 0;
        int b_let_idx = 0;
        int c_let_idx = 0;
        int d_let_idx = 0;
        size_t x = 0;

        DO(alphabet_letter_get_index(encrypted_text[i], &a_let_idx, NULL));
        DO(alphabet_letter_get_index(encrypted_text[i + 1], &b_let_idx, NULL));
        DO(alphabet_letter_get_index(encrypted_text[i + 2], &c_let_idx, NULL));
        DO(alphabet_letter_get_index(encrypted_text[i + 3], &d_let_idx, NULL));

        x = a_let_idx * TRI_LEN + b_let_idx * DIA_LEN + c_let_idx * MONO_LEN + d_let_idx;
        tetra_frequency_internal[x]++;
    }

    for (i = 0; i < TETRA_LEN; i++) {
        tetra_frequency_internal[i] = tetra_frequency_internal[i] / (double)(encrypted_text_len - 3);
    }

    *tetra_frequency = tetra_frequency_internal;

    cleanup:

    if (ret != RET_OK) {
        free(tetra_frequency_internal);
    }

    return ret;
}

int calculate_fitness(const char *encrypted_text, size_t encrypted_text_len, double *score)
{
    int ret = RET_OK;
    double score_internal = 0;

    CHECK_PARAM(encrypted_text);
    CHECK_PARAM(encrypted_text_len > 0);

    for (int i = 0; i < encrypted_text_len - 3; i++) {
        int a_let_idx = 0;
        int b_let_idx = 0;
        int c_let_idx = 0;
        int d_let_idx = 0;
        char tetragram[4];
        double y = 0;
        size_t x = 0;

        memcpy(tetragram, &encrypted_text[i], 4);
        DO(alphabet_letter_get_index(tetragram[0], &a_let_idx, NULL));
        DO(alphabet_letter_get_index(tetragram[1], &b_let_idx, NULL));
        DO(alphabet_letter_get_index(tetragram[2], &c_let_idx, NULL));
        DO(alphabet_letter_get_index(tetragram[3], &d_let_idx, NULL));

        x = a_let_idx * TRI_LEN + b_let_idx * DIA_LEN + c_let_idx * MONO_LEN + d_let_idx;
        y = tetra_freq_trained[x];

        if (y == 0) {
            score_internal += -15;
        } else {
            score_internal += log(y);
        }
    }

    *score = score_internal / (double)(encrypted_text_len - 3);

    cleanup:

    return ret;
}

static int variational_method_check_candidate(const char *encrypted_text, size_t encrypted_text_len,
                                               const char *key_candidate, size_t key_len, double *candidate_score)
{
    int ret = RET_OK;
    char *temp_decrypted = NULL;

    DO(vigenere_decrypt(encrypted_text, encrypted_text_len, key_candidate, key_len, &temp_decrypted));
    DO(calculate_fitness(temp_decrypted, encrypted_text_len, candidate_score));

    cleanup:

    free(temp_decrypted);

    return ret;
}

int variational_method_decrypt(const char *encrypted_text, size_t encrypted_text_len, char **key, size_t *key_len,
                               char **decrypted_text)
{
    int ret = RET_OK;
    char *key_internal = NULL;
    size_t key_internal_len = 0;
    char *decrypted_text_internal = NULL;
    double score = -99;

    CHECK_PARAM(encrypted_text);
    CHECK_PARAM(encrypted_text_len > 0);

    DO(find_key_len(encrypted_text, encrypted_text_len, &key_internal_len));

    MALLOC_CHECKED(key_internal, key_internal_len + 1);
    memset(key_internal, 'a', key_internal_len);
    memset(&key_internal[key_internal_len], '\0', 1);

    for (int k = 0; score < ENGLISH_FITNESS && k < UCHAR_MAX; k++) {
        size_t x = 0;
        char *key_candidate = strdup(key_internal);
        srand(k);

        x = (rand() + 1) % key_internal_len;

        for (int i = 0; i < CURRENT_ALPHABET_LEN; i++) {
            double candidate_score = 0;

            DO(alphabet_letter_from_index(i, false, &key_candidate[x]));
            DO(variational_method_check_candidate(encrypted_text, encrypted_text_len, key_candidate,
                                                  key_internal_len, &candidate_score));
            if (candidate_score > score) {
                memcpy(key_internal, key_candidate, key_internal_len);
                score = candidate_score;
            }
        }

        free(key_candidate);
    }

    DO(vigenere_decrypt(encrypted_text, encrypted_text_len, key_internal, key_internal_len, &decrypted_text_internal));

    *decrypted_text = decrypted_text_internal;
    *key = key_internal;
    *key_len = key_internal_len;

    cleanup:

    if (ret != RET_OK)
    {
        if (key_internal) free(key_internal);
    }

    return ret;
}