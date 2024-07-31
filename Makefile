all:
	g++ -I src/include -L src/lib -o main NesKO.cpp -lmingw32 -lSDL2main -lSDL2
