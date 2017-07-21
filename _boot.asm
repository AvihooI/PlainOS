;this code deals with making the kernel multiboot compliant as well as passing on responsibility to _envrionment.asm
bits 32 ;we're assembling 32 bit code, this is optional seeing as we already specify to NASM we're assembling in 32 bit format

MAGIC equ 0x1BADB002 ;multiboot magic value
FLAGS equ 1 | 16 ;page aligned, aout kludge
CHECKSUM equ -(MAGIC + FLAGS) ;checksum - this scheme is used to make sure we don't get an overflow
extern bss, end, code ;all the relevant sections and labels

section .text

multiboot:
dd MAGIC ;magic value to indicate the beginning of the multiboot header
dd FLAGS ;the flags telling the bootloader what state we want to start in
dd CHECKSUM ;checksum to allow the bootloader to verify the magic value wasn't inserted by chance 
dd multiboot ;the entry point of the multiboot header (I'm not sure why multiboot requires this)
dd code ;the beginning of the code section
dd bss ;the beginning of the bss section
dd end ;the end of our kernel binary
dd start ;the beginning of our kernel binary, where the first instruction in the kernel begins

;the boot responsibility is over and it's passed on to _environment.asm
global start
start:
    extern environment 
    jmp environment
