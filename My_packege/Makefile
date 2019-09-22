# ---------------------------------------------------------------------------
#                   commands
# ---------------------------------------------------------------------------
CC := g++
LINK := g++
RM := rm -rf
MV := mv
TAR := tar
MKDIR := mkdir


# ---------------------------------------------------------------------------
#                   settings
# ---------------------------------------------------------------------------
SRC_SUFFIX := .cpp
OBJ_SUFFIX := .o
LIB_SUFFIX := .a
BIN_SUFFIX := .exe
DLL_SUFFIX := .so

INC_PREFIX := -I
LIB_PREFIX := -L

OPT_C := -c
OPT_OUT := -o 
OPT_LINKOUT := -o 

CFLAGS := $(OPT_C)
LIBFLAGS := -Debug


# ---------------------------------------------------------------------------	
#                   directories
# ---------------------------------------------------------------------------
SRC_DIR := . ./Graphics ./Utils
OBJ_DIR := ./obj
INC_DIR := D:/dev/include/SDL2 D:/dev/include/SDL2_image D:/dev/include/SDL2_ttf D:/dev/include/SDL2_mixer
LIB_DIR := D:/dev/lib
BIN_DIR := ./bin/


# ---------------------------------------------------------------------------
#                   common settings
# ---------------------------------------------------------------------------
# 将所有SRC_DIR中的.cpp文件取出
SRCS := $(foreach var, $(SRC_DIR), $(wildcard $(var)/*$(SRC_SUFFIX)))

# 对SRC_DIR中的.cpp文件生成对应的.o文件名 放到其原本在的目录下
OBJS := $(patsubst %$(SRC_SUFFIX), %$(OBJ_SUFFIX),$(SRCS)) 

# 对SRC_DIR中的.cpp文件生成对应的.o文件名 放到OBJ_DIR下
#OBJS := $(foreach var, $(SRC_DIR), $(patsubst $(var)/%$(SRC_SUFFIX),$(OBJ_DIR)/%$(OBJ_SUFFIX),$(wildcard $(var)/*$(SRC_SUFFIX))))

# -I 
INCS := $(foreach var, $(INC_DIR), $(addprefix $(INC_PREFIX), $(var)))

# -L
LIBS := $(addprefix $(LIB_PREFIX), $(LIB_DIR))

# -l
LINKERS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w #-Wl,-subsystem,windows

TEMPFILES  := core core.* *$(OBJ_SUFFIX) temp.* *.out typescript*



# ---------------------------------------------------------------------------
#                   make rule
# ---------------------------------------------------------------------------
TARGET := test

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(BIN_DIR)$(TARGET)$(BIN_SUFFIX) $(OBJS)

$(TARGET):$(OBJS)
	$(LINK) $(OBJS) $(COMPILER_FLAGS) $(INCS) $(LIBS) $(LINKERS) $(OPT_LINKOUT)$(BIN_DIR)$(TARGET)$(BIN_SUFFIX)

$(OBJS):%.o:%.cpp
	$(CC) $(CFLAGS) $(COMPILER_FLAGS) $(INCS) $(LIBS) $(LINKERS) $(OPT_OUT)$@ $<

	