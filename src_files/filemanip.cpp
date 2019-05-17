#include "dependencies.h"

using namespace std;

// definição das variávies globais
string nome_ficheiro_clientes, nome_ficheiro_pacotes;
int ultimo_pacote;
Agency agencia;

// Carregar a informação presente no
// documento txt dos pacotes
void loadPacotes() {
    stringstream ss;
    ss << "./ficheiros_txt/" << nome_ficheiro_pacotes;
    string ficheiro_pacotes_string = ss.str();
    string linha;
    int itens_count = 0;
    vector<TravelPack> packs;

    ifstream ficheiro_pacotes(ficheiro_pacotes_string);

    // Variável ultimo_pacote toma o valor
    // da primeira linha do ficheiro de pacotes
    getline(ficheiro_pacotes, linha);
    ultimo_pacote = stoi(linha);

    TravelPack pacote;
    Date data_begin;
    Date data_end;
    vector<int> data_valores;

    while (getline(ficheiro_pacotes, linha)) {

        switch (itens_count) {
            case 0:
                pacote.setId(stoi(linha));
                break;
            case 1:
                pacote.setLocais(linha);
                break;
            case 2: {
                data_valores = data_parser(linha);
                data_begin.setAno(data_valores[0]);
                data_begin.setMes(data_valores[1]);
                data_begin.setDia(data_valores[2]);
                pacote.setDataInicio(data_begin);
                break;}
            case 3: {
                data_valores = data_parser(linha);
                data_end.setAno(data_valores[0]);
                data_end.setMes(data_valores[1]);
                data_end.setDia(data_valores[2]);
                pacote.setDataFim(data_end);
                break;}
            case 4:
                pacote.setPreco(stof(linha));
                break;
            case 5:
                pacote.setLugaresMax(stoi(linha));
                break;
            case 6: {
                pacote.setLugaresVendidos(stoi(linha));
                packs.push_back(pacote);
                break;}
            case 7:
                itens_count = -1;                       // -1 para recomeçar em 0 depois da incrementação
                break;
        }

        itens_count++;

    }

    agencia.setPacotes(packs);

    ficheiro_pacotes.close();
}


// Carregar a informação presente no
// documento txt dos clientes
void loadClientes() {
    stringstream ss;
    ss << "./ficheiros_txt/" << nome_ficheiro_clientes;
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
                cliente.setNome(linha);
                break;
            case 1:
                cliente.setNif(stoi(linha));
                break;
            case 2:
                cliente.setAgregadoFam(stoi(linha));
                break;
            case 3:
                morada_cliente_elementos = morada_parser(linha);
                morada_cliente.setRua(morada_cliente_elementos[0]);
                morada_cliente.setNumPorta(stoi(morada_cliente_elementos[1]));
                morada_cliente.setAndar(morada_cliente_elementos[2]);
                morada_cliente.setCodigoPostal(morada_cliente_elementos[3]);
                morada_cliente.setLocalidade(morada_cliente_elementos[4]);
                cliente.setMorada(morada_cliente);
                break;
            case 4:
                idPacotes_cliente = idPacotes_parser(linha);
                for (size_t i = 0; i < agencia.getPacotes().size(); i++) {
                    for (size_t j = 0; j < idPacotes_cliente.size(); j++)
                        if (abs(agencia.getPacotes()[i].getId()) == idPacotes_cliente[j]) {
                            packs_bought.push_back(agencia.getPacotes()[i]);
                            break;
                        }
                }
                cliente.setPacotesComprados(packs_bought);
                clients.push_back(cliente);
                packs_bought.clear();
                break;
            case 5:
                itens_count = -1;
                break;
        }

        itens_count++;
    }

    agencia.setClientes(clients);

    ficheiro_clientes.close();
}


// Carregar a informação presente
// no documento agency.txt
void loadAgencia() {
    int itens_count = 0;
    string linha;

    ifstream ficheiro_agencia("./ficheiros_txt/agency.txt");

    Address morada_agencia;
    vector<string> morada_agencia_elementos;

    while (getline(ficheiro_agencia, linha)) {

        switch (itens_count) {
            case 0:
                agencia.setNome(linha);
                break;
            case 1:
                agencia.setNIF(stoi(linha));
                break;
            case 2:
                agencia.setURL(linha);
                break;
            case 3: {
                morada_agencia_elementos = morada_parser(linha);
                morada_agencia.setRua(morada_agencia_elementos[0]);
                morada_agencia.setNumPorta(stoi(morada_agencia_elementos[1]));
                morada_agencia.setAndar(morada_agencia_elementos[2]);
                morada_agencia.setCodigoPostal(morada_agencia_elementos[3]);
                morada_agencia.setLocalidade(morada_agencia_elementos[4]);
                agencia.setMorada(morada_agencia);
                break;}
            case 4:
                nome_ficheiro_clientes = linha;
                break;
            case 5:
                nome_ficheiro_pacotes = linha;
                break;
        }

        itens_count++;
    }

    ficheiro_agencia.close();
}


