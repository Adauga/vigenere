#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "error_codes.h"
#include "vigenere.h"
#include "test_util.h"

static int error_count = 0;

static void utest_vigenere_encrypt(void)
{
    char *plain_text = "TheVigenerecipherisaperiodicpolyalphabeticsubstitutioncipher";
    char *key = "ThisisKey";
    char *encrypted_text = NULL;
    char *expected_encrypted_text = "MomNqyorcklkaxzovglhxwzayhgvwwdgsvtftimlqucyzlaqlclsslvpxzmj";

    ASSERT_RET_OK(vigenere_encrypt(plain_text, strlen(plain_text), key, strlen(key), &encrypted_text));

    ASSERT_TRUE(!memcmp(expected_encrypted_text, encrypted_text, strlen(expected_encrypted_text)));

    cleanup:

    free(encrypted_text);
}

static void utest_vigenere_encrypt_used_as_one_time_pad(void)
{
    char *plain_text = "The";
    char *key = "ThisisKey";
    char *encrypted_text = NULL;
    char *expected_encrypted_text = "Mom";

    ASSERT_RET_OK(vigenere_encrypt(plain_text, strlen(plain_text), key, strlen(key), &encrypted_text));

    ASSERT_TRUE(!memcmp(expected_encrypted_text, encrypted_text, strlen(expected_encrypted_text)));

    cleanup:

    free(encrypted_text);
}

static void utest_vigenere_encrypt_NULL_plain_text(void)
{
    char *plain_text = NULL;
    char *key = "ThisisKey";
    char *encrypted_text = NULL;

    ASSERT_RET(RET_INVALID_PARAM, vigenere_encrypt(plain_text, 0, key, strlen(key),
                                                   &encrypted_text));

    cleanup:;
}

static void utest_vigenere_encrypt_NULL_key(void)
{
    char *plain_text = "The";
    char *key = NULL;
    char *encrypted_text = NULL;

    ASSERT_RET(RET_INVALID_PARAM, vigenere_encrypt(plain_text, strlen(plain_text), key, 0,
                                                   &encrypted_text));

    cleanup:;
}

static void utest_vigenere_encrypt_empty_plain_text(void)
{
    char *plain_text = "";
    char *key = "ThisisKey";
    char *encrypted_text = NULL;

    ASSERT_RET(RET_INVALID_PARAM, vigenere_encrypt(plain_text, strlen(plain_text), key, strlen(key),
                                                   &encrypted_text));

    cleanup:;
}

static void utest_vigenere_encrypt_empty_key(void)
{
    char *plain_text = "The";
    char *key = "";
    char *encrypted_text = NULL;

    ASSERT_RET(RET_INVALID_PARAM, vigenere_encrypt(plain_text, strlen(plain_text), key, strlen(key),
                                                   &encrypted_text));

    cleanup:;
}

static void utest_vigenere_decrypt(void)
{
    char *encrypted_text = "MomNqyorcklkaxzovglhxwzayhgvwwdgsvtftimlqucyzlaqlclsslvpxzmj";
    char *key = "ThisisKey";
    char *decrypted_text = NULL;
    char *expected_decrypted_text = "TheVigenerecipherisaperiodicpolyalphabeticsubstitutioncipher";

    ASSERT_RET_OK(vigenere_decrypt(encrypted_text, strlen(encrypted_text), key, strlen(key), &decrypted_text));

    ASSERT_TRUE(!memcmp(expected_decrypted_text, decrypted_text, strlen(expected_decrypted_text)));

    cleanup:

    free(decrypted_text);
}

static void utest_vigenere_decrypt_used_as_one_time_pad(void)
{
    char *encrypted_text = "Mom";
    char *key = "ThisisKey";
    char *decrypted_text = NULL;
    char *expected_decrypted_text = "The";

    ASSERT_RET_OK(vigenere_decrypt(encrypted_text, strlen(encrypted_text), key, strlen(key), &decrypted_text));

    ASSERT_TRUE(!memcmp(expected_decrypted_text, decrypted_text, strlen(expected_decrypted_text)));

    cleanup:

    free(decrypted_text);
}

int main(void)
{
    utest_vigenere_encrypt();
    utest_vigenere_encrypt_used_as_one_time_pad();

    utest_vigenere_encrypt_NULL_plain_text();
    utest_vigenere_encrypt_NULL_key();
    utest_vigenere_encrypt_empty_plain_text();
    utest_vigenere_encrypt_empty_key();

    utest_vigenere_decrypt();
    utest_vigenere_decrypt_used_as_one_time_pad();

    return (error_count > 0) ? -1 : 0;
}