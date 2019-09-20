#OBJS specifies which files to compile as part of the project
OBJS = 41_bitmap_fonts.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -ID:/dev/include/SDL2 -ID:/dev/include/SDL2_image -ID:/dev/include/SDL2_ttf -ID:/dev/include/SDL2_mixer

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LD:/dev/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -l SDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = 41_bitmap_fonts

#EXECUTE FILE DIR
OUTPUT_PATH = ../

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_PATH)$(OBJ_NAME)
	
.PHONY: clean
clean:
	rm $(OUTPUT_PATH)$(OBJ_NAME).exe