// Recebe um objeto morada e devolve uma
// stringstream com a morada visualmente compreensível
string morada_processada(Address morada) {
    stringstream morada_processed;

    morada_processed << morada.getRua() << ", nº" << morada.getNumPorta() << ", ";

    if (morada.getAndar() != "-") {
        morada_processed << morada.getAndar() << ", " << morada.getCodigoPostal() << " " << morada.getLocalidade();
    } else
        morada_processed << morada.getCodigoPostal() << " " << morada.getLocalidade();

    return morada_processed.str();
}


// Função que cria um novo cliente
// com dados introduzidos pelo utilizador
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
    nova_morada.setRua(rua);
    nova_morada.setNumPorta(stoi(n_porta));
    nova_morada.setAndar(andar);
    nova_morada.setCodigoPostal(codigo_postal);
    nova_morada.setLocalidade(localidade);

    novo_cliente.setNome(nome);
    novo_cliente.setNif(stoi(nif));
    novo_cliente.setAgregadoFam(stoi(n_pessoas_agregado));
    novo_cliente.setMorada(nova_morada);
    novo_cliente.setPacotesComprados(novo_vetor_pacotes);                // vetor vazio inicialmente

    // Adiciona o novo cliente ao vetor de clientes da agencia
    agencia.getClientes().push_back(novo_cliente);

    // Abrir ficheiro de clientes para escrita
    stringstream ss;
    ss << "./ficheiros_txt/" << nome_ficheiro_clientes;
    string ficheiro_clientes_string = ss.str();
    ofstream ficheiro_clientes(ficheiro_clientes_string, ios::app);

    // Escrita no ficheiro do novo pacote
    ficheiro_clientes << endl << "::::::::::" << endl
                      << novo_cliente.getNome() << endl
                      << novo_cliente.getNif() << endl
                      << novo_cliente.getAgregadoFam() << endl
                      << morada_guardar(novo_cliente.getMorada()) << endl
                      << "NENHUM PACOTE COMPRADO";						        // 0 representa a inexistência
                                                                                // de pacotes comprados

    ficheiro_clientes.close();
}


