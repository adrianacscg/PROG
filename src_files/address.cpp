#include "dependencies.h"

using namespace std;

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

//GET

const string Address::getRua() {
	return rua;
}

const int Address::getNumPorta() {
	return n_porta;
}

const string Address::getAndar() {
	return andar;
}

const string Address::getCodigoPostal() {
	return codigo_postal;
}

const string Address::getLocalidade() {
	return localidade;
}

//SET

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




