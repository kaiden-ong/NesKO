#include <iostream>
#include <filesystem>
#include <string>
#include <SDL2/SDL.h>
using namespace std;

typedef enum {
    RUNNING,
    PAUSED,
    QUIT
} nes_state_t;

typedef struct {
    uint16_t ram[0xFFFF];
    uint16_t PC; // Program Counter
    uint8_t stack_pointer; 
    uint8_t A; // Accumulator
    uint8_t X; // Index Register
    uint8_t Y; // Index Register
    const char *romName;
} nes_t;

int main(int argc, char **argv) {
    
}