#pragma once
#include "dependencies.h"

using namespace std;

void loadPacotes();
void loadClientes();
void loadAgencia();
string morada_processada(Address morada);
void criar_cliente();
void novo_ficheiroClientes();
void alterar_cliente();
void remover_cliente();
void mudar_idInicial(int novo_id);
void criar_pacote();
void novo_ficheiroPacotes();
void alterar_pacote();
void remover_pacote();
void comprar_pacote();