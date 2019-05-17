#pragma once
#include "dependencies.h"

using namespace std;

vector<string> morada_parser(string morada_linha);
vector<int> data_parser(string data_linha);
vector<int> idPacotes_parser(string idPacotes_linha);
string morada_guardar(Address morada);
string idPacotes_guardar(vector<TravelPack> vetor_pacotes);
string data_guardar(Date data);
vector<string> separa_destino_locais(string locais_string);
vector<string> getTodosOsLocais(vector<TravelPack> packs);
