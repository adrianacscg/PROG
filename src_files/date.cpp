#include "dependencies.h"

using namespace std;


/*
 * @Constructor
 */
    Date::Date(){
        dia = 0, mes = 0, ano = 0;
    }

    Date::Date(int d, int m, int a){
        dia = d;
        mes = m;
        ano = a;
    }


/*
 * @Get Methods
 */
    int Date::getDia() const{
        return dia;
    }

    int Date::getMes() const{
        return mes;
    }

    int Date::getAno() const{
        return ano;
    }


/*
 * @Set Methods
 */
    void Date::setDia(int d){
        if (d < 1 && d > 31) cout << "ERRO: input inválido para <dia>";
        else dia = d;
    }

    void Date::setMes(int m){
        if (m < 1 && m > 12) cout << "ERRO: input inválido para <mes>";
        else mes = m;
    }

    void Date::setAno(int a){
        if (a < 2019) cout << "ERRO: input inválido para <ano>";
        else ano = a;
    }

