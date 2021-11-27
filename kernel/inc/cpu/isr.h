#ifndef __CPU_ISR
#define __CPU_ISR

#include <stdint.h>
// Define the ISR's for CPU exceptions
extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

extern void isr_32();
extern void isr_33();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

// Function to install the ISR's to the IDT and
// load the IDT to the CPU
void isr_install();

// Structure to push registers when saving for ISR
typedef struct
{
    uint64_t ds;
    uint64_t rdi, rsi, rbp, rsp, rdx, rcx, rbx, rax;
    uint64_t int_no, err_code;
    uint64_t rip, cs, eflags, useresp, ss;
} registers;

// One handler for all ISR's
void isr_handler(registers regs);
void isr_handler2(registers regs);
void isr_handler32(registers regs);

typedef void (*isr_t)(registers *regs);
void register_interrupt_handler(uint8_t n, isr_t handler);

int get_timer();

#endif