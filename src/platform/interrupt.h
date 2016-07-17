#pragma once

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

void *KLime_Debug_getInterruptTableLocation();
unsigned KLime_getNumberOfInterrupts();
void KLime_setInterruptHandler(unsigned which, void(*handler)(void));
void KLime_setupInterrupts();

typedef void(*KLime_InterruptHandler)(void);

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
    enum KLime_ExceptionType type) __attribute__((fastcall));

#ifdef __cplusplus
}
#endif
