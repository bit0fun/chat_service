CFLAGS 			=
CC 					= gcc
DEPS 				= netfuncts.h genfunct.h database.h
ODIR				= ../build
OBJ				  = $(addprefix $(ODIR)/, netfuncts.o genfunct.o database.o)
TRG					= database.o netfuncts.o genfunct.o





$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $(ODIR)/$@ $< $(CFLAGS)


.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
