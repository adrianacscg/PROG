#include "dependencies.h"

using namespace std;

// Recebe a uma string com a morada como
// está nos ficheiros e retorna-a separada
// nos vários elementos
vector<string> morada_parser(string morada_linha) {
    vector<string> morada_valores;
    string elemento;
    string delimiter = " / ";
    size_t pos;

    while ((pos = morada_linha.find(delimiter)) != string::npos) {
        elemento = morada_linha.substr(0, pos);
        morada_valores.push_back(elemento);
        morada_linha.erase(0, pos + delimiter.length());
    }
    elemento = morada_linha.substr(0, pos);
    morada_valores.push_back(elemento);

    return morada_valores;
}


// Recebe uma string com a data como
// está nos ficheiros e retorna-a separada
// nos 3 elementos (ano, mês, dia)
vector<int> data_parser(string data_linha) {
    vector<int> data_valores;
    string elemento;
    string delimiter = "/";
    size_t pos;

    while ((pos = data_linha.find(delimiter)) != string::npos) {
        elemento = data_linha.substr(0, pos);
        data_valores.push_back(stoi(elemento));
        data_linha.erase(0, pos + delimiter.length());
    }
    elemento = data_linha.substr(0, pos);
    data_valores.push_back(stoi(elemento));

    return data_valores;
}


// Função que retorna um vetor ordenado
// com todos os ids dos pacotes existentes
// no parâmetro
vector<int> idPacotes_parser(string idPacotes_linha) {
    vector<int> idPacotes_valores;
    string elemento;
    string delimiter = " ; ";
    size_t pos;

    if (idPacotes_linha == "NENHUM PACOTE COMPRADO")
        return idPacotes_valores;

    while ((pos = idPacotes_linha.find(delimiter)) != string::npos) {
        elemento = idPacotes_linha.substr(0, pos);
        idPacotes_valores.push_back(stoi(elemento));
        idPacotes_linha.erase(0, pos + delimiter.length());
    }
    elemento = idPacotes_linha.substr(0, pos);
    idPacotes_valores.push_back(stoi(elemento));

    sort(idPacotes_valores.begin(), idPacotes_valores.end());

    return idPacotes_valores;
}


// Função recebe uma Address e devolve
// uma string no formato correto para
// guardar no ficheiro
string morada_guardar(Address morada) {
    stringstream morada_ss;

    morada_ss << morada.getRua() << " / " << morada.getNumPorta() << " / " << morada.getAndar() << " / "
              << morada.getCodigoPostal() << " / " << morada.getLocalidade();

    return morada_ss.str();
}


// Função que recebe um vetor de pacotes e retorna
// uma string com os ids para guardar no ficheiro
string idPacotes_guardar(vector<TravelPack> vetor_pacotes) {
    stringstream idPacotes_ss;

    if (vetor_pacotes.empty())
        idPacotes_ss << "NENHUM PACOTE COMPRADO";
    else if (vetor_pacotes.size() == 1)
        idPacotes_ss << abs(vetor_pacotes[0].id);
    else {
        idPacotes_ss << abs(vetor_pacotes[0].id);

        for (size_t i = 1; i < vetor_pacotes.size(); i++) {
            idPacotes_ss << " ; " << abs(vetor_pacotes[i].id);
        }
    }

    return idPacotes_ss.str();
}


// Função recebe uma Data e devolve
// uma string no formato YYYY/MM/DD
string data_guardar(Date data) {
    stringstream data_ss;

    data_ss << data.getAno() << "/";

    if (data.getMes() > 9) data_ss << data.getMes() << "/";
    else data_ss << "0" << data.getMes() << "/";

    if (data.getDia() > 9) data_ss << data.getDia();
    else data_ss << "0" << data.getDia();

    return data_ss.str();
}


// Função que devolve um vetor com 2 elementos (destino e locais)
vector<string> separa_destino_locais(string locais_string) {
    vector<string> destino_locais;
    string elemento;
    string delimiter = " - ";
    size_t pos;

    while ((pos = locais_string.find(delimiter)) != string::npos) {
        elemento = locais_string.substr(0, pos);
        destino_locais.push_back(elemento);
        locais_string.erase(0, pos + delimiter.length());
    }
    elemento = locais_string.substr(0, pos);
    destino_locais.push_back(elemento);

    return destino_locais;
}