// Função que altera o ficheiro de clientes
// para o atualizar (porque houve alteração
// ou remoção de um pacote)
void novo_ficheiroClientes() {
    stringstream ss;
    ss << "./ficheiros_txt/" << nome_ficheiro_clientes;
    string ficheiro_clientes_string = ss.str();
    ofstream novo_ficheiro("./ficheiros_txt/nome_temp.txt");

    // Guardar informação sobre o primeiro cliente
    novo_ficheiro << agencia.getClientes()[0].getNome() << endl;
    novo_ficheiro << agencia.getClientes()[0].getNif() << endl;
    novo_ficheiro << agencia.getClientes()[0].getAgregadoFam() << endl;
    novo_ficheiro << morada_guardar(agencia.getClientes()[0].getMorada()) << endl;
    novo_ficheiro << idPacotes_guardar(agencia.getClientes()[0].getPacotesComprados());

    // Guardar a informação dos restantes clientes
    for (size_t i = 1; i < agencia.getClientes().size(); i++) {
        novo_ficheiro << endl << "::::::::::";
        novo_ficheiro << endl << agencia.getClientes()[i].getNome();
        novo_ficheiro << endl << agencia.getClientes()[i].getNif();
        novo_ficheiro << endl << agencia.getClientes()[i].getAgregadoFam();
        novo_ficheiro << endl << morada_guardar(agencia.getClientes()[i].getMorada());
        novo_ficheiro << endl << idPacotes_guardar(agencia.getClientes()[i].getPacotesComprados());
    }

    novo_ficheiro.close();

    // Apaga o ficheiro original e renomeia o
    // ficheiro novo com o nome do ficheiro apagado
    if (remove(ficheiro_clientes_string.c_str()) != 0)
        perror( "Error deleting file" );

    if (rename("./ficheiros_txt/nome_temp.txt", ficheiro_clientes_string.c_str()) != 0)
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

    // Cliente cliente_alterar toma o valor
    // do cliente a alterar (com o nome introduzido)
    Client cliente_alterar;
    int index_cliente_alterar;              // variável que vai guardar o valor
    // do index do cliente que vai ser alterado

    nome_antigo = capitalize(toLower(nome_antigo));

    for (size_t i = 0; i < agencia.getClientes().size(); i++)
        if (agencia.getClientes()[i].getNome() == nome_antigo) {
            cliente_alterar = agencia.getClientes()[i];
            index_cliente_alterar = i;
            break;
        }

    // Verificar se mantém os elementos antigos
    // ou faz alteração se for o caso
    if (nome_novo != "M" && nome_novo != "m")
        cliente_alterar.setNome(nome_novo);
    else
        cliente_alterar.setNome(agencia.getClientes()[index_cliente_alterar].getNome());

    if (nif != "M" && nif != "m")
        cliente_alterar.setNif(stoi(nif));
    else
        cliente_alterar.setNif(agencia.getClientes()[index_cliente_alterar].getNif());

    if (n_pessoas_agregado != "M" && n_pessoas_agregado != "m")
        cliente_alterar.setAgregadoFam(stoi(n_pessoas_agregado));
    else
        cliente_alterar.setAgregadoFam(agencia.getClientes()[index_cliente_alterar].getAgregadoFam());


    Address morada_nova;

    if (rua != "M" && rua != "m")
        morada_nova.setRua(rua);
    else
        morada_nova.setRua(agencia.getClientes()[index_cliente_alterar].getMorada().getRua());

    if (n_porta != "M" && n_porta != "m")
        morada_nova.setNumPorta(stoi(n_porta));
    else
        morada_nova.setNumPorta(agencia.getClientes()[index_cliente_alterar].getMorada().getNumPorta());

    if (andar != "M" && andar != "m")
        morada_nova.setAndar(andar);
    else
        morada_nova.setAndar(agencia.getClientes()[index_cliente_alterar].getMorada().getAndar());

    if (codigo_postal != "M" && codigo_postal != "m")
        morada_nova.setCodigoPostal(codigo_postal);
    else
        morada_nova.setCodigoPostal(agencia.getClientes()[index_cliente_alterar].getMorada().getCodigoPostal());

    if (localidade != "M" && localidade != "m")
        morada_nova.setLocalidade(localidade);
    else
        morada_nova.setLocalidade(agencia.getClientes()[index_cliente_alterar].getMorada().getLocalidade());

    cliente_alterar.setMorada(morada_nova);

    // Alterar o cliente antigo para o cliente alterado
    agencia.getClientes()[index_cliente_alterar] = cliente_alterar;

    // Depois da alteração cria um
    // novo ficheiro com a alteração e apaga o antigo
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

    // Percorre o vetor de pacotes e quando
    // encontra aquele com o id introduzido elimina-o
    for (size_t i = 0; i < agencia.getClientes().size(); i++)
        if (agencia.getClientes()[i].getNome() == nome)
            agencia.getClientes().erase(agencia.getClientes().begin()+i);

    novo_ficheiroClientes();
}


// Função que altera a primeira linha
// do ficheiro de pacotes para o novo id
void mudar_idInicial(int novo_id) {
    string linha;

    stringstream ss;
    ss << "./ficheiros_txt/" << nome_ficheiro_pacotes;
    string ficheiro_pacotes_string = ss.str();
    ifstream ficheiro_inicial(ficheiro_pacotes_string);
    ofstream ficheiro_final("./ficheiros_txt/nome_temp.txt");

    getline(ficheiro_inicial, linha);
    ficheiro_final << novo_id;

    while(getline(ficheiro_inicial, linha))
        ficheiro_final << endl << linha;

    ficheiro_inicial.close();
    ficheiro_final.close();

    // Apaga o ficheiro original e renomeia o
    // ficheiro novo com o nome do ficheiro apagado
    if (remove(ficheiro_pacotes_string.c_str()) != 0)
        perror( "Error deleting file" );

    if (rename("./ficheiros_txt/nome_temp.txt", ficheiro_pacotes_string.c_str()) != 0)
        perror( "Error renaming file" );
}


