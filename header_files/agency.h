#pragma once
#include "dependencies.h"

using namespace std;

struct Agency {
    string nome;
    int nif;
    Address morada;
    string url;
    vector<TravelPack> pacotes;
    vector<Client> clientes;
};
