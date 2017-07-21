;this code deals with several things
; 1 - setting up an execution stack for the kernel under the .bss section
; 2 - setting up a fixed, read only global descriptor table (GDT)
; 3 - setting up an interrupt descriptor table (IDT) with empty entries (filling it is the responsibility of the kernel)
; 4 - calling kernel_main()

section .text

global environment
environment:
    cli ;disable interrupts, just in case (the system should start with the interrupt flag cleared)
stack_setup:
    mov esp, stack_bottom
gdt_setup:
    lgdt [gdtr] ;load the gdt register 
    mov ax, 0x08 ;load the first gdt selector for our code segment
    jmp 0x08:gdt_reload ;we're now using the code segment selector to jump
gdt_reload:
    mov ax, 0x10 ;load the second gdt selector for the data segments and stack segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
idt_setup:
    lidt [idtr] ;load the idt register
finish: ;we're done setting up the environment, we can jump to kernel main
    extern kmain
    jmp kmain ;jmp to kernel_main, a function defined elsewhere (typically C code) to indicate the beginning of our kernel

section .rodata

gdtr: ;the data to load into the gdt register
    gdt_limit dw 8*5 ;five entries
    gdt_base dd gd_table ;pointer to the gd_table in rodata

align 8
gd_table:
.gdt_e_null: ;null decriptor with data about the location and size of the GDT (this data isn't really important)
    dd gdt_limit
    dd gdt_base
.gdt_e_code_0: ;ring 0 code segment
    dw 0xffff
    dw 0
    db 0
    db 0x9a
    db 11001111b
    db 0
.gdt_e_data_0: ;ring 0 data segment
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 11001111b
    db 0
.gdt_e_code_3: ;ring 3 code segment
    dw 0xffff
    dw 0
    db 0
    db 0xfa
    db 11001111b
    db 0
.gdt_e_data_3: ;ring 3 data segment
    dw 0xffff
    dw 0
    db 0
    db 0xf2
    db 11001111b
    db 0

section .data

idtr: ;the data to load into the gdt register
    idt_limit dw 8*256 ;256 entries
    idt_base dd gd_table ;pointer to the idt in data

global _idt ;we want to export this symbol in order to later populate it elsewhere
align 8
_idt times 256 dq 0 ;an interrupt table with empty 256 entries

section .bss

stack_top:
resb 16384 ;reserve 16 KiB
stack_bottom: ;stacks grow downwards in memory