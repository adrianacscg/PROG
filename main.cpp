#include <algorithm> // utilizar a função sort()
#include <iostream>	// operações cin e cout
#include <fstream> // operações de escrita e leitura de ficheiros
#include <string> // utilizar o tipo string
#include <vector> // utilizar a estrutura de dados vector
#include <sstream> // utilizar stringstreams

using namespace std;


// Definição das structs
struct Date {
	int dia;
	int mes;
	int ano;
};

struct TravelPack {
	int id;
	string locais;
	Date data_inicio;
	Date data_fim;
	float preco;
	int lugares_max;
	int lugares_vendidos;
};

struct Address {
	string rua;
	int n_porta;
	string andar;
	string codigo_postal;
	string localidade;
};

struct Client {
	string nome;
	int nif;
	int n_pessoas_agregado;
	Address morada;
	vector<TravelPack> pacotes_comprados;
};

struct Agency {
	string nome;
	int nif;
	Address morada;
	string url;
	vector<TravelPack> pacotes;
	vector<Client> clientes;
};


//Variávies globais
string nome_ficheiro_clientes, nome_ficheiro_pacotes;
int ultimo_pacote;
Agency agencia; // Criação do objeto principal dp programa ("agencia")


// Declaração das funções necessárias devido à ordem existente
void menu_principal(int n_opcoes);
void menu_pacotes(int n_opcoes);
void menu_clientes(int n_opcoes);


// Função usada para efetuar a escolha de uma opção para todos os menus existentes, com tratamento de entradas erradas
int escolher_opcao(int n_op) {
	string opcao;
	bool e_int = false;

	cin >> opcao;
	cin.clear();
	cin.ignore(1000, '\n');

	while (cin.fail() || opcao.size() != 1 || opcao == "0" || e_int == false) {
		for (int i = 1; i <= n_op; i++) {
			char a = opcao[0];
			char b = to_string(i)[0];

			if (opcao.size() == 1 && a == b) {
				e_int = true;
				break;
			}
		}

		// C++ não permite fazer break de um nested loop
		// (solução: usar a flag e_int para fazer break nos dois loops)
		if (e_int == true)
			break;

		cout << "Por favor, introduza uma opção válida... ";
        cin >> opcao;
		cin.clear();
		cin.ignore(1000, '\n');

	}

	return stoi(opcao);
}


// Recebe a uma string com a morada como está nos ficheiros e retorna-a separada nos vários elementos
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


// Recebe uma string com a data como está nos ficheiros e retorna-a separada nos 3 elementos (ano, mês, dia)
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


// Carregar a informação presente no documento txt dos pacotes
void loadPacotes() {
	stringstream ss;
	ss << ".//ficheiros txt//" << nome_ficheiro_pacotes;
	string ficheiro_pacotes_string = ss.str();
	string linha;
	int itens_count = 0;
	vector<TravelPack> packs;

	ifstream ficheiro_pacotes(ficheiro_pacotes_string);

	// Variável ultimo_pacote toma o valor da primeira linha do ficheiro de pacotes
	//getline(ficheiro_pacotes, linha);
	cout << "O ficheiro é: " << nome_ficheiro_pacotes << endl;
	ultimo_pacote = stoi(linha);

	TravelPack pacote;
	Date data_begin;
	Date data_end;
	vector<int> data_valores;

	while (getline(ficheiro_pacotes, linha)) {

		switch (itens_count) {
			case 0:
				pacote.id = stoi(linha);
				break;
			case 1:
				pacote.locais = linha;
				break;
			case 2: {
				data_valores = data_parser(linha);
				data_begin.ano = data_valores[0];
				data_begin.mes = data_valores[1];
				data_begin.dia = data_valores[2];
				pacote.data_inicio = data_begin;
				break;}
			case 3: {
				data_valores = data_parser(linha);
				data_end.ano = data_valores[0];
				data_end.mes = data_valores[1];
				data_end.dia = data_valores[2];
				pacote.data_fim = data_end;
				break;}
			case 4:
				pacote.preco = stof(linha);
				break;
			case 5:
				pacote.lugares_max = stoi(linha);
				break;
			case 6: {
				pacote.lugares_vendidos = stoi(linha);
				packs.push_back(pacote);
				break;}
			case 7:
				itens_count = -1; // -1 para recomeçar em 0 depois da incrementação
				break;
		}

		itens_count++;

	}

	agencia.pacotes = packs;

	ficheiro_pacotes.close();
}


// Função que retorna um vetor ordenado com todos os ids dos pacotes existentes no parâmetro
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


// Carregar a informação presente no documento txt dos clientes
void loadClientes() {
	stringstream ss;
	ss << "./ficheiros txt/" << nome_ficheiro_clientes;
	string ficheiro_clientes_string = ss.str();
	string linha;
	int itens_count = 0;
	vector<Client> clients;

	ifstream ficheiro_clientes(ficheiro_clientes_string);

	Client cliente;
	Address morada_cliente;
	vector<string> morada_cliente_elementos;
	vector<TravelPack> packs_bought;
	vector<int> idPacotes_cliente;

	while (getline(ficheiro_clientes, linha)) {
		switch (itens_count) {
			case 0:
				cliente.nome = linha;
				break;
			case 1:
				cliente.nif = stoi(linha);
				break;
			case 2:
				cliente.n_pessoas_agregado = stoi(linha);
				break;
			case 3:
				morada_cliente_elementos = morada_parser(linha);
				morada_cliente.rua = morada_cliente_elementos[0];
				morada_cliente.n_porta = stoi(morada_cliente_elementos[1]);
				morada_cliente.andar = morada_cliente_elementos[2];
				morada_cliente.codigo_postal = morada_cliente_elementos[3];
				morada_cliente.localidade = morada_cliente_elementos[4];
				cliente.morada = morada_cliente;
				break;
			case 4:
				idPacotes_cliente = idPacotes_parser(linha);
				for (size_t i = 0; i < agencia.pacotes.size(); i++) {
					for (size_t j = 0; j < idPacotes_cliente.size(); j++)
						if (abs(agencia.pacotes[i].id) == idPacotes_cliente[j]) {
							packs_bought.push_back(agencia.pacotes[i]);
							break;
						}
				}
				cliente.pacotes_comprados = packs_bought;
				clients.push_back(cliente);
				packs_bought.clear();
				break;
			case 5:
				itens_count = -1;
				break;
		}

		itens_count++;
	}

	agencia.clientes = clients;

	ficheiro_clientes.close();
}


