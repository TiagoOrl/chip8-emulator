
all:
	gcc -o main ./src/main.c `sdl2-config --cflags --libs`



cl:
	rm -r ./bin/* ./build/* main