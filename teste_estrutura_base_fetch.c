#include <stdio.h>
#include <stdint.h>

// Variáveis globais
uint8_t mem[256] = {0};   // Memória: 256 bytes
uint8_t reg[4] = {0};     // Registradores: R0-R3
int pc = 0;           
uint8_t zf = 0;           
uint8_t running = 1;      
int ciclo = 0;            

// Busca instrução na memória e avança PC
void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
    *op = mem[pc];        
    *a = mem[pc + 1];     
    *b = mem[pc + 2];     
    pc += 3;              
}

// Laço principal de execução
void run() {
    uint8_t op, a, b;
    
    while (running && pc + 2 < 256) {
        ciclo++;
        fetch(&op, &a, &b);
        
        if (op == 0x0A) {  // HALT
            running = 0;
        }
    }
}

int main() {
    mem[0] = 0x05; mem[1] = 0x00; mem[2] = 50;
    mem[3] = 0x05; mem[4] = 0x01; mem[5] = 30;
    mem[6] = 0x0A; mem[7] = 0x00; mem[8] = 0x00;
    
    run();
    
    if (ciclo == 3 && pc == 9 && running == 0) {
        printf("✅ DUPLA 1 OK\n");
        printf("Ciclos: %d\n", ciclo);
        printf("PC: 0x%02X\n", (unsigned)pc);
        printf("running: %d\n", running);
        return 0;
    } else {
        printf("❌ ERRO\n");
        printf("Ciclos: %d (esperado 3)\n", ciclo);
        printf("PC: 0x%02X (esperado 0x09)\n", (unsigned)pc);
        printf("running: %d (esperado 0)\n", running);
        return 1;
    }
}
