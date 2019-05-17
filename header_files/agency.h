#pragma once
#include "dependencies.h"

using namespace std;


class Agency {
private:
	string nome;
	int nif;
	Address morada;
	string url;
	vector<TravelPack> pacotes;
	vector<Client> clientes;

public:

	Agency();
	Agency(string name, int vat, Address address, string link, vector<TravelPack> packs, vector<Client> clients);

	//GET
	string getNome() const;
	int getNIF() const;
	Address getMorada() const;
	string getURL() const;
	vector<TravelPack> getPacotes() const;
	vector<Client> getClientes() const;

	//SET

	void setNome(string name);
	void setNIF(int vat);
	void setMorada(Address address);
	void setURL(string link);
	void setPacotes(vector<TravelPack> packs);
	void setClientes(vector<Client> clients);
};

