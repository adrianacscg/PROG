#include "dependencies.h"

using namespace std;

/*
 * Misc
 */
    // Função auxiliar para comparar duas datas
    // (true se a 1ª for antes ou no mesmo dia
    // da 2ª, false otherwise)
    bool compara_datas(Date data1, Date data2) {
        if (data1.getAno() < data2.getAno())
            return true;
        else if (data1.getAno() == data2.getAno()) {
            if (data1.getMes() < data2.getMes())
                return true;
            else if (data1.getMes() == data2.getMes()) {
                if (data1.getDia() <= data2.getDia())
                    return true;
                else
                    return false;
            } else
                return false;
        } else
            return false;
    }

    bool pacoteVendido(TravelPack pacote){
        return pacote.getLugaresVendidos() > 0;
    }


/*
 * Métodos Strings
 */
    // função que apara uma string da posição inicial
    string lTrim(string &s){
        s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch){
            return !isspace(ch);
        }));
        return s;
    }

    // função que apara uma string da posição final
    string rTrim(string s){
        s.erase(find_if(s.rbegin(), s.rend(), [](int ch){
            return !isspace(ch);
        }).base(), s.end());
        return s;
    }

    // função que apara uma string de ambos os lados
    string trim(string s){
        lTrim(s);
        rTrim(s);
        return s;
    }

    // função que divide uma string por um delimitador
    // devolvendo um vector com os elementos resultantes
    // desta operação
    template<typename Out>
    void split(const string& s, char delim, Out result){
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) *result++ = trim(item);
    }

    vector<string> split(const string& s, char delim){
        vector<string> v;
        split(s, delim, back_inserter(v));
        return v;
    }

    // função que transforma todos os caracteres de
    // uma string em uppercase
    string toUpper(string s){
        for (auto &ch : s) ch = toupper(ch);
        return s;
    }

    // função que transforma todos os caracteres de
    // uma string em lowercase
    string toLower(string s){
        for (auto &ch : s) ch = tolower(ch);
        return s;
    }

    // função que transforma a primeira letra de
    // cada palavra numa string em uppercase
    string capitalize(string s){
        string newStr;
        vector<string> words = split(s, ' ');
        for (auto word : words) {
            word[0] = toupper(word[0]);
            newStr += word + ' ';
        }
        return rTrim(newStr);
    }


/*
 * Métodos Vectors
 */
    // função que verifica se o vector está vazio
    template<typename vType>
    bool vectorIsEmpty(vector<vType>v) {
        return v.size() == 0;
    }

    bool stringInVector(string s, vector<string> v) {
        return find(v.begin(), v.end(), s) != v.end();
    }

/*
 * Métodos Stream
 */
    // função que extrai caracteres da stream
    // colocando-os numa variável do tipo especificado
    template<typename type>
    void getvar(type &var, istream &s) {
        while(true) {
            if (s >> var)
                break;
            else {
                s.clear();
                s.ignore(10000, '\n');
            }
        }
        s.ignore(10000, '\n');
    }


/*
 * Métodos Files
 */
    // função que verifica se um ficheiro está vazio
    bool fileIsEmpty(ifstream& file){
        return file.peek() == ifstream::traits_type::eof();
    }