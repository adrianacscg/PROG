#pragma once
#include "dependencies.h"

using namespace std;

bool compara_datas(Date data1, Date data2);
string lTrim(string &s);
string rTrim(string s);
string trim(string s);
template<typename Out> void split(const string& s, char delim, Out result);
vector<string> split(const string& s, char delim);
string toUpper(string s);
string toLower(string s);
string capitalize(string s);
template<typename vType> bool vectorIsEmpty(vector<vType>v);
template<typename type> void getvar(type &var, istream &s);
bool fileIsEmpty(ifstream& file);