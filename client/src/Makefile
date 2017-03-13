CFLAGS 			=
CC 					= gcc
_DEPS 			= netfuncts.o genfunct.o
DEPS				= $(patsubst %, $(ODIR)/%, $(_DEPS))
_OBJ				= chat_client.o
OBJ					= $(patsubst %, $(ODIR)/%, $(_OBJ))
TRG 				= chat_client
LIB					= ../lib
ODIR				= ../build

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all
all: $(TRG)

.PHONY: debugcli
debugcli: $(OBJ)
	$(CC)  -pthread -g -o ../$@  $^ $(CFLAGS) $(DEPS)

chat_client: $(OBJ)
	$(CC) -pthread -o ../$@ $^ $(CFLAGS) $(DEPS)


.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
