################################################################################
# Declare some Makefile variables
################################################################################
CC = clang++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libraries/includes/"
LIBRARY_PATH = -L"./libraries/libs/"
SRC_FILES = ./libraries/libs/libglfw.3.3.dylib \
			./src/glad.c \
			./src/Main.cpp \
			./src/Engine/*.cpp \
			./src/Logger/*.cpp \
			./src/ECS/*.cpp \
			./src/Rendering/*.cpp \
			./src/Rendering/Shaders/*.cpp \
			./src/Rendering/Meshes/*.cpp \
			./src/Handlers/*.cpp \
			./src/Stores/*.cpp
LINKER_FLAGS = -lstd_image \
				-lGLFW \
				-llua
OBJ_NAME = engine

################################################################################
# Declare some Makefile rules
################################################################################
build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) -g $(INCLUDE_PATH) $(LIBRARY_PATH) $(SRC_FILES) -o $(OBJ_NAME) -framework OpenGl;

run:
	./$(OBJ_NAME);

clean: 
	rm $(OBJ_NAME);
	rm -rf $(OBJ_NAME).dSYM/;
	find ./src -type f ! -name "*.*" -not -path "*.dSYM/*" -exec rm -rf "$(basename {}).dSYM" \; -exec rm "$(basename {})" \;