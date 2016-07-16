lime_num_interrupts equ 512

section .data
align 4

idt_start:
times lime_num_interrupts dq 0
idt_end:

os_interrupts_start:
times lime_num_interrupts dq 0
os_interrupts_end:

section .text

extern KLime_timerInterruptHandler

global KLime_setupInterrupts
global KLime_Debug_getInterruptTableLocation

align 4

; ISRs:
; 

; ISR prologue and epilogue
%macro Lime_M_isrPrologue 0
    pushad
    cld
%endmacro

%macro Lime_M_isrEpilogue 0
    popad
    iret
%endmacro

KLime_pitInterruptHandler:
    Lime_M_isrPrologue
    call KLime_timerInterruptHandler
    Lime_M_isrEpilogue


    struc   intr_desc
offset_1    resb 2 ; offset bits (unused?)
selector    resb 2 ; Code segment selector in GDT or IDT
unused_     resb 1 ; Definitely unused, for some reason.
attr        resb 1 ; Attributes
offset_2    resb 2 ; more offsets.
    endstruc

; Attributes are defined as so:
;   0-3: Gate type
;   4: Segment (0 for gates)
;   5-6: Privelege level
;   7: Present (0 for unused)
; 
; Type is defined as one of the following:
;   0x05: 32-bit (386) task gate
;
;   0x06: 16-bit (286) interrupt gate
;   0x07: 16-bit (286) trap gate
;
;   0x0E: 32-bit (386) interrupt gate
;   0x0F: 32-bit (386) trap gate
;
; Some interrupts are hard-coded:
;   0 is the timer interrupt from the PIC.
;
;
;
;
;
;
; While we are here, we can set the PIT's timer frequency to 250Hz, which is
; generally what we want. In the future, this should be made configurable at
; compile time.
; 

KLime_setupInterrupts:

    ; Make room for the IDT setup
    sub esp,6
    ; Setup the IDT
    mov [esp-6], word (512*8)
    mov [esp-4], dword idt_start

    lidt [esp]
    add esp,6
    ; Restore the stack after the IDT setup

    ; Set the PIT timer to be 250Hz.
    mov ecx, 0x40
    mov [ecx], dword 0x12B0

    ret

KLime_Debug_getInterruptTableLocation:
    mov eax, os_interrupts_start
    ret
