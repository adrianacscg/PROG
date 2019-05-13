#pragma once
#include "dependencies.h"

using namespace std;

struct Client {
    string nome;
    int nif;
    int n_pessoas_agregado;
    Address morada;
    vector<TravelPack> pacotes_comprados;
};
