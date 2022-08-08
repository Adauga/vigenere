#include <stdbool.h>
#include <stdio.h>

#include "error_codes.h"
#include "alphabet_util.h"
#include "test_util.h"

static int error_count = 0;

static void utest_alphabet_upper_letter_get_index(void)
{
    char p_upper = 'P';
    int index = -1;
    bool is_upper = false;

    ASSERT_RET_OK(alphabet_letter_get_index(p_upper, &index, &is_upper));

    ASSERT_TRUE(index == 15);
    ASSERT_TRUE(is_upper == true);

    cleanup:;
}

static void utest_alphabet_lower_letter_get_index(void)
{
    char p_upper = 'p';
    int index = -1;
    bool is_upper = false;

    ASSERT_RET_OK(alphabet_letter_get_index(p_upper, &index, &is_upper));

    ASSERT_TRUE(index == 15);
    ASSERT_TRUE(is_upper == false);

    cleanup:;
}

static void utest_non_alphabet_symbol_get_index(void)
{
    char p_upper = '+';
    int index = -1;
    bool is_upper = false;

    ASSERT_RET(RET_INVALID_PARAM, alphabet_letter_get_index(p_upper, &index, &is_upper));

    cleanup:;
}

static void utest_alphabet_upper_letter_from_index(void)
{
    int index = 15;
    bool is_upper = true;
    char letter = ' ';

    ASSERT_RET_OK(alphabet_letter_from_index(index, is_upper, &letter));

    ASSERT_TRUE(letter == 'P');

    cleanup:;
}

static void utest_alphabet_lower_letter_from_index(void)
{
    int index = 15;
    bool is_upper = false;
    char letter = ' ';

    ASSERT_RET_OK(alphabet_letter_from_index(index, is_upper, &letter));

    ASSERT_TRUE(letter == 'p');

    cleanup:;
}

static void utest_non_alphabet_symbol_from_index(void)
{
    int index = 27;
    bool is_upper = false;
    char letter = ' ';

    ASSERT_RET(RET_INVALID_PARAM, alphabet_letter_from_index(index, is_upper, &letter));

    cleanup:;
}

int main(void)
{
    utest_alphabet_upper_letter_get_index();
    utest_alphabet_lower_letter_get_index();
    utest_non_alphabet_symbol_get_index();

    utest_alphabet_upper_letter_from_index();
    utest_alphabet_lower_letter_from_index();
    utest_non_alphabet_symbol_from_index();

    return (error_count > 0) ? -1 : 0;
}