// Carregar a informação presente no documento agency.txt
void loadAgencia() {
	int itens_count = 0;
	string linha;

	ifstream ficheiro_agencia("./ficheiros txt/agency.txt");

	Address morada_agencia;
	vector<string> morada_agencia_elementos;
	
	if (ficheiro_agencia.is_open())
		cout << "asd" << endl;
	else
		cout << "Deu asneira" << endl;

	while (getline(ficheiro_agencia, linha)) {
		cout << "A linha e: " << linha << endl;
		switch (itens_count) {
			case 0:
				agencia.nome = linha;
				break;
			case 1:
				agencia.nif = stoi(linha);
				break;
			case 2:
				agencia.url = linha;
				break;
			case 3: {
				morada_agencia_elementos = morada_parser(linha);
				morada_agencia.rua = morada_agencia_elementos[0];
				morada_agencia.n_porta = stoi(morada_agencia_elementos[1]);
				morada_agencia.andar = morada_agencia_elementos[2];
				morada_agencia.codigo_postal = morada_agencia_elementos[3];
				morada_agencia.localidade = morada_agencia_elementos[4];
				agencia.morada = morada_agencia;
				break;}
			case 4:
				nome_ficheiro_clientes = linha;
				break;
			case 5:
				nome_ficheiro_pacotes = linha;
				cout << nome_ficheiro_pacotes << " : " << endl;
				break;
		}

		itens_count++;
	}

	ficheiro_agencia.close();
}


// Recebe um objeto morada e devolve uma stringstream com a morada visualmente compreensível
string morada_processada(Address morada) {
	stringstream morada_processed;

	morada_processed << morada.rua << ", nº" << morada.n_porta << ", ";

	if (morada.andar != "-") {
		morada_processed << morada.andar << ", " << morada.codigo_postal << " " << morada.localidade;
	} else
		morada_processed << morada.codigo_postal << " " << morada.localidade;

	return morada_processed.str();
}


// Operações de acesso à informação presente em agency.txt
void informacoes_agencia() {
	cout << "Informações gerais sobre a agência:" << endl;
	cout << endl;
	cout << "Nome: " << agencia.nome << endl;
	cout << "NIF: " << agencia.nif << endl;
	cout << "Site: " << agencia.url << endl;
	cout << "Morada: " << morada_processada(agencia.morada) << endl;
	cout << endl;
	cout << "1. Retroceder" << endl;
	cout << "2. Sair" << endl;
	cout << endl;
	cout << "Que opção pretende escolher? ";

	int n_opcoes = 2;
	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			menu_principal(5);
			return;
		case 2:
			cout << endl << "O programa vai agora terminar!" << endl;
			return;
	}
}


// Função recebe uma Address e devolve uma string no formato correto para guardar no ficheiro
string morada_guardar(Address morada) {
	stringstream morada_ss;

	morada_ss << morada.rua << " / " << morada.n_porta << " / " << morada.andar << " / "
			  << morada.codigo_postal << " / " << morada.localidade;

	return morada_ss.str();
}


// Função que cria um novo cliente com dados introduzidos pelo utilizador
void criar_cliente() {
	string nome, nif, n_pessoas_agregado, rua, n_porta, andar, codigo_postal, localidade;

	cout << endl;
	cout << "Qual é o nome do cliente? ";
	getline(cin, nome);
	cout << "Qual é o NIF do cliente? ";
	getline(cin, nif);
	cout << "Quantas pessoas possui no agregado familiar? ";
	getline(cin, n_pessoas_agregado);
	cout << "Em que rua mora? ";
	getline(cin, rua);
	cout << "Qual é o número da porta? ";
	getline(cin, n_porta);
	cout << "Qual é o andar em que mora? (se não existir andar, digite \"-\") ";
	getline(cin, andar);
	cout << "Qual é o código postal da morada do cliente? ";
	getline(cin, codigo_postal);
	cout << "Qual é a localidade da morada do cliente? ";
	getline(cin, localidade);
	cout << string( 35, '\n' );
	cout << "Cliente criado com sucesso!" << endl;
	cout << endl;

	// Criação de um cliente
	Client novo_cliente;
	vector<TravelPack> novo_vetor_pacotes;

	Address nova_morada;
	nova_morada.rua = rua;
	nova_morada.n_porta = stoi(n_porta);
	nova_morada.andar = andar;
	nova_morada.codigo_postal = codigo_postal;
	nova_morada.localidade = localidade;

	novo_cliente.nome = nome;
	novo_cliente.nif = stoi(nif);
	novo_cliente.n_pessoas_agregado = stoi(n_pessoas_agregado);
	novo_cliente.morada = nova_morada;
	novo_cliente.pacotes_comprados = novo_vetor_pacotes; // vetor vazio inicialmente

	// Adiciona o novo cliente ao vetor de clientes da agencia
	agencia.clientes.push_back(novo_cliente);

	// Abrir ficheiro de clientes para escrita
	stringstream ss;
	ss << "./ficheiros txt/" << nome_ficheiro_clientes;
	string ficheiro_clientes_string = ss.str();
	ofstream ficheiro_clientes(ficheiro_clientes_string, ios::app);

	// Escrita no ficheiro do novo pacote
	ficheiro_clientes << endl << "::::::::::" << endl
					  << novo_cliente.nome << endl
					  << novo_cliente.nif << endl
					  << novo_cliente.n_pessoas_agregado << endl
					  << morada_guardar(novo_cliente.morada) << endl
					  << "NENHUM PACOTE COMPRADO"; // 0 representa a inexistência de pacotes comprados

	ficheiro_clientes.close();
}


// Função que recebe um vetor de pacotes e retorna uma string com os ids para guardar no ficheiro
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


