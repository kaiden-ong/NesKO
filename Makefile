all:
	g++ -I src/include -L src/lib -o main NesKO.cpp nes/nes.cpp nes/cpu.cpp nes/ppu.cpp -lmingw32 -lSDL2main -lSDL2
