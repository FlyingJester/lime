#pragma once

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#if defined __GNUC__
#define LIME_FASTCALL __attribute__((fastcall))
#define LIME_CCALL __attribute__((cdecl))
#elif ( defined __WATCOMC__ ) || (defined MSC_VER_)
#define LIME_FASTCALL __fastcall
#define LIME_CCALL _cdecl
#endif

void *KLime_Debug_getInterruptTableLocation();
unsigned KLime_getNumberOfInterrupts();
void KLime_setInterruptHandler(unsigned which, void(*handler)(void));
void KLime_setupInterrupts();

/* Note that the code may or may not be meaningful */
typedef void(* LIME_CCALL KLime_InterruptHandler)(int code);

enum KLime_ExceptionType {
    keDivideByZero,
    keDebug,
    keNMI,
    keBreakPoint,
    keOverflow,
    keBoundsRangeError,
    keIllegalInstruction,
    keDoubleFault,
    keInvalidTSS = 0x0A,
    keSegmentMissing,
    keStackFault,
    keProtectionFault,
    kePageFault,
    keFPException = 0x10,
    keAlignmentCheck,
    keMachineFailure,
    keSIMDException,
    keVirtException,
    keSecurityException = 0x1E,
    keTripleFault = 0x20
};

bool KLime_setExceptionHandler(KLime_InterruptHandler handler,
    enum KLime_ExceptionType type) LIME_FASTCALL;

#ifdef __cplusplus
}
#endif
