.include "../../lime.mk"

all: libklimearch.a kernel.ld
	install -C libklimearch.a $(BUILDDIR)
	install -C kernel.ld $(BUILDDIR)

ARCHLIBS=bootstub.o thread.o syscall.o interrupt.o

libklimearch.a: $(ARCHLIBS) ${ls | fgrep .s}
	$(XAR) rvs libklimearch.a $(ARCHLIBS)

clean:
	rm *.o *.a

.SILENT: all
