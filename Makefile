# *** MACROS
CC = cc

# *** TARGETS
engine: engine.o sandbox.o window.o
	$(CC) -o engine engine.o sandbox.o window.o -lSDL2 -lGL

engine.o: engine.c sandbox.h
	$(CC) -c engine.c

sandbox.o: sandbox.c sandbox.h window.h
	$(CC) -c sandbox.c

window.o: window.c window.h
	$(CC) -c window.c -lSDL2 -lGL

clean:
	rm -rf *.o