.include "../../lime.mk"

all: libklimearch.a kernel.ld
	install -C libklimearch.a $(BUILDDIR)
	install -C kernel.ld $(BUILDDIR)

ARCHOBJS=bootstub.o thread.o syscall.o interrupt.o descriptor.o

libklimearch.a: $(ARCHOBJS) ${ls | fgrep .s}
	$(XAR) rvs libklimearch.a $(ARCHOBJS)

clean:
	rm *.o *.a

.SILENT: all
