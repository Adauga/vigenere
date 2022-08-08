#ifndef VIGENEREDECRYPTER_MACRO_H
#define VIGENEREDECRYPTER_MACRO_H

#define DO(func)                                                                                                       \
    {                                                                                                                  \
        ret = (func);                                                                                                  \
        if (ret != RET_OK) {                                                                                           \
            goto cleanup;                                                                                              \
        }                                                                                                              \
    }

#define MALLOC_CHECKED(_buffer, _len)                                                                                  \
    {                                                                                                                  \
        if (NULL == ((_buffer) = malloc(_len))) {                                                                      \
            ret = RET_MEMORY_ALLOC_ERROR;                                                                              \
            goto cleanup;                                                                                              \
        }                                                                                                              \
    }

#define CALLOC_CHECKED(_buffer, _len)                                                                                  \
    {                                                                                                                  \
        if (NULL == ((_buffer) = calloc(1, (_len)))) {                                                                 \
            ret = RET_MEMORY_ALLOC_ERROR;                                                                              \
            goto cleanup;                                                                                              \
        }                                                                                                              \
    }

#define REALLOC_CHECKED(_buffer, _len, _out)                                                                           \
    {                                                                                                                  \
        if (NULL == ((_out) = realloc((_buffer), (_len)))) {                                                           \
            ret = RET_MEMORY_ALLOC_ERROR;                                                                              \
            goto cleanup;                                                                                              \
        }                                                                                                              \
    }

#define CHECK_PARAM(_statement)                                                                                        \
    {                                                                                                                  \
        if (!(_statement)) {                                                                                           \
            ret = RET_INVALID_PARAM;                                                                                   \
            goto cleanup;                                                                                              \
        }                                                                                                              \
    }

#endif //VIGENEREDECRYPTER_MACRO_H
