CXX := g++
LD := ld

ARCH := x86-64
IMAGE_NAME := Lumora_$(ARCH)

BUILD_DIR := build
ISO_DIR := iso
LIMINE_DIR := limine-binary
LIMINE_TAR := limine-binary.tar.gz

KERNEL_SRC := kernel/kernel.cc kernel/ubsan.cc
KERNEL_OBJ := $(patsubst kernel/%.cc,$(BUILD_DIR)/%.o,$(KERNEL_SRC))
KERNEL_ELF := $(BUILD_DIR)/kernel.elf
ISO_IMAGE := $(BUILD_DIR)/$(IMAGE_NAME).iso

CXXFLAGS := -std=c++20 -O2 -Wall -Wextra \
    -ffreestanding -fno-exceptions -fno-rtti \
	-fsanitize=undefined -fno-sanitize=vptr \
    -march=x86-64 -mno-red-zone \
    -mno-sse -mno-sse2 -mno-mmx \
    -mcmodel=kernel -fno-stack-protector \
    -fno-pic -fno-pie -Ikernel

LDFLAGS := -nostdlib -static \
    -z max-page-size=0x1000 -T linker.lds

.PHONY: all kernel run clean distclean

all: kernel

# Fetch Limine bootloader binaries
$(LIMINE_TAR):
	curl -fL -o $@ https://github.com/limine-bootloader/limine/releases/latest/download/limine-binary.tar.gz

$(LIMINE_DIR)/limine.c: $(LIMINE_TAR)
	rm -rf $(LIMINE_DIR)
	gunzip < $(LIMINE_TAR) | tar -xf -
	touch -r $(LIMINE_TAR) $@

# Build kernel
kernel: $(KERNEL_ELF)
	@echo "LumoraOS kernel built successfully!"

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/%.o: kernel/%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(KERNEL_ELF): $(KERNEL_OBJ) linker.lds
	$(LD) $(LDFLAGS) $(KERNEL_OBJ) -o $@

# Create ISO and run QEMU
run: kernel $(LIMINE_DIR)/limine.c
	mkdir -p $(ISO_DIR)/boot/limine

	cp $(LIMINE_DIR)/BOOTX64.EFI $(ISO_DIR)/boot/limine/
	cp $(LIMINE_DIR)/limine-uefi-cd.bin $(ISO_DIR)/boot/
	cp $(LIMINE_DIR)/limine-bios-cd.bin $(ISO_DIR)/boot/
	cp $(LIMINE_DIR)/limine-bios.sys $(ISO_DIR)/boot/
	cp limine.conf $(ISO_DIR)/boot/
	cp $(KERNEL_ELF) $(ISO_DIR)/boot/kernel.elf

	xorriso -as mkisofs \
	    -b boot/limine-bios-cd.bin \
	    -no-emul-boot \
	    -boot-load-size 4 \
	    -boot-info-table \
	    --efi-boot boot/limine-uefi-cd.bin \
	    -efi-boot-part \
	    --efi-boot-image \
	    --protective-msdos-label \
	    $(ISO_DIR)/ \
	    -o $(ISO_IMAGE)

	qemu-system-x86_64 -bios /usr/share/edk2/x64/OVMF.4m.fd -cdrom $(ISO_IMAGE) -m 512M -boot d

# Clean build artifacts (keeps downloaded Limine archive)
clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR)
	@echo "Cleaned!"

# Clean everything including downloaded Limine files
distclean: clean
	rm -rf $(LIMINE_DIR) $(LIMINE_TAR)
	@echo "Distcleaned!"

