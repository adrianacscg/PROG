#pragma once
#include "dependencies.h"

using namespace std;

class Date {
    private:
        int dia, mes, ano;

    public:
        // @Constructors
        Date();
        Date(int d, int m, int a);


        // @Get Methods
        int getDia() const;
        int getMes() const;
        int getAno() const;

        // @Set Methods
        void setDia(int d);
        void setMes(int m);
        void setAno(int a);

        // @Operators
        const bool operator < (Date d) {
            if (this->ano < d.ano)return true;
            if (this->ano == d.ano){
                if (this->mes < d.mes)return true;
                if (this->mes == d.mes){
                    if (dia < d.dia)return true;
                }
            }
            return false;
        }

        const bool operator == (Date d){
            if (dia == d.dia && mes == d.mes && ano == d.ano)return true;
            else return false;
        }
};

