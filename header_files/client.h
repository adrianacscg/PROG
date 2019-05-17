#pragma once
#include "dependencies.h"

using namespace std;

class Client {
    private:
        string nome;
        int nif, n_pessoas_agregado;
        Address morada;
        vector<TravelPack> pacotes_comprados;

    public:
        // @Constructors
        Client();
        Client(string name, int vat, int famNumber, Address address, vector<TravelPack> packsBought);

        // @Get Methods
        string getNome() const;
        int getNif() const;
        int getAgregadoFam() const;
        Address getMorada() const;
        vector<TravelPack> getPacotesComprados() const;

        // @Set Methods
        void setNome(string name);
        void setNif(int vat);
        void setAgregadoFam(int famNumber);
        void setMorada(Address address);
        void setPacotesComprados(vector<TravelPack> packsBought);
};
