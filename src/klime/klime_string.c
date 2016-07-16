#include "klime_string.h"

uint64_t KLime_stringLength(const char *str){
    uint64_t i = 0;
ks_strlen:
    if(str[i]==0)
        return i;
    else
        i++;
    goto ks_strlen;
}

bool KLime_charIsSpace(char c){
    switch(c){
        case '\n':
        case '\t':
        case '\r':
        case '\v':
        case ' ':
            return 1;
        default:
            return 0;
    }
}

static char klime_get_digit_char(uint8_t i, uint8_t base){
    const uint8_t c = i % base;
    if(c < 10)
        return '0' + c;
    else if(c < 36)
        return 'a' + c - 10;
    else if(c < 62)
        return 'A' + c - 36;
    else if(c == 62)
        return '_';
    else if(c == 63)
        return '+';

    return '?';
}

void KLime_intToString(int32_t in, char *output, uint8_t base){
    char buffer[32];
    const int max_buffer_index = 32;
    int buffer_index = max_buffer_index, output_index = 0;
    const bool negate = in < 0;

    if(negate)
        in = -in;
    else if(in == 0){
        output[0] = '0';
        output[1] = '\0';
        return;
    }

    /* We need to interate backwards first. */
    while(in){
        const char c = klime_get_digit_char(in, base);
        buffer[--buffer_index] = c; 
        in /= base;
    }

    if(negate)
        output[output_index++] = '-';

    while(buffer_index < max_buffer_index){
        output[output_index++] = buffer[buffer_index++];
    }

    output[output_index] = '\0';

}
