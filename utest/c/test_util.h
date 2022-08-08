#ifndef VIGENEREDECRYPTER_TEST_UTIL_H
#define VIGENEREDECRYPTER_TEST_UTIL_H

#define ASSERT_RET_OK(func)                                                                                            \
    {                                                                                                                  \
        int _ret = (func);                                                                                             \
        if (_ret != RET_OK) {                                                                                          \
            error_count++;                                                                                             \
            goto cleanup;                                                                                              \
        }                                                                                                              \
    }

#define ASSERT_RET(exp_ret, func)                                                                                      \
    {                                                                                                                  \
        int _ret = (func);                                                                                             \
        if (_ret != (exp_ret)) {                                                                                       \
            error_count++;                                                                                             \
            goto cleanup;                                                                                              \
        }                                                                                                              \
    }

#define ASSERT_TRUE(expression)                                                                                        \
    {                                                                                                                  \
        if (!(expression)) {                                                                                           \
            error_count++;                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \

#endif //VIGENEREDECRYPTER_TEST_UTIL_H
