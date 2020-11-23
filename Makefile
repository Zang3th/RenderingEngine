LIBS = $(wildcard libs/*)
INCLUDE_PATH = libs/
LINKER = -lSDL2 -lGL

engine: libraries
	cc app/engine.c $(wildcard libraries/*) -I$(INCLUDE_PATH) -o engine $(LINKER)

libraries:
	mkdir libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		cc -c *.c -I../; \
		mv *.o ../../libraries; \
		cd -; \
	done

clean:
	rm -rf libraries/ engine