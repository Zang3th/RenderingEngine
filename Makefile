# ******************************************* MACROS ******************************************************
LIBS_SANDBOX = $(wildcard libs/sandbox) 
LIBS_2D = $(wildcard libs/engine-core/2D) $(wildcard libs/engine-core/general)
LIBS_3D = $(wildcard libs/engine-core/3D) $(wildcard libs/engine-core/general)
LIBS_VENDOR = $(wildcard vendor/*)
INCLUDE_PATH = libs/
LINKER_VENDOR = -DLOG_USE_COLOR
LINKER_SANDBOX = -lSDL2 -lGL -lm -ldl -lfreetype -lchipmunk
CC = cc
CFLAGS = -Wall -Wno-unused-variable -Wno-sizeof-pointer-memaccess
# ******************************************* DEMOS *******************************************************
sandboxDemo: compile_sandbox compile_2D compile_vendor
	$(CC) $(CFLAGS) app/sandboxDemo.c $(wildcard compiled/*) -I$(INCLUDE_PATH) -o sandboxDemo $(LINKER_SANDBOX)

wrathGLDemo:
	$(CC) $(CFLAGS) app/wrathGLDemo.c -o wrathGLDemo
# **************************************** DIRS TO COMPILE ************************************************
compile_sandbox:
	mkdir compiled/
	for dir in $(LIBS_SANDBOX); do \
		cd $$dir; \
		$(CC) $(CFLAGS) -c *.c -I ../; \
		mv *.o ../../compiled; \
		cd -; \
	done

compile_2D:
	for dir in $(LIBS_2D); do \
		cd $$dir; \
		$(CC) $(CFLAGS) -c *.c -I ../../; \
		mv *.o ../../../compiled; \
		cd -; \
	done

compile_3D:
	for dir in $(LIBS_3D); do \
		cd $$dir; \
		$(CC) $(CFLAGS) -c *.c -I ../../; \
		mv *.o ../../../compiled; \
		cd -; \
	done

compile_vendor:
	for dir in $(LIBS_VENDOR); do \
		cd $$dir; \
		$(CC) -c *.c -I ../ $(LINKER_VENDOR); \
		mv *.o ../../compiled; \
		cd -; \
	done
# *********************************************************************************************************
clean:
	rm -rf compiled/ sandboxDemo wrathGLDemo 