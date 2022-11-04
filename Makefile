################################################################################
# Declare some Makefile variables
################################################################################
CC = clang++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libraries/includes/"
SRC_FILES = ./src/glad.c \
			./src/*.cpp \
			./src/Engine/*.cpp \
			./src/Logger/*.cpp \
			./src/ECS/*.cpp \
			./src/Camera/*.cpp \
			./src/Handlers/*.cpp \
			./src/Models/**/*.cpp \
			./src/AssetStore/*.cpp
LINKER_FLAGS = -lSDL2 \
				-lSDL2_image \
				-lSDL2_ttf \
				-lSDL2_mixer -llua
OBJ_NAME = engine

################################################################################
# Declare some Makefile rules
################################################################################
build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME);

run:
	./$(OBJ_NAME);

clean: 
	rm $(OBJ_NAME);
	rm -rf $(OBJ_NAME).dSYM/;
	find ./src -type f ! -name "*.*" -not -path "*.dSYM/*" -exec rm -rf "$(basename {}).dSYM" \; -exec rm "$(basename {})" \;