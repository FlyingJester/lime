#include "platform/hardware/vga.h"
#include "platform/interrupt.h"
#include "klime_string.h"
#include <stdint.h>


static const char *license_text1 =
"\
Permission to use, copy, modify, and/or distribute this software for any \
purpose with or without fee is hereby granted, provided that the above \
copyright notice and this permission notice appear in all copies. \
";

static const char *license_text2 = 
"\
THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL WARRANTIES \
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF \
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR \
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES \
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN \
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF \
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\
";

template<typename T>
static void print_address(KLime_VGA_Terminal &term, T x, const char *what){
    char buffer[34] = { '0', 'x' };

    KLime_VGA_terminalNewLine(&term);
    KLime_intToString((unsigned)x, buffer + 2, 16);
    KLime_VGA_terminalPutStringWordWrap(&term, "The ");
    KLime_VGA_terminalPutStringWordWrap(&term, what);
    KLime_VGA_terminalPutStringWordWrap(&term, " is at ");
    KLime_VGA_terminalPutStringWordWrap(&term, buffer);

    KLime_VGA_terminalNewLine(&term);
}

extern "C"
void KLime_main(){
    KLime_VGA_Terminal term;
    KLime_VGA_terminalInit(&term);

    KLime_setupInterrupts();

    KLime_VGA_terminalPutStringWordWrap(&term, "Starting Lime Operating system version 0.01\n"\
    "\tCopyright (c) 2016 Martin McDonough\n"\
    "\t\n");
    KLime_VGA_terminalPutStringWordWrap(&term, license_text1);
    KLime_VGA_terminalNewLine(&term);
    KLime_VGA_terminalNewLine(&term);
    KLime_VGA_terminalPutStringWordWrap(&term, license_text2);


    for(unsigned i = 0; i < 32; i++){
        if(i%8 == 0)
            KLime_VGA_terminalNewLine(&term);
        
        const char *const value = KLime_setExceptionHandler((KLime_InterruptHandler)0, (KLime_ExceptionType)i) ? "Y" : "N";
        char buffer[8];
        KLime_intToString(i, buffer, 10);
        if(buffer[1] == '\0'){
            buffer[1] = ' ';
            buffer[2] = '\0';
        }
        KLime_VGA_terminalPutStringWordWrap(&term, buffer);
        KLime_VGA_terminalPutStringWordWrap(&term, ": (");
        KLime_VGA_terminalPutStringWordWrap(&term, value);
        KLime_VGA_terminalPutStringWordWrap(&term, ") ");
    }

}
