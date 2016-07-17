#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#else
#endif

struct KLime_DescriptorEntry{
    uint32_t m_base_address;
    uint32_t m_length;
    uint8_t type;
};

bool KLime_setGlobalDescriptor(void *destination, const struct KLime_DescriptorEntry *entry);

#ifdef __cplusplus
}
#endif