// Função que cria um novo pacote com
// dados introduzidos pelo utilizador
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
    cout << string(35, '\n');
    cout << "Pacote criado com sucesso!" << endl;
    cout << endl;

    // Junção do destino e dos locais numa só variável
    stringstream destino_locais;
    destino_locais << destino << " - " << locais;

    // Criação de um pacote
    TravelPack novo_pacote;

    Date data_begin;
    data_begin.setAno(data_parser(data_inicio)[0]);
    data_begin.setMes(data_parser(data_inicio)[1]);
    data_begin.setDia(data_parser(data_inicio)[2]);

    Date data_end;
    data_end.setAno(data_parser(data_fim)[0]);
    data_end.setMes(data_parser(data_fim)[1]);
    data_end.setDia(data_parser(data_fim)[2]);

    novo_pacote.setId(ultimo_pacote + 1);
    novo_pacote.setLocais(destino_locais.str());
    novo_pacote.setDataInicio(data_begin);
    novo_pacote.setDataFim(data_end);
    novo_pacote.setPreco(stof(preco_pessoa));
    novo_pacote.setLugaresMax(stoi(lugares_max));
    novo_pacote.setLugaresVendidos(0);

    agencia.getPacotes().push_back(novo_pacote);

    // Abrir ficheiro de pacotes para escrita
    stringstream ss;
    ss << "./ficheiros_txt/" << nome_ficheiro_pacotes;
    string ficheiro_pacotes_string = ss.str();
    ofstream ficheiro_pacotes(ficheiro_pacotes_string, ios::app);

    // Escrita no ficheiro do novo pacote
    ficheiro_pacotes << endl << "::::::::::" << endl
                     << novo_pacote.getId() << endl
                     << novo_pacote.getLocais() << endl
                     << data_guardar(novo_pacote.getDataInicio()) << endl
                     << data_guardar(novo_pacote.getDataFim()) << endl
                     << novo_pacote.getPreco() << endl
                     << novo_pacote.getLugaresMax() << endl
                     << novo_pacote.getLugaresVendidos();

    ficheiro_pacotes.close();

    // Mudar a primeira linha para o novo id
    mudar_idInicial(novo_pacote.getId());
}


// Função que altera o ficheiro de pacotes para
// o atualizar (porque houve alteração ou remoção
// de um pacote)
void novo_ficheiroPacotes() {
    stringstream ss;
    ss << "./ficheiros_txt/" << nome_ficheiro_pacotes;
    string ficheiro_pacotes_string = ss.str();
    ofstream novo_ficheiro("./ficheiros_txt/nome_temp.txt");

    // Guarda o id do último pacote criado (primeira linha)
    novo_ficheiro << ultimo_pacote << endl;

    // Guardar informação sobre o primeiro pacote
    novo_ficheiro << agencia.getPacotes()[0].getId() << endl;
    novo_ficheiro << agencia.getPacotes()[0].getLocais() << endl;
    novo_ficheiro << data_guardar(agencia.getPacotes()[0].getDataInicio()) << endl;
    novo_ficheiro << data_guardar(agencia.getPacotes()[0].getDataFim()) << endl;
    novo_ficheiro << agencia.getPacotes()[0].getPreco() << endl;
    novo_ficheiro << agencia.getPacotes()[0].getLugaresMax() << endl;
    novo_ficheiro << agencia.getPacotes()[0].getLugaresVendidos();

    // Guardar a informação dos restantes pacotes
    for (size_t i = 1; i < agencia.getPacotes().size(); i++) {
        novo_ficheiro << endl << "::::::::::";
        novo_ficheiro << endl << agencia.getPacotes()[i].getId();
        novo_ficheiro << endl << agencia.getPacotes()[i].getLocais();
        novo_ficheiro << endl << data_guardar(agencia.getPacotes()[i].getDataInicio());
        novo_ficheiro << endl << data_guardar(agencia.getPacotes()[i].getDataFim());
        novo_ficheiro << endl << agencia.getPacotes()[i].getPreco();
        novo_ficheiro << endl << agencia.getPacotes()[i].getLugaresMax();
        novo_ficheiro << endl << agencia.getPacotes()[i].getLugaresVendidos();
    }

    novo_ficheiro.close();

    // Apaga o ficheiro original e renomeia o
    // ficheiro novo com o nome do ficheiro apagado
    if (remove(ficheiro_pacotes_string.c_str()) != 0)
        perror( "Error deleting file" );

    if (rename("./ficheiros_txt/nome_temp.txt", ficheiro_pacotes_string.c_str()) != 0)
        perror( "Error renaming file" );
}


