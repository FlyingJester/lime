#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum KLime_VGA_Color {
    keBlack,
    keBlue,
    keGreen,
    keCyan,
    keRed,
    keMagenta,
    keBrown,
    keGray,
    keDarkGray,
    keLightBlue,
    keLightGreen,
    keLightCyan,
    kePink,
    kePurple,
    keTan,
    keWhite
};

struct KLime_VGA_Terminal{
    uint8_t m_x, m_y;
    enum KLime_VGA_Color m_color;
};

#define KLime_VGA_makeColor(FORE_, BACK_) (FORE_ | (BACK_ << 4))
#define KLime_VGA_Character(CHAR_, COLOR_) (((uint16_t)CHAR_) | (((uint16_t)COLOR_) << 8))

void KLime_VGA_terminalInit(struct KLime_VGA_Terminal *term);
void KLime_VGA_clearTerminal(struct KLime_VGA_Terminal *term);
void KLime_VGA_terminalPutString(struct KLime_VGA_Terminal *term, const char *string);
void KLime_VGA_terminalPutStringWordWrap(struct KLime_VGA_Terminal *term, const char *string);
void KLime_VGA_terminalPutChar(struct KLime_VGA_Terminal *term, char c);

/* Semi-private, ensures a new line is printed regardless of word wrap. */
void KLime_VGA_terminalNewLine(struct KLime_VGA_Terminal *term);


#ifdef __cplusplus
}
#endif
