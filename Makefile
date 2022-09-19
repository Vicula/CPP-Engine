build:
	clang++ -g -I"./libs/" src/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -llua -o engine;

run:
	./engine;

clean: 
	rm engine;