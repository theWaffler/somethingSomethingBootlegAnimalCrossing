.PHONY: all clean

# Define default platform: PLATFORM_DESKTOP or PLATFORM_WEB
PLATFORM ?= PLATFORM_DESKTOP

# Define default C++ compiler: g++ or emcc (for WebAssembly)
ifeq ($(PLATFORM),PLATFORM_WEB)
    CC = emcc
    CFLAGS = -std=c++11 -Wall -Wno-missing-braces -Wno-unused-value $(PROJECT_CUSTOM_FLAGS)
    LDFLAGS = -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
    EXT = .html
else
    CC = g++
    CFLAGS = -std=c++11 -Wall -Wno-missing-braces -Wno-unused-value -D_DEFAULT_SOURCE $(PROJECT_CUSTOM_FLAGS)
    LDFLAGS = -L/usr/lib
    EXT = 
endif

# Include and library paths
INCLUDE_PATHS += -I. -I/usr/include

# Define project variables
PROJECT_NAME = raylib_game
PROJECT_SOURCE_FILES = main.cpp
PROJECT_BUILD_PATH = .

# Define libraries required for linking (Desktop and Web have different libraries)
ifeq ($(PLATFORM),PLATFORM_WEB)
    LDLIBS = $(RAYLIB_LIB_PATH)/libraylib.a
else
    LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Define object files
OBJS = $(patsubst %.cpp, %.o, $(PROJECT_SOURCE_FILES))

# Default target entry
all: $(PROJECT_NAME)

# Project target defined by PROJECT_NAME
$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_BUILD_PATH)/$(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile C++ source files
%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS)

# Clean everything
clean:
	rm -f *.o $(PROJECT_BUILD_PATH)/$(PROJECT_NAME)$(EXT)
	@echo Cleaning done