// Função que altera o ficheiro de clientes para o atualizar (porque houve alteração ou remoção de um pacote)
void novo_ficheiroClientes() {
	stringstream ss;
	ss << "./ficheiros txt/" << nome_ficheiro_clientes;
	string ficheiro_clientes_string = ss.str();
	ofstream novo_ficheiro("./ficheiros txt/nome_temp.txt");

	// Guardar informação sobre o primeiro cliente
	novo_ficheiro << agencia.clientes[0].nome << endl;
	novo_ficheiro << agencia.clientes[0].nif << endl;
	novo_ficheiro << agencia.clientes[0].n_pessoas_agregado << endl;
	novo_ficheiro << morada_guardar(agencia.clientes[0].morada) << endl;
	novo_ficheiro << idPacotes_guardar(agencia.clientes[0].pacotes_comprados);

	// Guardar a informação dos restantes clientes
	for (size_t i = 1; i < agencia.clientes.size(); i++) {
		novo_ficheiro << endl << "::::::::::";
		novo_ficheiro << endl << agencia.clientes[i].nome;
		novo_ficheiro << endl << agencia.clientes[i].nif;
		novo_ficheiro << endl << agencia.clientes[i].n_pessoas_agregado;
		novo_ficheiro << endl << morada_guardar(agencia.clientes[i].morada);
		novo_ficheiro << endl << idPacotes_guardar(agencia.clientes[i].pacotes_comprados);
	}

	novo_ficheiro.close();

	// Apaga o ficheiro original e renomeia o ficheiro novo com o nome do ficheiro apagado
	if (remove(ficheiro_clientes_string.c_str()) != 0)
		perror( "Error deleting file" );

	if (rename("./ficheiros txt/nome_temp.txt", ficheiro_clientes_string.c_str()) != 0)
		perror( "Error renaming file" );
}


// Função que altera os dados de um cliente já existente
void alterar_cliente() {
	string nome_antigo, nome_novo, nif, n_pessoas_agregado, rua, n_porta, andar, codigo_postal, localidade;

	cout << endl;
	cout << "Qual é o nome do cliente que quer alterar? ";
	getline(cin, nome_antigo);
	cout << "Para manter o valor atual do elemento, digite \"M\"" << endl << endl;
	cout << "Qual é o novo nome do cliente? ";
	getline(cin, nome_novo);
	cout << "Qual é o NIF do cliente? ";
	getline(cin, nif);
	cout << "Quantas pessoas possui no agregado familiar? ";
	getline(cin, n_pessoas_agregado);
	cout << "Em que rua mora? ";
	getline(cin, rua);
	cout << "Qual é o número da porta? ";
	getline(cin, n_porta);
	cout << "Qual é o andar em que mora? (se não existir andar, digite \"-\") ";
	getline(cin, andar);
	cout << "Qual é o código postal da morada do cliente? ";
	getline(cin, codigo_postal);
	cout << "Qual é a localidade da morada do cliente? ";
	getline(cin, localidade);
	cout << string( 35, '\n' );
	cout << "Cliente alterado com sucesso!" << endl;
	cout << endl;

	// Cliente cliente_alterar toma o valor do cliente a alterar (com o nome introduzido)
	Client cliente_alterar;
	int index_cliente_alterar; // variável que vai guardar o valor do index do cliente que vai ser alterado

	for (size_t i = 0; i < agencia.clientes.size(); i++)
		if (agencia.clientes[i].nome == nome_antigo) {
			cliente_alterar = agencia.clientes[i];
			index_cliente_alterar = i;
			break;
		}

	// Verificar se mantém os elementos antigos ou faz alteração se for o caso
	if (nome_novo != "M")
		cliente_alterar.nome = nome_novo;
	else
		cliente_alterar.nome = agencia.clientes[index_cliente_alterar].nome;

	if (nif != "M")
		cliente_alterar.nif = stoi(nif);
	else
		cliente_alterar.nif = agencia.clientes[index_cliente_alterar].nif;

	if (n_pessoas_agregado != "M")
		cliente_alterar.n_pessoas_agregado = stoi(n_pessoas_agregado);
	else
		cliente_alterar.n_pessoas_agregado = agencia.clientes[index_cliente_alterar].n_pessoas_agregado;


	Address morada_nova;

	if (rua != "M")
		morada_nova.rua = rua;
	else
		morada_nova.rua = agencia.clientes[index_cliente_alterar].morada.rua;

	if (n_porta != "M")
		morada_nova.n_porta = stoi(n_porta);
	else
		morada_nova.n_porta = agencia.clientes[index_cliente_alterar].morada.n_porta;

	if (andar != "M")
		morada_nova.andar = andar;
	else
		morada_nova.andar = agencia.clientes[index_cliente_alterar].morada.andar;

	if (codigo_postal != "M")
		morada_nova.codigo_postal = codigo_postal;
	else
		morada_nova.codigo_postal = agencia.clientes[index_cliente_alterar].morada.codigo_postal;

	if (localidade != "M")
		morada_nova.localidade = localidade;
	else
		morada_nova.localidade = agencia.clientes[index_cliente_alterar].morada.localidade;

	cliente_alterar.morada = morada_nova;

	// Alterar o cliente antigo para o cliente alterado
	agencia.clientes[index_cliente_alterar] = cliente_alterar;

	// Depois da alteração, cria um novo ficheiro com a alteração e apaga o antigo
	novo_ficheiroClientes();
}


// Função responsável por remover um pacote
void remover_cliente() {
	string nome;

	cout << endl;
	cout << "Qual é o nome do cliente que quer remover? ";
	getline(cin, nome);
	cout << string( 35, '\n' );
	cout << "Cliente removido com sucesso!" << endl;
	cout << endl;

	// Percorre o vetor de pacotes e quando encontra aquele com o id introduzido, elimina-o
	for (size_t i = 0; i < agencia.clientes.size(); i++)
		if (agencia.clientes[i].nome == nome)
			agencia.clientes.erase(agencia.clientes.begin()+i);

	novo_ficheiroClientes();
}


