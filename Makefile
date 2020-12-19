LIBS = $(wildcard libs/*) $(wildcard vendor/*)
INCLUDE_PATH = libs/
LINKER_LOCAL = -DLOG_USE_COLOR
LINKER_GLOBAL = -lSDL2 -lGL -lm -ldl -lfreetype
CC = cc
CFLAGS = -Wall -Wno-unused-variable

engine: libraries vendor
	$(CC) $(CFLAGS) app/engine.c $(wildcard libraries/*) -I$(INCLUDE_PATH) -o engine $(LINKER_GLOBAL)

libraries:
	mkdir libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		$(CC) -c *.c -I ../ $(LINKER_LOCAL); \
		mv *.o ../../libraries; \
		cd -; \
	done

debug: libraries vendor
	$(CC) app/engine.c $(wildcard libraries/*) -I$(INCLUDE_PATH) -g -o engine $(LINKER_GLOBAL)

clean:
	rm -rf libraries/ engine