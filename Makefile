LIBS = $(wildcard libs/*) $(wildcard vendor/*)
INCLUDE_PATH = libs/
LINKER_LOCAL = -DLOG_USE_COLOR
LINKER_GLOBAL = -lSDL2 -lGL -lm

engine: libraries vendor
	cc app/engine.c $(wildcard libraries/*) -I$(INCLUDE_PATH) -o engine $(LINKER_GLOBAL)

libraries:
	mkdir libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		cc -c *.c -I ../ $(LINKER_LOCAL); \
		mv *.o ../../libraries; \
		cd -; \
	done

clean:
	rm -rf libraries/ engine