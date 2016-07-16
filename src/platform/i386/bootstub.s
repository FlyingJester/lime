MBALIGN   equ 1<<0
MEMINFO   equ 1<<1
FLAGS     equ MBALIGN | MEMINFO
MAGIC     equ 0x1BADB002
CHECKSUM  equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 1048576
stack_top:

section .text
align 4

extern KLime_main
extern KLime_setupInterrupts

global _start
_start:
    mov esp, stack_top

    call KLime_setupInterrupts
    call KLime_main
    cli
.hang:
    hlt
    jmp .hang
