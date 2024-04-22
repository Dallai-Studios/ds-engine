#########################################################
##                 Makefile variables                  ##
#########################################################

CC = g++ 

COMPILER_FLAGS = -Wall -Wfatal-errors

TARGET_STD = -std=c++17

INCLUDES = -I"./libs/" \
		   -I"./engine/" \
		   -I"./libs/sdl2/include" \
		   -L"./libs/sdl2/lib" \
		   -L"./libs/lua"

SRC_FILES = src/*.cpp \
			src/engine/*.cpp \
			src/tools/logger/*.cpp \
			src/engine/ecs/*.cpp \
			src/engine/pipelines/graphics/*.cpp \

# the order here actually matters. SDL2main must be before SDL2 or else it will not compile
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OUTPUT = game

#########################################################
##                     Makefile rules                  ##
#########################################################

all:
	${CC} ${INCLUDES} ${COMPILER_FLAGS} ${TARGET_STD} ${SRC_FILES} ${LINKER_FLAGS} -o ${OUTPUT}

run: 
	./${OUTPUT}