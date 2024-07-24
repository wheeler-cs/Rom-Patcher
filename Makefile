CC=gcc
CFLAGS=-c -Wall -pedantic

INC=./inc
SRC=./src
BLD=./build

EXE=romPatcher

OBJECTS=main.o endian.o romPatcher.o

# === Program Target ===================================================================================================
all: $(OBJECTS)
	$(CC) $(BLD)/*.o -o $(BLD)/$(EXE)


# === Source File Targets ==============================================================================================
#main.o: $(SRC)/main.c $(INC)/romPatcher.h
#	$(CC) $(CFLAGS) $< -o $(BLD)/$@ -I$(INC)
#
#endian.o: $(SRC)/endian.c $(INC)/endian.h
#	$(CC) $(CFLAGS) $< -o $(BLD)/$@ -I$(INC)
$(OBJECTS): %.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $^ -o $(BLD)/$@ -I$(INC)

%.c:
	echo $@


# === Utility Targets ==================================================================================================
clean:
	rm $(BLD)/*.o
	rm $(BLD)/$(EXE)

run:
	$(BLD)/$(EXE)