// Função que imprime a informação relativa a todos os clientes
void informacoes_clientes() {
	float total_gasto;

	cout << "Informações sobre todos os clientes da agência:" << endl;
	cout << endl;

	for (size_t i = 0; i < agencia.clientes.size(); i++) {
		total_gasto = 0;

		// Loop para calcular o dinheiro gasto em pacotes por um cliente
		for (size_t j = 0; j < agencia.clientes[i].pacotes_comprados.size(); j++) {
			total_gasto += agencia.clientes[i].pacotes_comprados[j].preco;
		}

		cout << "-------------- CLIENTE Nº" << i+1 << " --------------" << endl;
		cout << "Nome: " << agencia.clientes[i].nome << endl;
		cout << "NIF: " << agencia.clientes[i].nif << endl;
		cout << "Número de pessoas no agregado familiar: " << agencia.clientes[i].n_pessoas_agregado << endl;
		cout << "Morada: " << morada_processada(agencia.clientes[i].morada) << endl;
		cout << "Quantia total gasta em pacotes: " << total_gasto << endl;
		cout << endl;
	}

	cout << "1. Retroceder" << endl;
	cout << "2. Sair" << endl;
	cout << endl;
	cout << "Que opção pretende escolher? ";

	int n_opcoes = 2;
	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			menu_clientes(6);
			return;
		case 2:
			cout << endl << "O programa vai agora terminar!" << endl;
			return;
	}

}


// Função que imprime a informação relativa a todos os pacotes de um destino específico
void informacoes_cliente_especifico() {
	string nome;
	bool peloMenosUm_cliente = false; // flag para imprimir caso não exista nenhum cliente com o nome introduzido
	float total_gasto;

	cout << endl;
	cout << "Qual o nome do cliente cuja informação pretende pesquisar? ";
	getline(cin, nome);
	cout << string( 35, '\n' );
	cout << "Informações sobre o cliente " << nome << ":"<< endl;
	cout << endl;

	for (size_t i = 0; i < agencia.clientes.size(); i++) {
		if (agencia.clientes[i].nome == nome) {
			total_gasto = 0;

			// Loop para calcular o dinheiro gasto em pacotes por um cliente
			for (size_t j = 0; j < agencia.clientes[i].pacotes_comprados.size(); j++) {
				total_gasto += agencia.clientes[i].pacotes_comprados[j].preco;
			}

			cout << "-------------- CLIENTE Nº" << i+1 << " --------------" << endl;
			cout << "Nome: " << agencia.clientes[i].nome << endl;
			cout << "NIF: " << agencia.clientes[i].nif << endl;
			cout << "Número de pessoas no agregado familiar: " << agencia.clientes[i].n_pessoas_agregado << endl;
			cout << "Morada: " << morada_processada(agencia.clientes[i].morada) << endl;
			cout << "Quantia total gasta em pacotes: " << total_gasto << endl;
			cout << endl;

			peloMenosUm_cliente = true;
		}
	}

	if (peloMenosUm_cliente == false)
		cout << "Não existe nenhum cliente com esse nome..." << endl << endl;

	cout << "1. Retroceder" << endl;
	cout << "2. Sair" << endl;
	cout << endl;
	cout << "Que opção pretende escolher? ";

	int n_opcoes = 2;
	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			menu_clientes(6);
			return;
		case 2:
			cout << endl << "O programa vai agora terminar!" << endl;
			return;
	}
}


// Apresenta o menu para as operações possíveis para os clientes
void menu_clientes(int n_opcoes) {

	cout << "----------------------------------------------------------" << endl
		 << "----------------------------------------------------------" << endl
		 << "--                                                      --" << endl
		 << "--                 CLIENTES DA AGÊNCIA                  --" << endl
		 << "--                                                      --" << endl
		 << "-- 1. Ver informação de todos os clientes               --" << endl
		 << "-- 2. Ver informação de um cliente específico           --" << endl
		 << "-- 3. Criar um novo cliente                             --" << endl
		 << "-- 4. Alterar dados de um cliente                       --" << endl
		 << "-- 5. Remover um cliente                                --" << endl
		 << "-- 6. Retroceder                                        --" << endl
		 << "--                                                      --" << endl
		 << "----------------------------------------------------------" << endl
		 << "----------------------------------------------------------" << endl
		 << endl
		 << "Que opção pretende escolher? ";

	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			informacoes_clientes();
			return;
		case 2:
			informacoes_cliente_especifico();
			return;
		case 3:
			criar_cliente();
			menu_clientes(6);
			return;
		case 4:
			alterar_cliente();
			menu_clientes(6);
			return;
		case 5:
			remover_cliente();
			menu_clientes(6);
			return;
		case 6:
			cout << string( 35, '\n' );
			menu_principal(5);
			return;
	}
}


// Função recebe uma Data e devolve uma string no formato YYYY/MM/DD
string data_guardar(Date data) {
	stringstream data_ss;

	data_ss << data.ano << "/";

	if (data.mes > 9)
		data_ss << data.mes << "/";
	else
		data_ss << "0" << data.mes << "/";

	if (data.dia > 9)
		data_ss << data.dia;
	else
		data_ss << "0" << data.dia;

	return data_ss.str();
}


// Função que altera a primeira linha do ficheiro de pacotes para o novo id
void mudar_idInicial(int novo_id) {
	string linha;

	stringstream ss;
	ss << "./ficheiros txt/" << nome_ficheiro_pacotes;
	string ficheiro_pacotes_string = ss.str();
	ifstream ficheiro_inicial(ficheiro_pacotes_string);
	ofstream ficheiro_final("./ficheiros txt/nome_temp.txt");

	getline(ficheiro_inicial, linha);
	ficheiro_final << novo_id;

	while(getline(ficheiro_inicial, linha))
		ficheiro_final << endl << linha;

	ficheiro_inicial.close();
	ficheiro_final.close();

	// Apaga o ficheiro original e renomeia o ficheiro novo com o nome do ficheiro apagado
	if (remove(ficheiro_pacotes_string.c_str()) != 0)
	    perror( "Error deleting file" );

	if (rename("./ficheiros txt/nome_temp.txt", ficheiro_pacotes_string.c_str()) != 0)
		perror( "Error renaming file" );
}


