#include "vga.h"
#include "klime_string.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BUFFER ((uint16_t *)0xB8000)

void KLime_VGA_terminalInit(struct KLime_VGA_Terminal *term){
    term->m_x = 0;
    term->m_y = 0;
    term->m_color = KLime_VGA_makeColor(kePink, keDarkGray);
    KLime_VGA_clearTerminal(term);
}

void KLime_VGA_clearTerminal(struct KLime_VGA_Terminal *term){
    const uint16_t blank_char = KLime_VGA_Character(' ', term->m_color);
    unsigned i = 0;
    for(; i < VGA_WIDTH * VGA_HEIGHT; i++){
        VGA_BUFFER[i] = blank_char;
    }
}

void KLime_VGA_terminalPutString(struct KLime_VGA_Terminal *term, const char *string){
    const uint64_t len = KLime_stringLength(string);
    unsigned i = 0;
    for(; i<len; i++){
        KLime_VGA_terminalPutChar(term, string[i]);
    }
}

void KLime_VGA_terminalPutStringWordWrap(struct KLime_VGA_Terminal *term, const char *string){
    while(*string!='\0'){
        uint16_t word_length = 0;
        while(!KLime_charIsSpace(string[word_length])){
            word_length++;
            if(string[word_length]=='\0'){
                KLime_VGA_terminalPutString(term, string);
                return;
            }
        }

        if((word_length < VGA_WIDTH) && (term->m_x + word_length >= VGA_WIDTH)){
            if(word_length==0){
                while(KLime_charIsSpace(*string))
                    string++;
                continue;
            }
            KLime_VGA_terminalNewLine(term);
        }
        else if(word_length==0)
            word_length = 1;
        else if(word_length >= VGA_WIDTH)
            KLime_VGA_terminalNewLine(term);
        
        {
            uint16_t i;
            for(i=0; i<word_length; i++)
                KLime_VGA_terminalPutChar(term, string[i]);
        }
        string += word_length;
    }
}

void KLime_VGA_terminalPutChar(struct KLime_VGA_Terminal *term, char c){
    switch(c){
        case '\n':
            do{
                KLime_VGA_terminalPutChar(term, ' ');
            }while(term->m_x);
            break;
        case '\t':
            do{
                KLime_VGA_terminalPutChar(term, ' ');
            }while(term->m_x%4);
            break;
        default:
            VGA_BUFFER[term->m_x + (term->m_y * VGA_WIDTH)] = KLime_VGA_Character(c, term->m_color);
                term->m_x++;
                if(term->m_x >= VGA_WIDTH){
                    KLime_VGA_terminalNewLine(term);
                }
            break;
    }
}

void KLime_VGA_terminalNewLine(struct KLime_VGA_Terminal *term){
    term->m_x = 0;
    if(++term->m_y > VGA_HEIGHT)
        term->m_y = 0;
}
