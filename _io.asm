section .text

global outb
outb:
    mov eax, [esp+8] ;get the value parameter
    mov edx, [esp+4] ;get the port parameter
    out dx, al ;put the value in the port
    ret

global inb
inb:
    mov edx, [esp+4] ;get the port parameter
    in al, dx ;put the value within the port into the return register
    ret