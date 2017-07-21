#ifndef __types_h__
#define __types_h__

#define packed __attribute__((packed))
#define asmlinkage __attribute__((used,regparm(0)))

typedef unsigned char   byte;
typedef unsigned short  word;
typedef unsigned int    dword;
typedef unsigned long   qword;
typedef unsigned long   size_t; 

struct regs
{
    dword gs, fs, es, ds;
    dword edi, esi, ebp, esp, ebx, edx, ecx, eax;
    dword int_no, err_code;
    dword eip, cs, eflags, useresp, ss;
} packed;

#endif