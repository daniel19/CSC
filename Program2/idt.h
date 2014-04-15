#ifndef IDT_H
#define IDT_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

struct idt_entry
{
    uint16_t base_low16;
    uint16_t selector;
    uint8_t always0;
    uint8_t access;
    uint16_t base_hi16;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

//single entry
void initIDTEntry(idt_entry_t *entry, uint32_t base, uint16_t selector, uint8_t access)
{
    //base_hi16 access  always0 selector    base_low16
    //63....48  47..40  39...32 31....16    16.......0

    //set up base address
    entry->base_low16 = (base & 0xFFFF); //set up low 16 bytes
    entry->base_hi16 = ((base >> 16) & 0xFFFF); //set up high 16 bytes
   
    entry->selector = selector; //set up selector
    entry->always0 = 0; //set always0 to 0
    entry->access = access; //set up access
}

void defaultIntHand()
{
    char msg[] = "DANGER!!! EXCEPTION ENCOUNTERED";
    protectedWrite(msg, 0, 0);
    while(1);
}

#endif
