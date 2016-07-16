
all: install_klime

.c.o:
	$(XCC) $(XCCFLAGS) -c $*.c

libklime.a: klime_string.o
	$(XAR) rvs libklime.a klime_string.o
	$(XRANLIB) libklime.a

install_klime: libklime.a
	install -C libklime.a $(BUILDDIR)

.SILENT: clean all install_klime
.IGNORE: clean
.PHONY: clean

clean:
	rm *.a *.o
