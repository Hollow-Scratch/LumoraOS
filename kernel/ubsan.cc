#include <cstdint>

extern "C" {

static void ubsan_panic(const char *msg) {
  // TODO: Print 'msg' to your framebuffer or serial port (COM1)
  asm volatile("cli");
  for (;;) {
    asm volatile("hlt");
  }
}

void __ubsan_handle_type_mismatch_v1(void *, void *) {
  ubsan_panic("UBSan: type mismatch");
}
void __ubsan_handle_pointer_overflow(void *, void *, void *) {
  ubsan_panic("UBSan: pointer overflow");
}
void __ubsan_handle_shift_out_of_bounds(void *, void *, void *) {
  ubsan_panic("UBSan: shift out of bounds");
}
void __ubsan_handle_divrem_overflow(void *, void *, void *) {
  ubsan_panic("UBSan: divrem overflow");
}
void __ubsan_handle_out_of_bounds(void *, void *) {
  ubsan_panic("UBSan: out of bounds");
}
void __ubsan_handle_add_overflow(void *, void *, void *) {
  ubsan_panic("UBSan: add overflow");
}
void __ubsan_handle_sub_overflow(void *, void *, void *) {
  ubsan_panic("UBSan: sub overflow");
}
void __ubsan_handle_mul_overflow(void *, void *, void *) {
  ubsan_panic("UBSan: mul overflow");
}
void __ubsan_handle_negate_overflow(void *, void *) {
  ubsan_panic("UBSan: negate overflow");
}
void __ubsan_handle_load_invalid_value(void *, void *) {
  ubsan_panic("UBSan: invalid load");
}
void __ubsan_handle_nonnull_arg(void *) { ubsan_panic("UBSan: nonnull arg"); }
void __ubsan_handle_nonnull_return_v1(void *, void *) {
  ubsan_panic("UBSan: nonnull return");
}
void __ubsan_handle_builtin_unreachable(void *) {
  ubsan_panic("UBSan: unreachable");
}

void __ubsan_handle_function_type_mismatch(void *data, void *fn) {
  (void)data;
  (void)fn;
  ubsan_panic("function type mismatch");
}

void __ubsan_handle_function_type_mismatch_abort(void *data, void *fn) {
  (void)data;
  (void)fn;
  ubsan_panic("function type mismatch");
}
}