// Função que altera os dados de
// um cliente já existente
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

    // Pacote pacote_alterar toma o valor do
    // pacote a alterar (com o id introduzido)
    TravelPack pacote_alterar;
    int index_pacote_alterar;                   // variável que vai guardar o valor
                                                // do index do pacote que vai ser alterado

    for (size_t i = 0; i < agencia.getPacotes().size(); i++)
        if (abs(agencia.getPacotes()[i].getId()) == stoi(id)) {
            pacote_alterar = agencia.getPacotes()[i];
            index_pacote_alterar = i;
            break;
        }

    // Verificar se mantém os elementos antigos
    // ou faz alteração se for o caso
    stringstream destino_locais;

    if (destino == "M") {
        if (locais != "M") {
            destino_locais << separa_destino_locais(agencia.getPacotes()[index_pacote_alterar].getLocais())[0] << " - " << locais;
            pacote_alterar.getLocais() = destino_locais.str();
        } else {
            destino_locais << separa_destino_locais(agencia.getPacotes()[index_pacote_alterar].getLocais())[0] << " - " << separa_destino_locais(agencia.getPacotes()[index_pacote_alterar].getLocais())[1];
            pacote_alterar.setLocais(destino_locais.str());
        }
    } else {
        if (locais != "M") {
            destino_locais << destino << " - " << locais;
            pacote_alterar.setLocais(destino_locais.str());
        } else {
            destino_locais << destino << " - " << separa_destino_locais(agencia.getPacotes()[index_pacote_alterar].getLocais())[1];
            pacote_alterar.setLocais(destino_locais.str());
        }
    }

    if (data_inicio != "M") {
        Date data_begin;
        data_begin.setAno(data_parser(data_inicio)[0]);
        data_begin.setMes(data_parser(data_inicio)[1]);
        data_begin.setDia(data_parser(data_inicio)[2]);
        pacote_alterar.setDataInicio(data_begin);
    } else
        pacote_alterar.setDataInicio(agencia.getPacotes()[index_pacote_alterar].getDataInicio());

    if (data_fim != "M") {
        Date data_end;
        data_end.setAno(data_parser(data_fim)[0]);
        data_end.setMes(data_parser(data_fim)[1]);
        data_end.setDia(data_parser(data_fim)[2]);
        pacote_alterar.setDataFim(data_end);
    } else
        pacote_alterar.setDataFim(agencia.getPacotes()[index_pacote_alterar].getDataFim());

    if (preco_pessoa != "M")
        pacote_alterar.setPreco(stof(preco_pessoa));
    else
        pacote_alterar.setPreco(agencia.getPacotes()[index_pacote_alterar].getPreco());

    if (lugares_max != "M")
        pacote_alterar.setLugaresMax(stoi(lugares_max));
    else
        pacote_alterar.setLugaresMax(agencia.getPacotes()[index_pacote_alterar].getLugaresMax());

    if (lugares_vendidos != "M")
        pacote_alterar.setLugaresVendidos(stoi(lugares_vendidos));
    else
        pacote_alterar.setLugaresVendidos(agencia.getPacotes()[index_pacote_alterar].getLugaresVendidos());

    // Alterar o pacote antigo para o pacote alterado
    agencia.getPacotes()[index_pacote_alterar] = pacote_alterar;

    // Depois da alteração, cria um novo ficheiro
    // com a alteração e apaga o antigo
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

    // Percorre o vetor de pacotes e quando encontra
    // aquele com o id introduzido elimina-o
    for (size_t i = 0; i < agencia.getPacotes().size(); i++)
        if (abs(agencia.getPacotes()[i].getId()) == stoi(id))
            agencia.getPacotes().erase(agencia.getPacotes().begin()+i);

    novo_ficheiroPacotes();
}


// Função que efetua a compra de um
// pacote por parte de um cliente
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

    // Pacote auxiliar para adicionar aos
    // pacotes comprados pelo cliente
    TravelPack pacote_adicionar;

    // Pesquisar o pacote que está a ser comprado
    // e incrementa o número de lugares vendidos
    for (size_t i = 0; agencia.getPacotes().size(); i++) {
        if (abs(agencia.getPacotes()[i].getId()) == stoi(id_pacote)) {
            int lugaresVendidos = agencia.getPacotes()[i].getLugaresVendidos();
            agencia.getPacotes()[i].setLugaresVendidos(lugaresVendidos++);

            if (agencia.getPacotes()[i].getLugaresVendidos() == agencia.getPacotes()[i].getLugaresMax())
                agencia.getPacotes()[i].setId(agencia.getPacotes()[i].getId() - agencia.getPacotes()[i].getId()*2);

            pacote_adicionar = agencia.getPacotes()[i];                  // pacote auxiliar toma o valor
                                                                    // do pacote que foi comprado
            break;
        }
    }

    // Pesquisar o cliente que está a efetuar a compra
    // e adicionar no vetor de pacotes comprados o
    // pacote que está a comprar agora
    for (size_t j = 0; j < agencia.getClientes().size(); j++) {
        if (agencia.getClientes()[j].getNome() == nome_cliente) {
            agencia.getClientes()[j].getPacotesComprados().push_back(pacote_adicionar);
            break;
        }
    }

    // Atualizar os ficheiros com os novos valores
    novo_ficheiroPacotes();
    novo_ficheiroClientes();
}



