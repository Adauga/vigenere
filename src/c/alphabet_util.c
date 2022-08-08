#include <stdbool.h>
#include <bits/types/FILE.h>
#include <stddef.h>
#include <stdio.h>
#include <malloc.h>

#include "alphabet_util.h"
#include "error_codes.h"
#include "macro.h"

char *read_file(const char *path, size_t *file_size_out) {
    FILE *p_file = NULL;
    char *text = NULL;
    long file_size = 0;
    size_t result = 0;
    int ret = RET_OK;

    CHECK_PARAM(path != NULL);

    p_file = fopen(path, "rb");
    if (!p_file) {
        ret = RET_FILE_OPEN_ERROR;
        goto cleanup;
    }

    fseek(p_file, 0, SEEK_END);
    file_size = ftell(p_file);
    rewind(p_file);

    if (file_size == -1L) {
        ret = RET_FILE_GET_SIZE_ERROR;
        goto cleanup;
    }

    MALLOC_CHECKED(text, (size_t)(unsigned)file_size);

    result = fread(text, 1, (size_t)(unsigned)file_size, p_file);
    if (result != file_size) {
        ret = RET_FILE_READ_ERROR;
    }

    *file_size_out = file_size;

    cleanup:

    if (p_file) {
        fclose(p_file);
    }

    return text;
}

int is_upper_case_letter(char letter, bool *is_upper)
{
    int ret = RET_OK;

    if (letter >= 'a' && letter <= 'z') {
        *is_upper = false;
    } else if (letter >= 'A' && letter <= 'Z') {
        *is_upper = true;
    } else {
        ret = RET_INVALID_PARAM;
    }

    return ret;
}

int alphabet_letter_get_index(char letter, int *index, bool *is_upper)
{
    int ret = RET_OK;
    bool is_upper_internal = false;

    DO(is_upper_case_letter(letter, &is_upper_internal));

    *index = (is_upper_internal == true) ? (letter - 'A') : (letter - 'a');

    if (is_upper) {
        *is_upper = is_upper_internal;
    }

    cleanup:

    return ret;
}

int alphabet_letter_from_index(int index, bool is_upper, char *letter)
{
    int ret = RET_OK;

    if ((0 <= index) && (index <= 25)) {
        *letter = (char) (is_upper ? index + 'A' : index + 'a');
    } else {
        ret = RET_INVALID_PARAM;
    }

    return ret;
}