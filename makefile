OBJECTS= ./build/tootlib.o ./build/chip8screen.o ./build/chip8.o ./build/chip8memory.o ./build/chip8stack.o ./build/chip8keyboard.o
FLAGS= -g

all: ${OBJECTS}
	gcc -o main ${FLAGS} ./src/main.c ${OBJECTS} `sdl2-config --cflags --libs`


./build/chip8memory.o: ./src/chip8memory.c
	gcc -o ./build/chip8memory.o ${FLAGS} -c ./src/chip8memory.c

./build/chip8stack.o: ./src/chip8stack.c
	gcc -o ./build/chip8stack.o ${FLAGS} -c ./src/chip8stack.c


./build/chip8keyboard.o: ./src/chip8keyboard.c
	gcc -o ./build/chip8keyboard.o ${FLAGS} -c ./src/chip8keyboard.c

./build/chip8.o: ./src/chip8.c
	gcc -o ./build/chip8.o ${FLAGS} -c ./src/chip8.c

./build/chip8screen.o: ./src/chip8screen.c
	gcc -o ./build/chip8screen.o ${FLAGS} -c ./src/chip8screen.c

./build/tootlib.o: ./src/toot/tootlib.c
	gcc -o ./build/tootlib.o ${FLAGS} -c ./src/toot/tootlib.c


cl:
	rm -r ./bin/* ./build/* main
