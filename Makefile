#########################################################
##                 Makefile variables                  ##
#########################################################

CC = g++ 

COMPILER_FLAGS = -Wall -Wfatal-errors

TARGET_STD = -Wall -std=c++17

INCLUDES = -I"./libs/" \
		   -I"./libs/sdl2/include" \
		   -L"./libs/sdl2/lib"

SRC_FILES = src/*.cpp \
			src/game/*.cpp

# the order here actually matters. SDL2main must be before SDL2 or else it will not compile
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

OUTPUT = game

#########################################################
##                     Makefile rules                  ##
#########################################################

all:
	${CC} ${INCLUDES} ${COMPILER_FLAGS} ${TARGET_STD} ${SRC_FILES} ${LINKER_FLAGS} -o ${OUTPUT}

run: 
	./${OUTPUT}