// Função que cria um novo pacote com dados introduzidos pelo utilizador
void criar_pacote() {
	string destino, locais, data_inicio, data_fim, preco_pessoa, lugares_max;

	cout << endl;
	cout << "Qual é o destino deste pacote? ";
	getline(cin, destino);
	cout << "Quais são os locais desse destino? (separados por uma vírgula e espaço) ";
	getline(cin, locais);
	cout << "Qual a data de início deste pacote? (no formato YYYY/MM/DD) ";
	cin >> data_inicio;
	cout << "Qual a data de fim deste pacote? (no formato YYYY/MM/DD) ";
	cin >> data_fim;
	cout << "Qual é o preço por pessoa deste pacote? ";
	cin >> preco_pessoa;
	cout << "Qual o número máximo de pessoas que este pacote pode ter? ";
	cin >> lugares_max;
	cout << string( 35, '\n' );
	cout << "Pacote criado com sucesso!" << endl;
	cout << endl;

	// Junção do destino e dos locais numa só variável
	stringstream destino_locais;
	destino_locais << destino << " - " << locais;

	// Criação de um pacote
	TravelPack novo_pacote;

	Date data_begin;
	data_begin.ano = data_parser(data_inicio)[0];
	data_begin.mes = data_parser(data_inicio)[1];
	data_begin.dia = data_parser(data_inicio)[2];

	Date data_end;
	data_end.ano = data_parser(data_fim)[0];
	data_end.mes = data_parser(data_fim)[1];
	data_end.dia = data_parser(data_fim)[2];

	novo_pacote.id = ultimo_pacote + 1;
	novo_pacote.locais = destino_locais.str();
	novo_pacote.data_inicio = data_begin;
	novo_pacote.data_fim = data_end;
	novo_pacote.preco = stof(preco_pessoa);
	novo_pacote.lugares_max = stoi(lugares_max);
	novo_pacote.lugares_vendidos = 0;

	agencia.pacotes.push_back(novo_pacote);

	// Abrir ficheiro de pacotes para escrita
	stringstream ss;
	ss << "./ficheiros txt/" << nome_ficheiro_pacotes;
	string ficheiro_pacotes_string = ss.str();
	ofstream ficheiro_pacotes(ficheiro_pacotes_string, ios::app);

	// Escrita no ficheiro do novo pacote
	ficheiro_pacotes << endl << "::::::::::" << endl
					 << novo_pacote.id << endl
					 << novo_pacote.locais << endl
					 << data_guardar(novo_pacote.data_inicio) << endl
					 << data_guardar(novo_pacote.data_fim) << endl
					 << novo_pacote.preco << endl
					 << novo_pacote.lugares_max << endl
					 << novo_pacote.lugares_vendidos;

	ficheiro_pacotes.close();

	// Mudar a primeira linha para o novo id
	mudar_idInicial(novo_pacote.id);
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


// Função que altera o ficheiro de pacotes para o atualizar (porque houve alteração ou remoção de um pacote)
void novo_ficheiroPacotes() {
	stringstream ss;
	ss << "./ficheiros txt/" << nome_ficheiro_pacotes;
	string ficheiro_pacotes_string = ss.str();
	ofstream novo_ficheiro("./ficheiros txt/nome_temp.txt");

	// Guarda o id do último pacote criado (primeira linha)
	novo_ficheiro << ultimo_pacote << endl;

	// Guardar informação sobre o primeiro pacote
	novo_ficheiro << agencia.pacotes[0].id << endl;
	novo_ficheiro << agencia.pacotes[0].locais << endl;
	novo_ficheiro << data_guardar(agencia.pacotes[0].data_inicio) << endl;
	novo_ficheiro << data_guardar(agencia.pacotes[0].data_fim) << endl;
	novo_ficheiro << agencia.pacotes[0].preco << endl;
	novo_ficheiro << agencia.pacotes[0].lugares_max << endl;
	novo_ficheiro << agencia.pacotes[0].lugares_vendidos;

	// Guardar a informação dos restantes pacotes
	for (size_t i = 1; i < agencia.pacotes.size(); i++) {
		novo_ficheiro << endl << "::::::::::";
		novo_ficheiro << endl << agencia.pacotes[i].id;
		novo_ficheiro << endl << agencia.pacotes[i].locais;
		novo_ficheiro << endl << data_guardar(agencia.pacotes[i].data_inicio);
		novo_ficheiro << endl << data_guardar(agencia.pacotes[i].data_fim);
		novo_ficheiro << endl << agencia.pacotes[i].preco;
		novo_ficheiro << endl << agencia.pacotes[i].lugares_max;
		novo_ficheiro << endl << agencia.pacotes[i].lugares_vendidos;
	}

	novo_ficheiro.close();

	// Apaga o ficheiro original e renomeia o ficheiro novo com o nome do ficheiro apagado
	if (remove(ficheiro_pacotes_string.c_str()) != 0)
		perror( "Error deleting file" );

	if (rename("./ficheiros txt/nome_temp.txt", ficheiro_pacotes_string.c_str()) != 0)
		perror( "Error renaming file" );
}


// Função que altera os dados de um cliente já existente
void alterar_pacote() {
	string id, destino, locais, data_inicio, data_fim, preco_pessoa, lugares_max, lugares_vendidos;

	cout << endl;
	cout << "Qual é o id do pacote que quer alterar? ";
	getline(cin, id);
	cout << "Para manter o valor atual do elemento, digite \"M\"" << endl << endl;
	cout << "Qual é o destino deste pacote? ";
	getline(cin, destino);
	cout << "Quais são os locais desse destino? (separados por uma vírgula e espaço) ";
	getline(cin, locais);
	cout << "Qual a data de início deste pacote? (no formato YYYY/MM/DD) ";
	cin >> data_inicio;
	cout << "Qual a data de fim deste pacote? (no formato YYYY/MM/DD) ";
	cin >> data_fim;
	cout << "Qual é o preço por pessoa deste pacote? ";
	cin >> preco_pessoa;
	cout << "Qual o número máximo de pessoas que este pacote pode ter? ";
	cin >> lugares_max;
	cout << "Qual o número de lugares já vendidos para este pacote? ";
	cin >> lugares_vendidos;
	cout << string( 35, '\n' );
	cout << "Pacote alterado com sucesso!" << endl;
	cout << endl;

	// Pacote pacote_alterar toma o valor do pacote a alterar (com o id introduzido)
	TravelPack pacote_alterar;
	int index_pacote_alterar; // variável que vai guardar o valor do index do pacote que vai ser alterado

	for (size_t i = 0; i < agencia.pacotes.size(); i++)
		if (abs(agencia.pacotes[i].id) == stoi(id)) {
			pacote_alterar = agencia.pacotes[i];
			index_pacote_alterar = i;
			break;
		}

	// Verificar se mantém os elementos antigos ou faz alteração se for o caso
	stringstream destino_locais;

	if (destino == "M") {
		if (locais != "M") {
			destino_locais << separa_destino_locais(agencia.pacotes[index_pacote_alterar].locais)[0] << " - " << locais;
			pacote_alterar.locais = destino_locais.str();
		} else {
			destino_locais << separa_destino_locais(agencia.pacotes[index_pacote_alterar].locais)[0] << " - " << separa_destino_locais(agencia.pacotes[index_pacote_alterar].locais)[1];
			pacote_alterar.locais = destino_locais.str();
		}
	} else {
		if (locais != "M") {
			destino_locais << destino << " - " << locais;
			pacote_alterar.locais = destino_locais.str();
		} else {
			destino_locais << destino << " - " << separa_destino_locais(agencia.pacotes[index_pacote_alterar].locais)[1];
			pacote_alterar.locais = destino_locais.str();
		}
	}

	if (data_inicio != "M") {
		Date data_begin;
		data_begin.ano = data_parser(data_inicio)[0];
		data_begin.mes = data_parser(data_inicio)[1];
		data_begin.dia = data_parser(data_inicio)[2];
		pacote_alterar.data_inicio = data_begin;
	} else
		pacote_alterar.data_inicio = agencia.pacotes[index_pacote_alterar].data_inicio;

	if (data_fim != "M") {
		Date data_end;
		data_end.ano = data_parser(data_fim)[0];
		data_end.mes = data_parser(data_fim)[1];
		data_end.dia = data_parser(data_fim)[2];
		pacote_alterar.data_fim = data_end;
	} else
		pacote_alterar.data_fim = agencia.pacotes[index_pacote_alterar].data_fim;

	if (preco_pessoa != "M")
		pacote_alterar.preco = stof(preco_pessoa);
	else
		pacote_alterar.preco = agencia.pacotes[index_pacote_alterar].preco;

	if (lugares_max != "M")
		pacote_alterar.lugares_max = stoi(lugares_max);
	else
		pacote_alterar.lugares_max = agencia.pacotes[index_pacote_alterar].lugares_max;

	if (lugares_vendidos != "M")
		pacote_alterar.lugares_vendidos = stoi(lugares_vendidos);
	else
		pacote_alterar.lugares_vendidos = agencia.pacotes[index_pacote_alterar].lugares_vendidos;

	// Alterar o pacote antigo para o pacote alterado
	agencia.pacotes[index_pacote_alterar] = pacote_alterar;

	// Depois da alteração, cria um novo ficheiro com a alteração e apaga o antigo
	novo_ficheiroPacotes();
}


// Função responsável por remover um pacote
void remover_pacote() {
	string id;

	cout << endl;
	cout << "Qual é o id do pacote que quer remover? ";
	getline(cin, id);
	cout << string( 35, '\n' );
	cout << "Pacote removido com sucesso!" << endl;
	cout << endl;

	// Percorre o vetor de pacotes e quando encontra aquele com o id introduzido, elimina-o
	for (size_t i = 0; i < agencia.pacotes.size(); i++)
		if (abs(agencia.pacotes[i].id) == stoi(id))
			agencia.pacotes.erase(agencia.pacotes.begin()+i);

	novo_ficheiroPacotes();
}


// Função que imprime a informação relativa a todos os pacotes
void informacoes_pacotes(){
	cout << "Informações sobre todos os pacotes da agência:" << endl;
	cout << endl;

	for (size_t i = 0; i < agencia.pacotes.size(); i++) {
		cout << "-------------- PACOTE Nº" << i+1 << " --------------" << endl;
		if (agencia.pacotes[i].id < 0)
			cout << "Disponibilidade: Indisponível" << endl;
		else
			cout << "Disponibilidade: Disponível" << endl;
		cout << "Destino e locais: " << agencia.pacotes[i].locais << endl;
		cout << "Data inicial: " << data_guardar(agencia.pacotes[i].data_inicio) << endl;
		cout << "Data final: " << data_guardar(agencia.pacotes[i].data_fim) << endl;
		cout << "Preço por pessoa: " << agencia.pacotes[i].preco << endl;
		cout << "Lugares inicialmente disponíveis: " << agencia.pacotes[i].lugares_max << endl;
		cout << "Lugares já vendidos: " << agencia.pacotes[i].lugares_vendidos << endl;
		cout << endl;
	}

	cout << "1. Retroceder" << endl;
	cout << "2. Sair" << endl;
	cout << endl;
	cout << "Que opção pretende escolher? ";

	int n_opcoes = 2;
	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			menu_pacotes(8);
			return;
		case 2:
			cout << endl << "O programa vai agora terminar!" << endl;
			return;
	}
}


