PROGRAM = list.out
C       = gcc
CFLAGS  = -g -Wno-return-local-addr

$(PROGRAM): main.c
	$(C) $(CFLAGS) -o $@ $<

.PHONY: clean

clean: 
	rm $(PROGRAM)
