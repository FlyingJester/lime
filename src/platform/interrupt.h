#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void *KLime_Debug_getInterruptTableLocation();
unsigned KLime_getNumberOfInterrupts();
void KLime_setInterruptHandler(unsigned which, void(*handler)(void));
void KLime_setupInterrupts();

#ifdef __cplusplus
}
#endif
