#include <assert.h>
#include <stdint.h>
#include <stdio.h>

uint8_t reg[4] = {0};
uint8_t zf = 0;

void testar_add(void) {
    reg[0] = 250;
    reg[1] = 10;

    decode_execute(0x03, 0, 1);
    assert(reg[0] == 4);
}

void testar_sub(void) {
    reg[0] = 3;
    reg[1] = 5;

    decode_execute(0x04, 0, 1);
    assert(reg[0] == 254);
}

void testar_mov(void) {
    reg[1] = 77;
    reg[2] = 0;

    decode_execute(0x05, 2, 1);
    assert(reg[2] == 77);
}

void testar_cmp_iguais(void) {
    reg[0] = 77;
    reg[1] = 77;
    zf = 0;

    decode_execute(0x06, 0, 1);
    assert(zf == 1);
    assert(reg[0] == 77);
    assert(reg[1] == 77);
}

void testar_cmp_diferentes(void) {
    reg[0] = 77;
    reg[1] = 78;
    zf = 1;

    decode_execute(0x06, 0, 1);
    assert(zf == 0);
    assert(reg[0] == 77);
    assert(reg[1] == 78);
}

int main(void) {
    testar_add();
    testar_sub();
    testar_mov();
    testar_cmp_iguais();
    testar_cmp_diferentes();

    printf("Todos os testes da ULA passaram.\n");
    return 0;
}