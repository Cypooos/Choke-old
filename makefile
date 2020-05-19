GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386
QEMUPARAMS = -d guest_errors

objects = obj/compiled/loader.o \
					obj/compiled/common/includer.o \
          obj/compiled/gdt.o \
          obj/compiled/drivers/driver.o \
          obj/compiled/hardwarecommunication/port.o \
          obj/compiled/hardwarecommunication/interruptstubs.o \
          obj/compiled/hardwarecommunication/interrupts.o \
          obj/compiled/hardwarecommunication/pci.o \
					obj/compiled/drivers/keyboard.o \
          obj/compiled/drivers/mouse.o \
          obj/compiled/drivers/vga.o \
				 	obj/compiled/gui/widget.o \
				 	obj/compiled/gui/desktop.o \
				 	obj/compiled/gui/window.o \
          obj/compiled/kernel.o \
          obj/compiled/multitasking.o \
          obj/compiled/textgui/tgm.o \
          obj/compiled/textgui/desktop.o \
          obj/compiled/memorymanagement.o

run: GenOS.iso
	qemu-system-x86_64 -cdrom obj/GenOS.iso $(QEMUPARAMS)

obj/compiled/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/compiled/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

GenOS.iso: linker.ld $(objects)
		ld $(LDPARAMS) -T $< -o obj/GenOS.bin $(objects)
		cp -r data/* obj/iso/
		cp obj/GenOS.bin obj/iso/boot/
		grub-mkrescue --output=obj/GenOS.iso obj/iso

install: GENOS.bin
	sudo cp $< /boot/GenOS.bin

.PHONY: clear
clear:
		rm -r obj/compiled/* obj/iso/* obj/GenOS.bin obj/GenOS.iso



.PHONY: clean
clean:
	rm -r obj/compiled/*
