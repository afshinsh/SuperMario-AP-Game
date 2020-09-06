CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer


all: super_mario.out

super_mario.out: main.o mario.o my_map.o mushroom.o coin.o goomba.o rsdl.o
	$(CC) main.o rsdl.o mario.o my_map.o mushroom.o coin.o goomba.o $(CCFLAGS) -o super_mario.out

main.o: main.cpp 
	$(CC) -c main.cpp

mario.o: mario.cpp mario.h
	$(CC) -c mario.cpp

my_map.o: my_map.cpp my_map.h
	$(CC) -c my_map.cpp

mushroom.o: mushroom.cpp mushroom.h
	$(CC) -c mushroom.cpp

coin.o: coin.cpp coin.h
	$(CC) -c coin.cpp

goomba.o: goomba.cpp goomba.h
	$(CC) -c goomba.cpp

rsdl.o: rsdl.cpp rsdl.hpp
	$(CC) -c rsdl.cpp

.PHONY: clean
clean:
	rm *.o
