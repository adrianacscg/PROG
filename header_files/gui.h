#pragma once
#include "dependencies.h"

using namespace std;

void menu_principal(int n_opcoes);
void menu_pacotes(int n_opcoes);
void menu_clientes(int n_opcoes);
int escolher_opcao(int n_op);
void retroceder(string menu);
void informacoes_agencia();
void informacoes_clientes();
void informacoes_cliente_especifico();
void informacoes_pacotes();
void informacoes_pacotes_vendidos();
void informacoes_pacotes_destino();
void informacoes_pacotes_entreDatas();
void informacoes_pacotes_destinoEentreDatas();

