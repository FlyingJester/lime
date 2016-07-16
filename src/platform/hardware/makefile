.include "../../lime.mk"

all: libklimehw.a
	install -C libklimehw.a $(BUILDDIR)

libklimehw.a: vga.o ${ls | fgrep .c} ${ls | fgrep .h}
	$(XAR) rvs libklimehw.a vga.o
	$(RANLIB) libklimehw.a

clean:
	rm *.a *.o

.SILENT: all
