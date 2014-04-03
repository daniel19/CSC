#ifndef GDT_H
#define GDT_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

struct gdt_entry
{
    uint16_t low_limit;
    uint16_t low_base;
    uint8_t mid_base;
    uint8_t access;
    uint8_t attr;
    uint8_t high_base;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr
{
    uint16_t lim;
    uint32_t base;
} __attribute__((packed));

typedef struct gdt_ptr gdt_ptr_t;

void initGDTEntry(gdt_entry_t *entry, uint32_t baseAddress, uint32_t limit,
        uint8_t access, uint8_t attributes)
{
    entry->low_base = (baseAddress & 0xFFFF);
    entry->mid_base = ((baseAddress >> 16) & 0xFF);
    entry->high_base = ((baseAddress >> 24) & 0xFF);

    entry->low_limit = (limit & 0xFFFF);
    entry->attr = ((limit >> 16) & 0x0F);

    entry->attr = entry->attr | (attributes & 0xF0);

    entry->access = access;
}

#endif
