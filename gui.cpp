#include "dependencies.h"

using namespace std;



/*
 * Opções
 */
    // Função usada para efetuar a escolha de
    // uma opção para todos os menus existentes,
    // com tratamento de entradas erradas
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
            if (e_int == true) break;

            cout << "Por favor, introduza uma opção válida... ";
            cin >> opcao;
            cin.clear();
            cin.ignore(1000, '\n');

        }

        return stoi(opcao);
    }


/*
 * Agência
 */
    // Operações de acesso à informação presente em agency.txt
    void informacoes_agencia() {
        cout << "Informações gerais sobre a agência:" << endl;
        cout << endl;
        cout << "Nome: " << agencia.getNome() << endl;
        cout << "NIF: " << agencia.getNIF() << endl;
        cout << "Site: " << agencia.getURL() << endl;
        cout << "Morada: " << morada_processada(agencia.getMorada()) << endl;
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


/*
 * Clientes
 */
    // Função que imprime a informação
    // relativa a todos os clientes
    void informacoes_clientes() {
        float total_gasto;

        cout << "Informações sobre todos os clientes da agência:" << endl;
        cout << endl;

        for (size_t i = 0; i < agencia.getClientes().size(); i++) {
            total_gasto = 0;

            // Loop para calcular o dinheiro
            // gasto em pacotes por um cliente
            for (size_t j = 0; j < agencia.getClientes()[i].getPacotesComprados().size(); j++) {
                total_gasto += agencia.getClientes()[i].getPacotesComprados()[j].getPreco();
            }

            cout << "-------------- CLIENTE Nº" << i+1 << " --------------" << endl;
            cout << "Nome: " << agencia.getClientes()[i].getNome() << endl;
            cout << "NIF: " << agencia.getClientes()[i].getNif() << endl;
            cout << "Número de pessoas no agregado familiar: " << agencia.getClientes()[i].getAgregadoFam()<< endl;
            cout << "Morada: " << morada_processada(agencia.getClientes()[i].getMorada()) << endl;
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


    // Função que imprime a informação relativa
    // a todos os pacotes de um destino específico
    void informacoes_cliente_especifico() {
        string nome;
        bool peloMenosUm_cliente = false;           // flag para imprimir caso não exista
        // nenhum cliente com o nome introduzido
        float total_gasto;

        cout << endl;
        cout << "Qual o nome do cliente cuja informação pretende pesquisar? ";
        getline(cin, nome);
        cout << string( 35, '\n' );
        cout << "Informações sobre o cliente " << nome << ":"<< endl;
        cout << endl;


        //Tornar todos os inputs de nomes no formato correto
        nome = capitalize(toLower(nome));

        for (size_t i = 0; i < agencia.getClientes().size(); i++) {
            if (agencia.getClientes()[i].getNome() == nome) {
                total_gasto = 0;

                // Loop para calcular o dinheiro gasto
                // em pacotes por um cliente
                for (size_t j = 0; j < agencia.getClientes()[i].getPacotesComprados().size(); j++) {
                    total_gasto += agencia.getClientes()[i].getPacotesComprados()[j].getPreco();
                }

                cout << "-------------- CLIENTE Nº" << i+1 << " --------------" << endl;
                cout << "Nome: " << agencia.getClientes()[i].getNome() << endl;
                cout << "NIF: " << agencia.getClientes()[i].getNif() << endl;
                cout << "Número de pessoas no agregado familiar: " << agencia.getClientes()[i].getAgregadoFam() << endl;
                cout << "Morada: " << morada_processada(agencia.getClientes()[i].getMorada()) << endl;
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


    // Apresenta o menu para as operações
    // possíveis para os clientes
    void menu_clientes(int n_opcoes) {

        cout << "----------------------------------------------------------" << endl
             << "----------------------------------------------------------" << endl
             << "--                                                      --" << endl
             << "--                 CLIENTES DA AGÊNCIA                  --" << endl
             << "--                                                      --" << endl
             << "-- 1. Ver informação de todos os clientes               --" << endl
             << "-- 2. Pesquisar cliente                                 --" << endl
             << "-- 3. Novo cliente                                      --" << endl
             << "-- 4. Alterar dados de um cliente                       --" << endl
             << "-- 5. Remover cliente                                   --" << endl
             << "-- 6. Retroceder                                        --" << endl
             << "--                                                      --" << endl
             << "----------------------------------------------------------" << endl
             << "----------------------------------------------------------" << endl
             << endl
             << "Que opção pretende escolher? ";

        int opcao = escolher_opcao(n_opcoes);

        switch(opcao) {
            case 1:
                cout << string(35, '\n');
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
                cout << string(35, '\n');
                menu_principal(5);
                return;
        }
    }


/*
 * Pacotes
 */
    // Função que imprime a informação
    // relativa a todos os pacotes
    void informacoes_pacotes(){
        cout << "Informações sobre todos os pacotes da agência:" << endl;
        cout << endl;

        for (size_t i = 0; i < agencia.getPacotes().size(); i++) {
            cout << "-------------- PACOTE Nº" << i+1 << " --------------" << endl;
            if (agencia.getPacotes()[i].getId() < 0)
                cout << "Disponibilidade: Indisponível" << endl;
            else
                cout << "Disponibilidade: Disponível" << endl;
            cout << "Destino e locais: " << agencia.getPacotes()[i].getLocais() << endl;
            cout << "Data inicial: " << data_guardar(agencia.getPacotes()[i].getDataInicio()) << endl;
            cout << "Data final: " << data_guardar(agencia.getPacotes()[i].getDataFim()) << endl;
            cout << "Preço por pessoa: " << agencia.getPacotes()[i].getPreco() << endl;
            cout << "Lugares inicialmente disponíveis: " << agencia.getPacotes()[i].getLugaresMax()<< endl;
            cout << "Lugares já vendidos: " << agencia.getPacotes()[i].getLugaresVendidos() << endl;
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


    // Função que imprime a informação relativa a
    // todos os pacotes de um destino específico
    void informacoes_pacotes_destino() {
        string destino;
        bool peloMenosUm_pacote = false; 				// flag para imprimir caso não exista
        // nenhum pacote entre as datas introduzidas

        cout << endl;
        cout << "Qual o destino cujos pacotes pretende pesquisar? ";
        cin >> destino;
        cout << string( 35, '\n' );
        cout << "Informações sobre todos os pacotes para o destino " << destino << ":"<< endl;
        cout << endl;

        for (size_t i = 0; i < agencia.getPacotes().size(); i++) {
            if (separa_destino_locais(agencia.getPacotes()[i].getLocais())[0] == destino) {
                cout << "-------------- PACOTE Nº" << i+1 << " --------------" << endl;
                if (agencia.getPacotes()[i].getId() < 0)
                    cout << "Disponibilidade: Indisponível" << endl;
                else
                    cout << "Disponibilidade: Disponível" << endl;
                cout << "Destino e locais: " << agencia.getPacotes()[i].getLocais() << endl;
                cout << "Data inicial: " << data_guardar(agencia.getPacotes()[i].getDataInicio()) << endl;
                cout << "Data final: " << data_guardar(agencia.getPacotes()[i].getDataFim()) << endl;
                cout << "Preço por pessoa: " << agencia.getPacotes()[i].getPreco() << endl;
                cout << "Lugares inicialmente disponíveis: " << agencia.getPacotes()[i].getLugaresMax() << endl;
                cout << "Lugares já vendidos: " << agencia.getPacotes()[i].getLugaresVendidos() << endl;
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
                cout << string(35, '\n');
                menu_pacotes(8);
                return;
            case 2:
                cout << endl << "O programa vai agora terminar!" << endl;
                return;
        }
    }


    // Função que imprime a informação relativa a
    // todos os pacotes entre duas datas pedidas
    void informacoes_pacotes_entreDatas() {
        string entreDatas_data1, entreDatas_data2;
        bool peloMenosUm_pacote = false; 				// flag para imprimir caso não exista nenhum
        // pacote entre as datas introduzidas

        cout << endl;
        cout << "Qual a primeira data para a filtragem? (no formato YYYY/MM/DD) ";
        cin >> entreDatas_data1;
        cout << "Qual a segunda data para a filtragem? (no formato YYYY/MM/DD) ";
        cin >> entreDatas_data2;
        cout << string(35, '\n');
        cout << "Informações sobre todos os pacotes entre " << entreDatas_data1 << " e " << entreDatas_data2 << ":"<< endl;
        cout << endl;

        // Criação de duas datas para comparar
        Date data1;
        data1.setAno(data_parser(entreDatas_data1)[0]);
        data1.setMes(data_parser(entreDatas_data1)[1]);
        data1.setDia(data_parser(entreDatas_data1)[2]);
        Date data2;
        data2.setAno(data_parser(entreDatas_data2)[0]);
        data2.setMes(data_parser(entreDatas_data2)[1]);
        data2.setDia(data_parser(entreDatas_data2)[2]);

        for (size_t i = 0; i < agencia.getPacotes().size(); i++) {
            // compara_datas();
            if (compara_datas(data1, agencia.getPacotes()[i].getDataInicio()) == true
                && compara_datas(agencia.getPacotes()[i].getDataFim(), data2) == true) {

                cout << "-------------- PACOTE Nº" << i+1 << " --------------" << endl;
                if (agencia.getPacotes()[i].getId() < 0)
                    cout << "Disponibilidade: Indisponível" << endl;
                else
                    cout << "Disponibilidade: Disponível" << endl;
                cout << "Destino e locais: " << agencia.getPacotes()[i].getLocais() << endl;
                cout << "Data inicial: " << data_guardar(agencia.getPacotes()[i].getDataInicio()) << endl;
                cout << "Data final: " << data_guardar(agencia.getPacotes()[i].getDataFim()) << endl;
                cout << "Preço por pessoa: " << agencia.getPacotes()[i].getPreco() << endl;
                cout << "Lugares inicialmente disponíveis: " << agencia.getPacotes()[i].getLugaresMax() << endl;
                cout << "Lugares já vendidos: " << agencia.getPacotes()[i].getLugaresVendidos() << endl;
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
                cout << string(35, '\n');
                menu_pacotes(8);
                return;
            case 2:
                cout << endl << "O programa vai agora terminar!" << endl;
                return;
        }
    }


    // Função que imprime a informação relativa a todos
    // os pacotes de um destino e entre duas datas
    void informacoes_pacotes_destinoEentreDatas() {
        string destino, entreDatas_data1, entreDatas_data2;
        bool peloMenosUm_pacote = false;                    // flag para imprimir caso não exista
        // nenhum pacote entre as datas introduzidas

        cout << endl;
        cout << "Qual o destino cujos pacotes pretende pesquisar? ";
        cin >> destino;
        cout << "Qual a primeira data para a filtragem? (no formato YYYY/MM/DD) ";
        cin >> entreDatas_data1;
        cout << "Qual a segunda data para a filtragem? (no formato YYYY/MM/DD) ";
        cin >> entreDatas_data2;
        cout << string(35, '\n');
        cout << "Informações sobre todos os pacotes para o destino " << destino << " e entre as datas " << entreDatas_data1 << " e " << entreDatas_data1 << ":" << endl;
        cout << endl;

        // Criação de duas datas para comparar
        Date data1;
        data1.setAno(data_parser(entreDatas_data1)[0]);
        data1.setMes(data_parser(entreDatas_data1)[1]);
        data1.setDia(data_parser(entreDatas_data1)[2]);
        Date data2;
        data2.setAno(data_parser(entreDatas_data2)[0]);
        data2.setMes(data_parser(entreDatas_data2)[1]);
        data2.setDia(data_parser(entreDatas_data2)[2]);

        for (size_t i = 0; i < agencia.getPacotes().size(); i++) {
            if (separa_destino_locais(agencia.getPacotes()[i].getLocais())[0] == destino &&
                compara_datas(data1, agencia.getPacotes()[i].getDataInicio()) == true &&
                compara_datas(agencia.getPacotes()[i].getDataFim(), data2) == true) {
                cout << "-------------- PACOTE Nº" << i+1 << " --------------" << endl;
                if (agencia.getPacotes()[i].getId() < 0)
                    cout << "Disponibilidade: Indisponível" << endl;
                else
                    cout << "Disponibilidade: Disponível" << endl;
                cout << "Destino e locais: " << agencia.getPacotes()[i].getLocais() << endl;
                cout << "Data inicial: " << data_guardar(agencia.getPacotes()[i].getDataInicio()) << endl;
                cout << "Data final: " << data_guardar(agencia.getPacotes()[i].getDataFim()) << endl;
                cout << "Preço por pessoa: " << agencia.getPacotes()[i].getPreco() << endl;
                cout << "Lugares inicialmente disponíveis: " << agencia.getPacotes()[i].getLugaresMax() << endl;
                cout << "Lugares já vendidos: " << agencia.getPacotes()[i].getLugaresVendidos() << endl;
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


    // Apresenta o menu para as operações
    // possíveis para os clientes
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


/*
 * Principal
 */
    // Apresenta o menu principal
    void menu_principal(int n_opcoes) {

        cout << "----------------------------------------------" << endl
             << "----------------------------------------------" << endl
             << "--                                          --" << endl
             << "--           AGÊNCIA NICEHOLIDAYS           --" << endl
             << "--                                          --" << endl
             << "-- 1. Agência                               --" << endl
             << "-- 2. Gerir Clientes                        --" << endl
             << "-- 3. Gerir Pacotes                         --" << endl
             << "-- 4. Comprar Pacotes                       --" << endl
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
