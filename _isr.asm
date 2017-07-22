;all the isr functions and a stub that 

section .text

global _isr_0
global _isr_1
global _isr_2
global _isr_3
global _isr_4
global _isr_5
global _isr_6
global _isr_7
global _isr_8
global _isr_9
global _isr_10
global _isr_11
global _isr_12
global _isr_13
global _isr_14
global _isr_15
global _isr_16
global _isr_17
global _isr_18
global _isr_19
global _isr_20
global _isr_21
global _isr_22
global _isr_23
global _isr_24
global _isr_25
global _isr_26
global _isr_27
global _isr_28
global _isr_29
global _isr_30
global _isr_31
global _irq_0
global _irq_1
global _irq_2
global _irq_3
global _irq_4
global _irq_5
global _irq_6
global _irq_7
global _irq_8
global _irq_9
global _irq_10
global _irq_11
global _irq_12
global _irq_13
global _irq_14
global _irq_15

_isr_0:
    cli    ;disable interrupts
    push 0 ;stub value/error code 
    push 0 ;divide by zero
    jmp common_isr
_isr_1:
    cli
    push 0 
    push 1 ;debug exception
    jmp common_isr
_isr_2:
    cli
    push 0
    push 2 ;non-maskable external interrupt
    jmp common_isr
_isr_3:
    cli
    push 0
    push 3 ;breakpoint
    jmp common_isr
_isr_4:
    cli
    push 0
    push 4
    jmp common_isr
_isr_5:
    cli
    push 0
    push 5 ;bound range exceeded
    jmp common_isr
_isr_6:
    cli
    push 0
    push 6 ;invalid opcode
    jmp common_isr
_isr_7:
    cli
    push 0
    push 7 ;device not available (x87 coprocessor)
    jmp common_isr 
_isr_8:
    cli
    push 8 ;double fault
_isr_9:
    cli
    push 0
    push 9 ;coprocessor segment overrun
_isr_10:
    cli
    push 10 ;invalid tss
    jmp common_isr
_isr_11:
    cli
    push 11 ;segment not present
    jmp common_isr
_isr_12:
    cli
    push 12 ;stack segment fault
    jmp common_isr
_isr_13:
    cli
    push 13 ;general protection fault
    jmp common_isr
_isr_14:
    cli
    push 14 ;page fault
    jmp common_isr
_isr_16:
    cli
    push 0
    push 16 ;floating point error
    jmp common_isr
_isr_17:
    cli
    push 17 ;alignment check
    jmp common_isr
_isr_18:
    cli
    push 0
    push 18 ;machine check
    jmp common_isr
_isr_19:
    cli
    push 0
    push 19 ;SIMD floating point error
    jmp common_isr
_isr_20:
    cli
    push 0
    push 20 ;virtualization exception
    jmp common_isr

;15 and 21 through 31 are reserved and unused on contemporary processors 
;so they're all treated the same with an ISR number of 15

_isr_15:
_isr_21:
_isr_22:
_isr_23:
_isr_24:
_isr_25:
_isr_26:
_isr_27:
_isr_28:
_isr_29:
_isr_30:
_isr_31:
    cli
    push 0
    push 15
    jmp common_isr

;IRQs have an ISR number ranging between 32 and 47 (0 + 32 to 15 + 32)

_irq_0:
    cli
    push 0
    push 32 
    jmp common_isr
_irq_1:
    cli
    push 0
    push 33
    jmp common_isr
_irq_2:
    cli
    push 0
    push 34
    jmp common_isr
_irq_3:
    cli
    push 0
    push 35
    jmp common_isr
_irq_4:
    cli
    push 0
    push 36
    jmp common_isr
_irq_5:
    cli
    push 0
    push 37
    jmp common_isr
_irq_6:
    cli
    push 0
    push 38
    jmp common_isr
_irq_7:
    cli
    push 0
    push 39
    jmp common_isr
_irq_8:
    cli
    push 0
    push 40
    jmp common_isr
_irq_9:
    cli
    push 0
    push 41
    jmp common_isr
_irq_10:
    cli
    push 0
    push 42
    jmp common_isr
_irq_11:
    cli
    push 0
    push 43
    jmp common_isr
_irq_12:
    cli
    push 0
    push 44
    jmp common_isr
_irq_13:
    cli
    push 0
    push 45
    jmp common_isr
_irq_14:
    cli
    push 0
    push 46
    jmp common_isr
_irq_15:
    cli
    push 0
    push 47
    jmp common_isr

;common handling code for all interrupt service routines
common_isr:
    pusha ;push all registers into the stack
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10 ;load ring-0 ds selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    extern interrupt_handler
    call interrupt_handler ;this calls interrupt_handler with the regs type as a parameter
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret




