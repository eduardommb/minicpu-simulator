#include <stdio.h>
#include <stdint.h>
#include <assert.h>

uint8_t mem[256] = {0};
uint8_t reg[4] = {0};
uint8_t pc = 0;
uint8_t zf = 0;
uint8_t running = 1;

void load(uint8_t a, uint8_t b) {
    reg[a] = mem[b];
}

void store(uint8_t a, uint8_t b) {
    mem[b] = reg[a];
}

void jmp(uint8_t a) {
    pc = a;
}

void jz(uint8_t a) {
    if (zf) {
        pc = a;
    }
}

void jnz(uint8_t a) {
    if (!zf) {
        pc = a;
    }
}

void halt(void) {
    running = 0;
}

void decode_execute_3(uint8_t op, uint8_t a, uint8_t b) {
    if (op == 0x01) {
        load(a, b);
    }
    else if (op == 0x02) {
        store(a, b);
    }
    else if (op == 0x07) {
        jmp(a);
    }
    else if (op == 0x08) {
        jz(a);
    }
    else if (op == 0x09) {
        jnz(a);
    }
    else if (op == 0x0A) {
        halt();
    }
}

void testar_load(void) {
    mem[0x25] = 89;
    reg[0] = 0;
    decode_execute_3(0x01, 0, 0x25);
    assert(reg[0] == 89);
}

void testar_store(void) {
    reg[1] = 42;
    mem[0x30] = 0;
    decode_execute_3(0x02, 1, 0x30);
    assert(mem[0x30] == 42);
}

void testar_jmp(void) {
    pc = 0x05;
    decode_execute_3(0x07, 0x50, 0x00);
    assert(pc == 0x50);
}

void testar_jz(void) {
    pc = 0x10;
    zf = 0;
    decode_execute_3(0x08, 0x60, 0x00);
    assert(pc == 0x10);

    zf = 1;
    decode_execute_3(0x08, 0x60, 0x00);
    assert(pc == 0x60);
}

void testar_jnz(void) {
    pc = 0x10;
    zf = 1;
    decode_execute_3(0x09, 0x70, 0x00);
    assert(pc == 0x10);

    zf = 0;
    decode_execute_3(0x09, 0x70, 0x00);
    assert(pc == 0x70);
}

void testar_halt(void) {
    running = 1;
    decode_execute_3(0x0A, 0x00, 0x00);
    assert(running == 0);
}

int main(void) {
    testar_load();
    testar_store();
    testar_jmp();
    testar_jz();
    testar_jnz();
    testar_halt();

    printf("OK\n");
    return 0;
}
