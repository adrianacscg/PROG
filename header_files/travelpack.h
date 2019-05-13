#pragma once
#include "dependencies.h"

using namespace std;

struct TravelPack {
    int id;
    string locais;
    Date data_inicio;
    Date data_fim;
    float preco;
    int lugares_max;
    int lugares_vendidos;
};