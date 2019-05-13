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
                itens_count = -1;                       // -1 para recomeçar em 0 depois da incrementação
                break;
        }

        itens_count++;

    }

    agencia.pacotes = packs;

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

    morada_processed << morada.rua << ", nº" << morada.n_porta << ", ";

    if (morada.andar != "-") {
        morada_processed << morada.andar << ", " << morada.codigo_postal << " " << morada.localidade;
    } else
        morada_processed << morada.codigo_postal << " " << morada.localidade;

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
    nova_morada.rua = rua;
    nova_morada.n_porta = stoi(n_porta);
    nova_morada.andar = andar;
    nova_morada.codigo_postal = codigo_postal;
    nova_morada.localidade = localidade;

    novo_cliente.nome = nome;
    novo_cliente.nif = stoi(nif);
    novo_cliente.n_pessoas_agregado = stoi(n_pessoas_agregado);
    novo_cliente.morada = nova_morada;
    novo_cliente.pacotes_comprados = novo_vetor_pacotes;                // vetor vazio inicialmente

    // Adiciona o novo cliente ao vetor de clientes da agencia
    agencia.clientes.push_back(novo_cliente);

    // Abrir ficheiro de clientes para escrita
    stringstream ss;
    ss << "./ficheiros_txt/" << nome_ficheiro_clientes;
    string ficheiro_clientes_string = ss.str();
    ofstream ficheiro_clientes(ficheiro_clientes_string, ios::app);

    // Escrita no ficheiro do novo pacote
    ficheiro_clientes << endl << "::::::::::" << endl
                      << novo_cliente.nome << endl
                      << novo_cliente.nif << endl
                      << novo_cliente.n_pessoas_agregado << endl
                      << morada_guardar(novo_cliente.morada) << endl
                      << "NENHUM PACOTE COMPRADO";						// 0 representa a inexistência
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

    for (size_t i = 0; i < agencia.clientes.size(); i++)
        if (agencia.clientes[i].nome == nome_antigo) {
            cliente_alterar = agencia.clientes[i];
            index_cliente_alterar = i;
            break;
        }

    // Verificar se mantém os elementos antigos
    // ou faz alteração se for o caso
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
    for (size_t i = 0; i < agencia.clientes.size(); i++)
        if (agencia.clientes[i].nome == nome)
            agencia.clientes.erase(agencia.clientes.begin()+i);

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
    ss << "./ficheiros_txt/" << nome_ficheiro_pacotes;
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

    for (size_t i = 0; i < agencia.pacotes.size(); i++)
        if (abs(agencia.pacotes[i].id) == stoi(id)) {
            pacote_alterar = agencia.pacotes[i];
            index_pacote_alterar = i;
            break;
        }

    // Verificar se mantém os elementos antigos
    // ou faz alteração se for o caso
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
    for (size_t i = 0; i < agencia.pacotes.size(); i++)
        if (abs(agencia.pacotes[i].id) == stoi(id))
            agencia.pacotes.erase(agencia.pacotes.begin()+i);

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
    for (size_t i = 0; agencia.pacotes.size(); i++) {
        if (abs(agencia.pacotes[i].id) == stoi(id_pacote)) {
            agencia.pacotes[i].lugares_vendidos++;

            if (agencia.pacotes[i].lugares_vendidos == agencia.pacotes[i].lugares_max)
                agencia.pacotes[i].id -= agencia.pacotes[i].id*2;

            pacote_adicionar = agencia.pacotes[i];                  // pacote auxiliar toma o valor
            // do pacote que foi comprado
            break;
        }
    }

    // Pesquisar o cliente que está a efetuar a compra
    // e adicionar no vetor de pacotes comprados o
    // pacote que está a comprar agora
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



