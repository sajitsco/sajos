
#include "cpu/isr.h"
#include "cpu/idt.h"
#include "drivers/vga.h"
#include "cpu/ports.h"

isr_t interrupt_handlers[256];
// Give string values for each exception
char *exception_messages[] = {
    "Division by Zero",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bat TSS",
    "Segment not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

// Install the ISR's to the IDT
void isr_install()
{
    set_idt_gate(0, (uint64_t)isr_0);
    set_idt_gate(1, (uint64_t)isr_1);
    set_idt_gate(2, (uint64_t)isr_2);
    set_idt_gate(3, (uint64_t)isr_3);
    set_idt_gate(4, (uint64_t)isr_4);
    set_idt_gate(5, (uint64_t)isr_5);
    set_idt_gate(6, (uint64_t)isr_6);
    set_idt_gate(7, (uint64_t)isr_7);
    set_idt_gate(8, (uint64_t)isr_8);
    set_idt_gate(9, (uint64_t)isr_9);
    set_idt_gate(10, (uint64_t)isr_10);
    set_idt_gate(11, (uint64_t)isr_11);
    set_idt_gate(12, (uint64_t)isr_12);
    set_idt_gate(13, (uint64_t)isr_13);
    set_idt_gate(14, (uint64_t)isr_14);
    set_idt_gate(15, (uint64_t)isr_15);
    set_idt_gate(16, (uint64_t)isr_16);
    set_idt_gate(17, (uint64_t)isr_17);
    set_idt_gate(18, (uint64_t)isr_18);
    set_idt_gate(19, (uint64_t)isr_19);
    set_idt_gate(20, (uint64_t)isr_20);
    set_idt_gate(21, (uint64_t)isr_21);
    set_idt_gate(22, (uint64_t)isr_22);
    set_idt_gate(23, (uint64_t)isr_23);
    set_idt_gate(24, (uint64_t)isr_24);
    set_idt_gate(25, (uint64_t)isr_25);
    set_idt_gate(26, (uint64_t)isr_26);
    set_idt_gate(27, (uint64_t)isr_27);
    set_idt_gate(28, (uint64_t)isr_28);
    set_idt_gate(29, (uint64_t)isr_29);
    set_idt_gate(30, (uint64_t)isr_30);
    set_idt_gate(31, (uint64_t)isr_31);

    set_idt_gate(32, (uint64_t)isr_32);
    set_idt_gate(33, (uint64_t)isr_33);

    /*set_idt_gate(34, (uint64_t)isr_34);
    set_idt_gate(35, (uint64_t)isr_34);
    set_idt_gate(36, (uint64_t)isr_34);
    set_idt_gate(37, (uint64_t)isr_34);
    set_idt_gate(38, (uint64_t)isr_34);
    set_idt_gate(39, (uint64_t)isr_34);

    set_idt_gate(40, (uint64_t)isr_35);
    set_idt_gate(41, (uint64_t)isr_35);
    set_idt_gate(42, (uint64_t)isr_35);
    set_idt_gate(43, (uint64_t)isr_35);
    set_idt_gate(44, (uint64_t)isr_35);
    set_idt_gate(45, (uint64_t)isr_35);
    set_idt_gate(46, (uint64_t)isr_35);
    set_idt_gate(47, (uint64_t)isr_35);
    set_idt_gate(48, (uint64_t)isr_35);
    set_idt_gate(49, (uint64_t)isr_35);
    set_idt_gate(50, (uint64_t)isr_35);*/
    // Remap the PIC

    // ICW1 - begin initialization
    byte_out(0x20, 0x11);
    byte_out(0xA0, 0x11);

    // ICW2 - remap offset address of idt_table */
    //
    // In x86 protected mode, we have to remap the PICs beyond 0x20 because
    // Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
    //
    byte_out(0x21, 0x20);
    byte_out(0xA1, 0x28);

    // unknown
    // byte_out(0x21, 0x04);
    // byte_out(0xA1, 0x02);

    // ICW3 - setup cascading
    byte_out(0x21, 0x0);
    byte_out(0xA1, 0x0);

    // ICW4 - environment info
    byte_out(0x21, 0x01);
    byte_out(0xA1, 0x01);

    // mask interrupts
    // byte_out(0x21, 0xff);
    // byte_out(0xA1, 0xff);

    // Get current master PIC interrupt mask
    // unsigned char curmask_master = byte_in(0x21);
    /* 0xFD is 11111101 - enables only IRQ1 (keyboard) on master pic
       by clearing bit 1. bit is clear for enabled and bit is set for disabled */
    // byte_out(0x21, curmask_master & 0xFD); // 0b11111101
    //  byte_out(0x21, 0b11111100);
    //     Load the IDT to the CPU
    set_idt();

    // Enable Interrupts
    __asm__ volatile("sti");
}

void isr_handler(registers regs)
{
    if (regs.int_no > 31)
    {
        putstr("\rReceived Interrupt: ", COLOR_WHT, COLOR_RED);
        const char *message = exception_messages[regs.int_no];
        putstr(message, COLOR_WHT, COLOR_RED);
    }
    else
    {
        if (regs.int_no == 32)
        {
            putstr("\rReceived Interrupt:  32 \n", COLOR_WHT, COLOR_RED);
        }
        else if (regs.int_no == 33)
        {
            uint8_t scancode = byte_in(0x60);
            putstr("\rReceived Interrupt:  33 \n", COLOR_WHT, COLOR_RED);
        }
        else if (regs.int_no == 34)
        {
            putstr("\rReceived Interrupt:  34 \n", COLOR_WHT, COLOR_RED);
        }
        else if (regs.int_no == 35)
        {
            putstr("\rReceived Interrupt:  35 \n", COLOR_WHT, COLOR_RED);
            byte_out(0xA0, 0x20);
        }

        byte_out(0x20, 0x20);
    }
}

void isr_handler2(registers regs)
{

    isr_t handler = interrupt_handlers[33];
    handler(&regs);
    byte_out(0x20, 0x20); /* leader */
}

int timer1 = 0;

void isr_handler32(registers regs)
{
    timer1++;
    byte_out(0x20, 0x20);
}

int get_timer()
{
    return timer1;
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void irq_handler(registers r)
{
    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(&r);
    }

    // EOI
    if (r.int_no >= 40)
    {
        byte_out(0xA0, 0x20); /* follower */
    }
    byte_out(0x20, 0x20); /* leader */
}