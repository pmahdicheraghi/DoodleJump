CC := g++ --std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

doodleJump.out: main.o rsdl.o doodler.o objects.o
	$(CC) main.o rsdl.o doodler.o objects.o $(CCFLAGS) -o doodleJump.out

main.o: main.cpp RSDL/src/rsdl.hpp doodler.hpp objects.hpp
	$(CC) -c main.cpp -o main.o

doodler.o: doodler.cpp doodler.hpp structs.hpp
	$(CC) -c doodler.cpp -o doodler.o

objects.o: objects.cpp objects.hpp structs.hpp
	$(CC) -c objects.cpp -o objects.o

rsdl.o: RSDL/src/rsdl.hpp RSDL/src/rsdl.cpp
	$(CC) -c RSDL/src/rsdl.cpp -o rsdl.o

clean:
	rm -r *.o
