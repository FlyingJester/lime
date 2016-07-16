
export BUILDDIR=${PWD}

PDIR=${PWD}

KERNELLIBS=libklimehw.a libklimearch.a libklime.a
KERNELOBJS=klime_main.o klime_interrupts.o

.include "lime.mk"
.include "system.mk"

all: kernel
kernel: lime_kernel.bin

libklime.a: klime

klime:
	$(MAKE) -C klime

libklimehw.a: build_platform
libklimearch.a: build_platform

build_platform:
	$(MAKE) -C platform/$(ARCHTARGET)
	$(MAKE) -C platform/hardware

$(KERNELLIBS) kernel.ld: build_platform

lime_kernel.bin: $(KERNELLIBS) $(KERNELOBJS) platform/interrupt.h
	$(XLINK) $(XLINKFLAGS) $(KERNELOBJS) $(KERNELLIBS) -L./libgcc.a -T kernel.ld -o lime_kernel.bin 

.PHONY: build_platform clean klime kernel klime
.IGNORE:clean
.SILENT:build_platform clean klime

clean:
	rm *.a *.o *.bin *.ld
	$(MAKE) -C platform/$(ARCHTARGET) clean
	$(MAKE) -C platform/hardware clean
	$(MAKE) -C klime clean
