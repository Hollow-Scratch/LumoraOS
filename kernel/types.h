#pragma once

using u64 = __UINT64_TYPE__;
using u32 = __UINT32_TYPE__;
using u16 = __UINT16_TYPE__;
using u8 = __UINT8_TYPE__;

using i64 = __INT64_TYPE__;
using i32 = __INT32_TYPE__;
using i16 = __INT16_TYPE__;
using i8 = __INT8_TYPE__;

using usize = __SIZE_TYPE__;
using isize = __PTRDIFF_TYPE__;
using uptr = __UINTPTR_TYPE__;

static_assert(sizeof(u8) == 1 && sizeof(i8) == 1);
static_assert(sizeof(u16) == 2 && sizeof(i16) == 2);
static_assert(sizeof(u32) == 4 && sizeof(i32) == 4);
static_assert(sizeof(u64) == 8 && sizeof(i64) == 8);
static_assert(sizeof(uptr) == sizeof(void *));
