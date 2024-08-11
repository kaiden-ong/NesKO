all:
	g++ -I src/include -L src/lib -o main NesKO.cpp src/nes.cpp src/cpu.cpp -lmingw32 -lSDL2main -lSDL2
