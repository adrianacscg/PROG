#include "dependencies.h"

using namespace std;

Agency::Agency(){
	nif = 0;
}

Agency::Agency(string name, int vat, Address address, string link, vector<TravelPack> packs, vector<Client> clients){
	nome = name;
	nif = vat;
	morada = address;
	url = link;
	pacotes = packs;
	clientes = clients;
}

//GET

string Agency::getNome() const {
	return nome;
}

int Agency::getNIF() const {
	return nif;
}

Address Agency::getMorada() const {
	return morada;
}

string Agency::getURL() const {
	return url;
}

vector<TravelPack> Agency::getPacotes() const {
	return pacotes;
}

vector<Client> Agency::getClientes() const {
	return clientes;
}

//SET

void Agency::setNome(string name){
	nome = name;
}

void Agency::setNIF(int vat){
	nif = vat;
}

void Agency::setMorada(Address address){
	morada = address;
}

void Agency::setURL(string link){
	url = link;
}

void Agency::setPacotes(vector<TravelPack> packs){
	pacotes = packs;
}

void Agency::setClientes(vector<Client> clients){
	clientes = clients;
}
