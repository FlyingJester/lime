#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus

#define DEF_ARG(X_) = X_

extern "C" {

#else

#define DEF_ARG(X_)

#endif

uint64_t KLime_stringLength(const char *str);
bool KLime_charIsSpace(char c);

/* The output buffer must be at least 32 bytes long. */
void KLime_intToString(int32_t in, char *out, uint8_t base DEF_ARG(10));

#ifdef __cplusplus
}
#endif

#undef DEF_ARG