// Função que imprime a informação relativa a todos os pacotes de um destino específico
void informacoes_pacotes_destino() {
	string destino;
	bool peloMenosUm_pacote = false; // flag para imprimir caso não exista nenhum pacote entre as datas introduzidas

	cout << endl;
	cout << "Qual o destino cujos pacotes pretende pesquisar? ";
	cin >> destino;
	cout << string( 35, '\n' );
	cout << "Informações sobre todos os pacotes para o destino " << destino << ":"<< endl;
	cout << endl;

	for (size_t i = 0; i < agencia.pacotes.size(); i++) {
		if (separa_destino_locais(agencia.pacotes[i].locais)[0] == destino) {
			cout << "-------------- PACOTE Nº" << i+1 << " --------------" << endl;
			if (agencia.pacotes[i].id < 0)
				cout << "Disponibilidade: Indisponível" << endl;
			else
				cout << "Disponibilidade: Disponível" << endl;
			cout << "Destino e locais: " << agencia.pacotes[i].locais << endl;
			cout << "Data inicial: " << data_guardar(agencia.pacotes[i].data_inicio) << endl;
			cout << "Data final: " << data_guardar(agencia.pacotes[i].data_fim) << endl;
			cout << "Preço por pessoa: " << agencia.pacotes[i].preco << endl;
			cout << "Lugares inicialmente disponíveis: " << agencia.pacotes[i].lugares_max << endl;
			cout << "Lugares já vendidos: " << agencia.pacotes[i].lugares_vendidos << endl;
			cout << endl;

			peloMenosUm_pacote = true;
		}
	}

	if (peloMenosUm_pacote == false)
		cout << "Não existe nenhum pacote com esse destino..." << endl << endl;

	cout << "1. Retroceder" << endl;
	cout << "2. Sair" << endl;
	cout << endl;
	cout << "Que opção pretende escolher? ";

	int n_opcoes = 2;
	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			menu_pacotes(8);
			return;
		case 2:
			cout << endl << "O programa vai agora terminar!" << endl;
			return;
	}
}


