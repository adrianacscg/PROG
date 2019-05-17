#pragma once
#include "dependencies.h"

using namespace std;

class Address {
    private:
        string rua;
        int n_porta;
        string andar;
        string codigo_postal;
        string localidade;

    public:
        // @Constructors
        Address();
        Address(string street, int doorNumber, string floor, string postalCode, string location);

        // @Get Methods
        string getRua() const;
        int getNumPorta() const;
        string getAndar() const;
        string getCodigoPostal() const;
        string getLocalidade() const;

        // @Set Methods
        void setRua(string street);
        void setNumPorta(int doorNumber);
        void setAndar(string floor);
        void setCodigoPostal(string postalCode);
        void setLocalidade(string location);
};