
.c.o:
	$(XCC) $(XCCFLAGS) -c $*.c
.cpp.o:
	$(XCXX) $(XCXXFLAGS) -c $*.cpp
.s.o:
	$(XAS) $*.s $(XASFLAGS) -o $*.o

.IGNORE:clean
.PHONY:clean
.SILENT:clean
