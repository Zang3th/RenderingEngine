# *** MACROS ***
CC = cc
LINK = -lSDL2 -lGL
OBJECT_FILES = engine.o sandbox.o window.o

# *** TARGETS ***
all: engine

%.o: %.c %.h
	$(CC) -c $^

engine:	$(OBJECT_FILES)
	$(CC) -o $@ $^ $(LINK)

clean:
	rm -rf *.o *.gch engine	