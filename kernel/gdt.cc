#include "gdt.h"

extern "C" void gdt_flush(u64 gdt_pointer_addr);

namespace Lumora::X86_64::GDT {

namespace {

alignas(16) GDTEntry gdt_entries[5];
GDTPointer gdt_pointer{};

constexpr void set_gdt_entry(usize index, GDTEntry entry) {
  gdt_entries[index] = entry;
}

} // namespace

void Init() {
  gdt_pointer.limit = sizeof(gdt_entries) - 1;
  gdt_pointer.base = reinterpret_cast<u64>(&gdt_entries);

  // 0x00: Null descriptor
  set_gdt_entry(0, {});

  // 0x08: Kernel code (Ring 0, Exec/Read, 64-bit Long Mode flag 0x20)
  set_gdt_entry(1, {.access = 0x9A, .granularity = 0x20});

  // 0x10: Kernel data (Ring 0, Read/Write)
  set_gdt_entry(2, {.access = 0x92, .granularity = 0x00});

  // 0x18: User data (Ring 3, Read/Write)
  set_gdt_entry(3, {.access = 0xF2, .granularity = 0x00});

  // 0x20: User code (Ring 3, Exec/Read, 64-bit Long Mode flag 0x20)
  set_gdt_entry(4, {.access = 0xFA, .granularity = 0x20});

  gdt_flush(reinterpret_cast<u64>(&gdt_pointer));
}

} // namespace Lumora::X86_64::GDT
