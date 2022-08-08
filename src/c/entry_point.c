#include <stdio.h>
#include <linux/limits.h>
#include <string.h>
#include <malloc.h>

#include "macro.h"
#include "error_codes.h"
#include "alphabet_util.h"
#include "frequency.h"

int main(int argc, char *argv[])
{
    int ret = RET_OK;
    char *encrypted_text = NULL;
    size_t file_size = 0;
    char *key = NULL;
    size_t key_len;
    char *decrypted_text = NULL;

    CHECK_PARAM(argc > 1);
    CHECK_PARAM(strlen(argv[1]) < PATH_MAX);

    DO(frequency_init("./novel_freq_blob.txt"));

    encrypted_text = read_file(argv[1], &file_size);
    DO(variational_method_decrypt(encrypted_text, file_size, &key, &key_len, &decrypted_text));

    printf("\n Founded key = ");
    fwrite(key, sizeof(char), key_len, stdout);
    printf("\n Decrypted text = ");
    fwrite(decrypted_text, sizeof(char), file_size, stdout);

cleanup:

    if (encrypted_text) free(encrypted_text);
    if (decrypted_text) free(decrypted_text);
    if (key) free(key);
    frequency_free();

    return ret;
}