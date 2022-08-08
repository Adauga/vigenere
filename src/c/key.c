#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "macro.h"
#include "error_codes.h"
#include "alphabet_util.h"
#include "key.h"

static int calculate_ioc(const char *text_slice, size_t text_slice_len, double *ioc_value)
{
    int ret = RET_OK;
    size_t a_counts[CURRENT_ALPHABET_LEN] = {0};
    size_t num_slice = 0;
    size_t total_l = 0;
    int i = 0;

    CHECK_PARAM(text_slice);
    CHECK_PARAM(text_slice_len > 0);

    for (i = 0; i < text_slice_len; i++) {
        int l_index = 0;

        DO(alphabet_letter_get_index(text_slice[i], &l_index, NULL));

        a_counts[l_index]++;
    }

    for (i = 0; i < CURRENT_ALPHABET_LEN; i++) {
        num_slice += a_counts[i] * (a_counts[i] - 1);
        total_l += a_counts[i];
    }

    *ioc_value = (double )(CURRENT_ALPHABET_LEN * num_slice) / (double)(total_l * (total_l - 1));

    cleanup:;

    return ret;
}

int slicing(const char *text, size_t text_len, size_t slice_count, char ***slices)
{
    int ret = RET_OK;
    char **slices_internal = NULL;
    size_t slice_len_internal = 0;
    int i = 0;

    CHECK_PARAM(text);
    CHECK_PARAM(text_len > 0);
    CHECK_PARAM(slice_count > 0);

    slice_len_internal = text_len / slice_count;

    MALLOC_CHECKED(slices_internal, sizeof(char *) * slice_count);

    for (i = 0; i < slice_count; i++) {
        MALLOC_CHECKED(slices_internal[i], slice_len_internal + 1);
        memset(slices_internal[i], '0', slice_len_internal);
        memset(slices_internal[i], '\0', slice_len_internal + 1);
    }

    for (i = 0; i < slice_len_internal * slice_count; i++) {
        strncat(slices_internal[i % slice_count], &text[i], 1);
    }

    *slices = slices_internal;

    cleanup:

    if (ret != RET_OK) {
        for (i = 0; i < slice_count; i++) {
            if (slices_internal[i]) {
                free(slices_internal[i]);
            }
        }
        free(slices_internal);
    }

    return ret;
}

static int try_period(const char *encrypted_text, size_t encrypted_text_len, size_t period, bool *is_key)
{
    int ret = RET_OK;
    char **slices = NULL;
    double sum = 0.0;
    int i = 0;

    CHECK_PARAM(encrypted_text);

    DO(slicing(encrypted_text, encrypted_text_len, period, &slices));

    for (i = 0; i < period; i++) {
        double ioc_value = 0;

        DO(calculate_ioc(slices[i], encrypted_text_len / period, &ioc_value));
        sum += ioc_value;
    }

    *is_key = (sum / (double)period) > ENGLISH_IOC ?  true : false;

    cleanup:

    if (slices) {
        for (i = 0; i < period; i++) {
            if (slices[i]) {
                free(slices[i]);
            }
        }
        free(slices);
    }

    return ret;
}

int find_key_len(const char *encrypted_text, size_t encrypted_text_len, size_t *period)
{
    int ret = RET_OK;
    size_t period_internal = MIN_KEY_LEN;
    bool is_found = false;

    CHECK_PARAM(encrypted_text);
    CHECK_PARAM(encrypted_text_len > 0);

    for (;!is_found && period_internal < MAX_KEY_LEN; period_internal++) {
        DO(try_period(encrypted_text, encrypted_text_len, period_internal, &is_found));
        if (is_found) {
            *period = period_internal;
            goto cleanup;
        }
    }

    ret = RET_KEY_LEN_UNSUPPORTED;

    cleanup:

    return ret;
}