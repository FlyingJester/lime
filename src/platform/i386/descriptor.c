#include "descriptor.h"

/* A Global Descriptor Entry is described as:
 *
 * Byte | What
 *    0 | Length0
 *    1 | Length1
 *    2 | Address0
 *    3 | Address1
 *    4 | Address2
 *    5 | Type
 *    6 | Length2
 *    7 | Address3
 *
 *
 * Except that the most-significant 4 bits of byte 6 are devoted to length2. 
 * This very logical structure is to ensure compatibility with the 286, Apparently.
 */

bool KLime_setGlobalDescriptor(void *destination, const struct KLime_DescriptorEntry *entry){
    /* Some limits cannot be encoded. */
    uint32_t length = entry->m_length;
    uint8_t *out = destination;
    const uint8_t *const base = &entry->m_base_address, *const limit = &length;

    if(length > 0x10000 && (length & 0xFFF) != 0xFFF){
        return false;
    }
    if(length > 0x10000){
        limit >>= 12;
        out[6] = 0xC0;
    }
    else
        out[6] = 0x40;
    
    out[0] = limit[0];
    out[1] = limit[1];
    out[6] |= limit[2] & 0xF;
    
    out[2] = base[0];
    out[3] = base[1];
    out[4] = base[2];
    out[7] = base[3];

    out[5] = entry->type;

    return true;
}
