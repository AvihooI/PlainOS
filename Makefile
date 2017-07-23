#
# Makefile for PlainOS
#
# Compiler: 	GCC 
# Assembler: 	NASM
# Linker: 		LD
#

TARGET := plainos.bin
ALL_OBJ :=  \
		_boot.o \
		_environment.o \
		_io.o \
		string.o \
		_isr.o \
		interrupts.o \
		terminal.o \
		kernel.o
ALL_DEP := $(patsubst %.o,.%.d,$(ALL_OBJ))

#Assembly configuration
NASM := nasm
ASM_FLAGS := -f elf32

#C compilation configuration
CC := gcc
CFLAGS := -std=gnu99 -m32 -ffreestanding -O2 -Wall -Wextra

#Linker configuration
LD := ld
LD_FLAGS := -m elf_i386 -T linker.ld

#All rules
.PHONY : all plainos clean
all : $(TARGET)
plainos : $(TARGET)

#Rules
%.o : %.c
	@echo " [C] $<"
	@$(CC) $(CFLAGS) -MMD -MF $(patsubst %.o, .%.d, $@) \
		-MT $(patsubst .%.d, %.o, $@) \
		-c -o $(patsubst .%.d, %.o, $@) $<

%.o : %.asm
	@echo " [NASM] $<"
	@$(NASM) $(ASM_FLAGS) $< -o $@	

plainos.bin: $(ALL_OBJ)
	@echo " [LD] $@"
	@$(LD) -o $@ $(LD_FLAGS) $^

clean:
	@echo "Cleaning directory"
	@rm -f $(ALL_DEP) $(ALL_OBJ)
	@rm -f $(TARGET)

ifneq ($(MAKECMDGOALS),clean)
-include $(ALL_DEP)
endif