// Função auxiliar para comparar duas datas (true se a 1ª for antes ou no mesmo dia da 2ª, false otherwise)
bool compara_datas(Date data1, Date data2) {

	if (data1.ano < data2.ano)
		return true;
	else if (data1.ano == data2.ano) {
		if (data1.mes < data2.mes)
			return true;
		else if (data1.mes == data2.mes) {
			if (data1.dia <= data2.dia)
				return true;
			else
				return false;
		} else
			return false;
	} else
		return false;

}


// Função que imprime a informação relativa a todos os pacotes entre duas datas pedidas
void informacoes_pacotes_entreDatas() {
	string entreDatas_data1, entreDatas_data2;
	bool peloMenosUm_pacote = false; // flag para imprimir caso não exista nenhum pacote entre as datas introduzidas

	cout << endl;
	cout << "Qual a primeira data para a filtragem? (no formato YYYY/MM/DD) ";
	cin >> entreDatas_data1;
	cout << "Qual a segunda data para a filtragem? (no formato YYYY/MM/DD) ";
	cin >> entreDatas_data2;
	cout << string( 35, '\n' );
	cout << "Informações sobre todos os pacotes entre " << entreDatas_data1 << " e " << entreDatas_data2 << ":"<< endl;
	cout << endl;

	// Criação de duas datas para comparar
	Date data1;
	data1.ano = data_parser(entreDatas_data1)[0];
	data1.mes = data_parser(entreDatas_data1)[1];
	data1.dia = data_parser(entreDatas_data1)[2];
	Date data2;
	data2.ano = data_parser(entreDatas_data2)[0];
	data2.mes = data_parser(entreDatas_data2)[1];
	data2.dia = data_parser(entreDatas_data2)[2];

	for (size_t i = 0; i < agencia.pacotes.size(); i++) {
		//compara_datas();
		if (compara_datas(data1, agencia.pacotes[i].data_inicio) == true && compara_datas(agencia.pacotes[i].data_fim, data2) == true) {
			cout << "-------------- PACOTE Nº" << i+1 << " --------------" << endl;
			if (agencia.pacotes[i].id < 0)
				cout << "Disponibilidade: Indisponível" << endl;
			else
				cout << "Disponibilidade: Disponível" << endl;
			cout << "Destino e locais: " << agencia.pacotes[i].locais << endl;
			cout << "Data inicial: " << data_guardar(agencia.pacotes[i].data_inicio) << endl;
			cout << "Data final: " << data_guardar(agencia.pacotes[i].data_fim) << endl;
			cout << "Preço por pessoa: " << agencia.pacotes[i].preco << endl;
			cout << "Lugares inicialmente disponíveis: " << agencia.pacotes[i].lugares_max << endl;
			cout << "Lugares já vendidos: " << agencia.pacotes[i].lugares_vendidos << endl;
			cout << endl;

			peloMenosUm_pacote = true;
		}
	}

	if (peloMenosUm_pacote == false)
		cout << "Não existe nenhum pacote entre as datas introduzidas..." << endl << endl;

	cout << "1. Retroceder" << endl;
	cout << "2. Sair" << endl;
	cout << endl;
	cout << "Que opção pretende escolher? ";

	int n_opcoes = 2;
	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			menu_pacotes(8);
			return;
		case 2:
			cout << endl << "O programa vai agora terminar!" << endl;
			return;
	}
}


// Função que imprime a informação relativa a todos os pacotes de um destino e entre duas datas
void informacoes_pacotes_destinoEentreDatas() {
	string destino, entreDatas_data1, entreDatas_data2;
	bool peloMenosUm_pacote = false; // flag para imprimir caso não exista nenhum pacote entre as datas introduzidas

	cout << endl;
	cout << "Qual o destino cujos pacotes pretende pesquisar? ";
	cin >> destino;
	cout << "Qual a primeira data para a filtragem? (no formato YYYY/MM/DD) ";
	cin >> entreDatas_data1;
	cout << "Qual a segunda data para a filtragem? (no formato YYYY/MM/DD) ";
	cin >> entreDatas_data2;
	cout << string( 35, '\n' );
	cout << "Informações sobre todos os pacotes para o destino " << destino << " e entre as datas " << entreDatas_data1 << " e " << entreDatas_data1 << ":" << endl;
	cout << endl;

	// Criação de duas datas para comparar
	Date data1;
	data1.ano = data_parser(entreDatas_data1)[0];
	data1.mes = data_parser(entreDatas_data1)[1];
	data1.dia = data_parser(entreDatas_data1)[2];
	Date data2;
	data2.ano = data_parser(entreDatas_data2)[0];
	data2.mes = data_parser(entreDatas_data2)[1];
	data2.dia = data_parser(entreDatas_data2)[2];

	for (size_t i = 0; i < agencia.pacotes.size(); i++) {
		if (separa_destino_locais(agencia.pacotes[i].locais)[0] == destino &&
			compara_datas(data1, agencia.pacotes[i].data_inicio) == true &&
			compara_datas(agencia.pacotes[i].data_fim, data2) == true) {
			cout << "-------------- PACOTE Nº" << i+1 << " --------------" << endl;
			if (agencia.pacotes[i].id < 0)
				cout << "Disponibilidade: Indisponível" << endl;
			else
				cout << "Disponibilidade: Disponível" << endl;
			cout << "Destino e locais: " << agencia.pacotes[i].locais << endl;
			cout << "Data inicial: " << data_guardar(agencia.pacotes[i].data_inicio) << endl;
			cout << "Data final: " << data_guardar(agencia.pacotes[i].data_fim) << endl;
			cout << "Preço por pessoa: " << agencia.pacotes[i].preco << endl;
			cout << "Lugares inicialmente disponíveis: " << agencia.pacotes[i].lugares_max << endl;
			cout << "Lugares já vendidos: " << agencia.pacotes[i].lugares_vendidos << endl;
			cout << endl;

			peloMenosUm_pacote = true;
		}
	}

	if (peloMenosUm_pacote == false)
		cout << "Não existe nenhum pacote com esse destino..." << endl << endl;

	cout << "1. Retroceder" << endl;
	cout << "2. Sair" << endl;
	cout << endl;
	cout << "Que opção pretende escolher? ";

	int n_opcoes = 2;
	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			menu_pacotes(8);
			return;
		case 2:
			cout << endl << "O programa vai agora terminar!" << endl;
			return;
	}
}


