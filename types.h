#ifndef __types_h__
#define __types_h__

#define packed __attribute__((packed))
#define asmlinkage __attribute__((used,regparm(0)))

typedef unsigned char       byte;   //1 byte
typedef unsigned short      word;   //2 bytes
typedef unsigned int        dword;  //4 bytes
typedef unsigned long long  qword;  //8 bytes (cannot fit a register)
typedef unsigned int        size_t; //Alias for dword under 32 bit systems

struct regs
{
    dword gs, fs, es, ds;
    dword edi, esi, ebp, esp, ebx, edx, ecx, eax;
    dword int_no, err_code;
    dword eip, cs, eflags, useresp, ss;
} packed;

#endif