# ************************************************** MACROS ***********************************************************
LIBS_SANDBOX = $(wildcard libs/sandbox) 
LIBS_WRATHGL = $(wildcard libs/wrathGL) 
LIBS_2D = $(wildcard libs/engine-core/2D) $(wildcard libs/engine-core/general)
LIBS_3D = $(wildcard libs/engine-core/3D) $(wildcard libs/engine-core/general)
LIBS_VENDOR = $(wildcard vendor/*)
COMPILED_FILES_SANDBOX = $(wildcard compiled_sandbox/*) $(wildcard compiled_engine_2D/*) $(wildcard compiled_vendor/*)
COMPILED_FILES_WRATHGL = $(wildcard compiled_wrathGL/*) $(wildcard compiled_engine_3D/*) $(wildcard compiled_vendor/*)
INCLUDE_PATH = libs/
LINKER_VENDOR = -DLOG_USE_COLOR
LINKER_SANDBOX = -lSDL2 -lGL -lm -ldl -lfreetype -lchipmunk
LINKER_WRATHGL = -lglfw3 -lX11 -pthread -lGL -lm -ldl -lfreetype -lchipmunk
CC = cc
CFLAGS = -Wall -Wno-unused-variable -Wno-sizeof-pointer-memaccess

# ************************************************** DEMOS ************************************************************
sandboxDemo: compile_sandbox compile_2D compile_vendor
	$(CC) $(CFLAGS) app/sandboxDemo.c $(COMPILED_FILES_SANDBOX) -I$(INCLUDE_PATH) -o sandboxDemo $(LINKER_SANDBOX)

wrathGLDemo: compile_wrathGL compile_3D compile_vendor
	$(CC) $(CFLAGS) app/wrathGLDemo.c $(COMPILED_FILES_WRATHGL) -I$(INCLUDE_PATH) -o wrathGLDemo $(LINKER_WRATHGL)

sandboxDemoDebug: compile_sandbox compile_2D compile_vendor
	$(CC) $(CFLAGS) app/sandboxDemo.c $(COMPILED_FILES_SANDBOX) -I$(INCLUDE_PATH) -g -o sandboxDemoDebug $(LINKER_SANDBOX)

wrathGLDemoDebug: compile_wrathGL compile_3D compile_vendor
	$(CC) $(CFLAGS) app/wrathGLDemo.c $(COMPILED_FILES_WRATHGL) -I$(INCLUDE_PATH) -g -o wrathGLDemoDebug $(LINKER_WRATHGL)
	
# *********************************************** DIRS TO COMPILE *****************************************************
compile_sandbox:
	mkdir -p compiled_sandbox/
	for dir in $(LIBS_SANDBOX); do \
		cd $$dir; \
		$(CC) $(CFLAGS) -c *.c -I ../; \
		mv *.o ../../compiled_sandbox; \
		cd -; \
	done

compile_wrathGL:
	mkdir -p compiled_wrathGL/
	for dir in $(LIBS_WRATHGL); do \
		cd $$dir; \
		$(CC) $(CFLAGS) -c *.c -I ../; \
		mv *.o ../../compiled_wrathGL; \
		cd -; \
	done

compile_2D:
	mkdir -p compiled_engine_2D/
	for dir in $(LIBS_2D); do \
		cd $$dir; \
		$(CC) $(CFLAGS) -c *.c -I ../../; \
		mv *.o ../../../compiled_engine_2D; \
		cd -; \
	done

compile_3D:
	mkdir -p compiled_engine_3D/
	for dir in $(LIBS_3D); do \
		cd $$dir; \
		$(CC) $(CFLAGS) -c *.c -I ../../; \
		mv *.o ../../../compiled_engine_3D; \
		cd -; \
	done

compile_vendor:
	mkdir -p compiled_vendor/
	for dir in $(LIBS_VENDOR); do \
		cd $$dir; \
		$(CC) -c *.c -I ../ $(LINKER_VENDOR); \
		mv *.o ../../compiled_vendor; \
		cd -; \
	done

# *********************************************************************************************************************
clean:
	rm -rf compiled_sandbox/ compiled_wrathGL/ compiled_engine_2D/ compiled_engine_3D/ compiled_vendor/ sandboxDemo wrathGLDemo sandboxDemoDebug wrathGLDemoDebug