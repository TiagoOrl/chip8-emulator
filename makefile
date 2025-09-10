


OBJECTS= ./build/chip8memory.o ./build/chip8stack.o
FLAGS= -g

all: ${OBJECTS}
	gcc -o main ${FLAGS} ./src/main.c ${OBJECTS} `sdl2-config --cflags --libs`


./build/chip8memory.o: ./src/chip8memory.c
	gcc -o ./build/chip8memory.o ${FLAGS} -c ./src/chip8memory.c

./build/chip8stack.o: ./src/chip8stack.c
	gcc -o ./build/chip8stack.o ${FLAGS} -c ./src/chip8stack.c

cl:
	rm -r ./bin/* ./build/* main
