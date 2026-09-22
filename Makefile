CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -g

PROGRAMS := minicpu teste_estrutura_base_fetch teste_memoria_fluxo teste_ula

.PHONY: all principal testes run run-testes clean help

all: $(PROGRAMS)

principal: minicpu

minicpu: structure.c
	$(CC) $(CFLAGS) $< -o $@

teste_estrutura_base_fetch: teste_estrutura_base_fetch.c
	$(CC) $(CFLAGS) $< -o $@

teste_memoria_fluxo: teste_memoria_fluxo.c
	$(CC) $(CFLAGS) $< -o $@

teste_ula: teste_ula.c
	$(CC) $(CFLAGS) $< -o $@

testes: teste_estrutura_base_fetch teste_memoria_fluxo teste_ula

run: minicpu
	./minicpu

run-testes: testes
	./teste_estrutura_base_fetch
	./teste_memoria_fluxo
	./teste_ula

clean:
	$(RM) $(PROGRAMS) $(addsuffix .exe,$(PROGRAMS))

help:
	@echo "make              - compila o simulador e todos os testes"
	@echo "make principal    - compila o programa principal"
	@echo "make testes       - compila apenas os testes"
	@echo "make run          - compila e executa o simulador"
	@echo "make run-testes   - compila e executa todos os testes"
	@echo "make clean        - remove os executaveis"