// Apresenta o menu para as operações possíveis para os clientes
void menu_pacotes(int n_opcoes) {

	cout << "--------------------------------------------------------------------" << endl
		 << "--------------------------------------------------------------------" << endl
		 << "--                                                                --" << endl
		 << "--                  PACOTES TURÍSTICOS DA AGÊNCIA                 --" << endl
		 << "--                                                                --" << endl
		 << "-- 1. Ver informação de todos os pacotes                          --" << endl
		 << "-- 2. Ver informação dos pacotes de um destino                    --" << endl
		 << "-- 3. Ver informação dos pacotes entre duas datas                 --" << endl
		 << "-- 4. Ver informação dos pacotes de um destino e entre duas datas --" << endl
		 << "-- 5. Criar um novo pacote                                        --" << endl
		 << "-- 6. Alterar dados de um pacote                                  --" << endl
		 << "-- 7. Remover um pacote                                           --" << endl
		 << "-- 8. Retroceder                                                  --" << endl
		 << "--                                                                --" << endl
		 << "--------------------------------------------------------------------" << endl
		 << "--------------------------------------------------------------------" << endl
		 << endl
		 << "Que opção pretende escolher? ";

	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			informacoes_pacotes();
			return;
		case 2:
			informacoes_pacotes_destino();
			return;
		case 3:
			informacoes_pacotes_entreDatas();
			return;
		case 4:
			informacoes_pacotes_destinoEentreDatas();
			return;
		case 5:
			criar_pacote();
			menu_pacotes(8);
			return;
		case 6:
			alterar_pacote();
			menu_pacotes(8);
			return;
		case 7:
			remover_pacote();
			menu_pacotes(8);
			return;
		case 8:
			cout << string( 35, '\n' );
			menu_principal(5);
			return;
	}
}


// Função que efetua a compra de um pacote por parte de um cliente
void comprar_pacote() {
	string nome_cliente, id_pacote;

	cout << endl;
	cout << "Como se chama o cliente que deseja efetuar uma compra? ";
	getline(cin, nome_cliente);
	cout << "Qual é o id do pacote que esse cliente deseja comprar? ";
	cin >> id_pacote;
	cout << string( 35, '\n' );
	cout << "Pacote comprado com sucesso!" << endl;
	cout << endl;

	// Pacote auxiliar para adicionar aos pacotes comprados pelo cliente
	TravelPack pacote_adicionar;

	// Pesquisar o pacote que está a ser comprado e incrementa o número de lugares vendidos
	for (size_t i = 0; agencia.pacotes.size(); i++) {
		if (abs(agencia.pacotes[i].id) == stoi(id_pacote)) {
			agencia.pacotes[i].lugares_vendidos++;

			if (agencia.pacotes[i].lugares_vendidos == agencia.pacotes[i].lugares_max)
				agencia.pacotes[i].id -= agencia.pacotes[i].id*2;

			pacote_adicionar = agencia.pacotes[i]; // pacote auxiliar toma o valor do pacote que foi comprado
			break;
		}
	}

	// Pesquisar o cliente que está a efetuar a compra e adicionar no vetor de pacotes comprados o pacote que está a comprar agora
	for (size_t j = 0; j < agencia.clientes.size(); j++) {
		if (agencia.clientes[j].nome == nome_cliente) {
			agencia.clientes[j].pacotes_comprados.push_back(pacote_adicionar);
			break;
		}
	}

	// Atualizar os ficheiros com os novos valores
	novo_ficheiroPacotes();
	novo_ficheiroClientes();
}


// Apresenta o menu principal
void menu_principal(int n_opcoes) {

	cout << "----------------------------------------------" << endl
		 << "----------------------------------------------" << endl
		 << "--                                          --" << endl
		 << "--           AGÊNCIA NICEHOLIDAYS           --" << endl
		 << "--                                          --" << endl
		 << "-- 1. Ver informações gerais da agência     --" << endl
		 << "-- 2. Fazer gestão dos clientes da agência  --" << endl
		 << "-- 3. Fazer gestão dos pacotes da agência   --" << endl
		 << "-- 4. Efetuar compra de um pacote turístico --" << endl
		 << "-- 5. Sair                                  --" << endl
		 << "--                                          --" << endl
		 << "----------------------------------------------" << endl
		 << "----------------------------------------------" << endl
		 << endl;
	cout << "Que opção pretende escolher? ";

	int opcao = escolher_opcao(n_opcoes);

	switch(opcao) {
		case 1:
			cout << string( 35, '\n' );
			informacoes_agencia();
			return;
		case 2:
			cout << string( 35, '\n' );
			menu_clientes(6);
			return;
		case 3:
			cout << string( 35, '\n' );
			menu_pacotes(8);
			return;
		case 4:
			comprar_pacote();
			menu_principal(5);
			return;
		case 5:
			cout << endl << "O programa vai agora terminar!" << endl;
			return;
	}

}


int main() {
	loadAgencia();
	loadPacotes();
	loadClientes();
	menu_principal(5);
	return 0;
}
