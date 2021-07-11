#include<iostream>
#include<string>
using namespace std;
struct dict{
    string word;
    double index;
    bool check = 0;
};
wstring read_file(string filename);
string readfile(string filename);
void write_file(string filename,wstring data);
void writefile(string filename,string data);
int check_stopword(wstring a);
int check_exist(dict* a,dict s, int n);
dict* wordindex(dict*u,int cn);
dict* gen_dict(string filename);
int get_num(string filename);
bool check_stopword(string s);
void remove_stopword(string stopword, string& mainStr);
#pragma once