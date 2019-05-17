#include "dependencies.h"

using namespace std;

/*
 * @Constructor
 */
    Client::Client(){
        nif = 0, n_pessoas_agregado = 0;
    }

    Client::Client(string name, int vat, int famNumber, Address address, vector<TravelPack> packsBought){
        nome = name;
        nif = vat;
        n_pessoas_agregado = famNumber;
        morada = address;
        pacotes_comprados = packsBought;
    }

/*
 * @Get Methods
 */
    string Client::getNome() const {
        return nome;
    }

    int Client::getNif() const {
        return nif;
    }

    int Client::getAgregadoFam() const {
        return n_pessoas_agregado;
    }

    Address Client::getMorada() const {
        return morada;
    }

    vector<TravelPack> Client::getPacotesComprados() const {
        return pacotes_comprados;
    }

/*
 * @Set Methods
 */
    void Client::setNome(string name){
        nome = name;
    }

    void Client::setNif(int vat){
        nif = vat;
    }

    void Client::setAgregadoFam(int famNumber){
        n_pessoas_agregado = famNumber;
    }

    void Client::setMorada(Address address){
        morada = address;
    }

    void Client::setPacotesComprados(vector<TravelPack> packsBought){
        pacotes_comprados = packsBought;
    }