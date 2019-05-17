#include "dependencies.h"

using namespace std;


/*
 * @Constructor
 */
    Address::Address() {
        n_porta = 0;
    }

    Address::Address(string street, int doorNumber, string floor, string postalCode, string location) {
        rua = street;
        n_porta = doorNumber;
        andar = floor;
        codigo_postal = postalCode;
        localidade = location;
    }


/*
 * @Get Methods
 */
    string Address::getRua() const {
        return rua;
    }

    int Address::getNumPorta() const {
        return n_porta;
    }

    string Address::getAndar() const {
        return andar;
    }

    string Address::getCodigoPostal() const {
        return codigo_postal;
    }

    string Address::getLocalidade() const {
        return localidade;
    }


/*
 * @Get Methods
 */
    void Address::setRua(string street){
        rua = street;
    }

    void Address::setAndar(string floor){
        andar = floor;
    }

    void Address::setCodigoPostal(string postalCode){
        codigo_postal = postalCode;
    }

    void Address::setLocalidade(string location){
        localidade = location;
    }

    void Address::setNumPorta(int doorNumber){
        n_porta = doorNumber;
    }
