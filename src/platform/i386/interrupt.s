lime_num_interrupts equ 512

section .data
align 4

idt_start:
times lime_num_interrupts dq 0
idt_end:

os_interrupts_start:
times lime_num_interrupts dq 0
os_interrupts_end:

cside_exception_calls:
times 32 dd 0

section .text

extern KLime_timerInterruptHandler

global KLime_setupInterrupts
global KLime_Debug_getInterruptTableLocation

align 4

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ISR prologue and epilogue
%macro Lime_M_isrPrologue 0
    pushad
    cld
%endmacro

%macro Lime_M_isrEpilogue 0
    popad
    iret
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Create the exception handlers. These are just unrolled via preprocessing.
%assign i 0
%rep 32
KLime_exceceptionHandler %+ i:
    Lime_M_isrPrologue
    mov eax, cside_exception_calls + (i*4)
    ; Check if the execption caller has been defined. This isn't really the
    ; right thing to do, but it prevents jumps to wild memory.
    cmp eax, 0
    je exception_ %+ i %+ _failed
    call [eax]
exception_ %+ i %+ _failed:
    Lime_M_isrEpilogue
%assign i i+1
%endrep

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; interrupt descriptor definition
    struc   intr_desc
offset_1    resb 2 ; offset bits (unused?)
selector    resb 2 ; Code segment selector in GDT or IDT
unused_     resb 1 ; Definitely unused, for some reason.
attr        resb 1 ; Attributes
offset_2    resb 2 ; more offsets.
    endstruc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; The exceptions (first 32 interrupt vectors) are as so:
;
; +----+-----------+--------+-------+---------+
; | ## |   what    |  type  |  code | errcode |
; +----+-----------+--------+-------+---------+
; |  0 | Div By 0  | Fault  | #DE   | No      |
; |  1 | Debug     | ?      | #DB   | No      |
; |  2 | NMI       | Int    | ?     | No      |
; |  3 | Break     | Trap   | #BP   | No      |
; |  4 | Overflow  | Trap   | #OF   | No      |
; |  5 | Rng Error | Fault  | #BR   | No      |
; |  6 | Ill Instr | Fault  | #UD   | No      |
; |  7 | No Device | Fault  | #NM   | No      |
; |  8 | Dbl Err   | Abort  | #DF   | Yes     |
; |  9 | ?         | ?      | ?     | No      |
; | 10 | bad TSS   | Fault  | #TS   | Yes     |
; | 11 | No Seg    | Fault  | #NP   | Yes     |
; | 12 | Stack Seg | Fault  | #SS   | Yes     |
; | 13 | SegFault  | Fault  | #GP   | Yes     |
; | 14 | PageFault | Fault  | #PF   | Yes     |
; | 15 | ?         | ?      | ?     | ?       |
; | 16 | x87 Error | Fault  | #MF   | No      |
; | 17 | Align Chk | Fault  | #AC   | Yes     |
; | 18 | Machn Chk | Abort  | #MC   | No      |
; | 19 | SIMD Err  | Fault  | #XM   | No      |
; | 20 | Virt Err  | Fault  | #VE   | No      |
; | 21 | ?         | ?      |       | ?       |
; | 22 | ?         | ?      |       | ?       |
; | 23 | ?         | ?      |       | ?       |
; | 24 | ?         | ?      |       | ?       |
; | 25 | ?         | ?      |       | ?       |
; | 26 | ?         | ?      |       | ?       |
; | 27 | ?         | ?      |       | ?       |
; | 28 | ?         | ?      |       | ?       |
; | 29 | ?         | ?      |       | ?       |
; | 30 | Sec Error | ?      | #SE   | Yes     |
; | 31 | Trpl Err  | ?      |       | No      |
; +----+-----------+--------+-------+---------+
; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

KLime_setExceptionHandler: 

    ; Arguments: KLime_InterruptHandler handler, KLime_ExceptionType
    ; ecx is the handler address
    ; edx is the type
    ;
    ; The type pulls double duty as the exception index.

    cmp edx, 30 ; Slip the security error through the later <= 20 check
    je set_exc_ok

    ; If the error is greater than 20 (and wasn't 30) it's in the reserved block
    cmp edx, 20
    jg set_exc_bad

    ; Check for the two reserved exceptions under 20.
    cmp edx, 15 
    je set_exc_bad
    cmp edx, 9
    je set_exc_bad

set_exc_ok


    mov eax, 1
    ret

set_exc_bad:
    mov eax, 0
    ret

KLime_setupInterrupts:

    ; Make room for the IDT setup
    sub esp,6
    ; Setup the IDT
    mov [esp-6], word (512*8)
    mov [esp-4], dword idt_start

    lidt [esp-6]
    add esp,6
    ; Restore the stack after the IDT setup

    ; Set up the dummy exception handlers.
    %assign i 0
    %rep 32
        mov dword [cside_exception_calls + (i*4)], 0
    %assign i i+1
    %endrep

    ret

KLime_Debug_getInterruptTableLocation:
    mov eax, os_interrupts_start
    ret
