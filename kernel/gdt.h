#ifndef LUMORAOS_GDT_HEADER
#define LUMORAOS_GDT_HEADER

#include "types.h"

namespace Lumora::X86_64::GDT {

typedef struct [[gnu::packed]] GDTEntry {
  u16 limit_low;
  u16 base_low;
  u8 base_middle;
  u8 access;
  u8 granularity;
  u8 base_high;
} GDTEntry;

typedef struct [[gnu::packed]] GDTPointer {
  u16 limit;
  u64 base;
} GDTPointer;

void Init();

} // namespace Lumora::X86_64::GDT

#endif LUMORAOS_GDT_HEADER
