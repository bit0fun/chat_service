CFLAGS 			=
CC 					= gcc
_DEPS 			= netfuncts.o database.o genfunct.o
DEPS				= $(patsubst %, $(ODIR)/%, $(_DEPS))
_OBJ				= chat_server.o
OBJ					= $(patsubst %, $(ODIR)/%, $(_OBJ))
TRG 				= chat_server
LIB					= ../lib
ODIR				= ../build

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all
all: $(TRG)

.PHONY: debugserv
debugserv: $(OBJ)
		$(CC) -g -o ../$@ $^ $(CFLAGS)

chat_server: $(OBJ) $(DEPS)
	gcc -o ../$@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
