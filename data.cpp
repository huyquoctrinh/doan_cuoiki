#include<iostream>
#include "stack_str.h"
// #include "vector_string.h"
#include "data_preprocessing.h"
#include<fstream>
#include <string>
#include <io.h>
#include<locale>
#include <fcntl.h>
#include<cstring>
#include "vector_string.h"
// #include "stack.h"
using namespace std;
wstring read_file(string filename){
    _setmode(_fileno(stdin), 0x40000);
    _setmode(_fileno(stdout), 0x40000);
    wifstream input;
    input.open(filename,ios::in);
    wstring in = {0};
    if (input.is_open()){
        getline(input,in);
        // wcout<<in;
    }
    else cout<<"no content";
    input.close();
    return in;
}
string readfile(string filename){
    ifstream input;
    string in;
    input.open(filename);
    if (input.is_open()){
        getline(input, in);
    }
    else cout<<"no content";
    input.close();
    return in;
}
void write_file(string filename,wstring data){
    _setmode(_fileno(stdout), 0x40000);
    wofstream output;
    output.open(filename,ios::out);
    if (output.is_open()){
        output<<data;
    }
    else cout<<"nothing to write";
    output.close();
}
void writefile(string filename,string data){
    ofstream output;
    output.open(filename);
    if (output.is_open()){
        output<<data;
    }
    else{
        return;
    }
    output.close();
}
int check_stopword(wstring a){
    int count = 0;
    _setmode(_fileno(stdin), 0x40000);
    wifstream input;
    wstring in;
    input.open("D:/doan_cuoiki/stopword.txt",ios::in);
    if (input.is_open()){
        while (getline(input,in)){
            // wcout<<in<<"\n";
            if (a.find(in)!= wstring::npos){
                count+=1;
            }
        }
    }
    cout<< count;
    return count;
}
// int remove_stopword(string a){
//     ifstream input;
//     int count =0;
//     input.open("D:/doan_cuoiki/stopword.txt");
//     string in;
//     if (input.is_open()){
//         getline(input,in);
//     }
//     if (a.find(in)==string::npos){

//     }
// }
void split(string in){
    string tmp = " ";
        for (int i =0; i<in.size();i++){
        if (in[i]==' '){
            string ind = "\n";
            for (int j = i-1;j>=0;j--){
                if (in[j]==' ')  break;
                
                tmp= (in[j])+tmp;        
            }
            tmp = ind+tmp;
        }
    }
    for (int i=0;i<tmp.size();i++){
        cout<<tmp[i];
    }
    writefile("out.txt",tmp);
}
string readutf8(string filename){
    ifstream inp(filename, ios::binary); 
    ofstream out("a.out"); 
    string s = " ";
    uint16_t buffer; 
    while (inp.read((char*)(&buffer), sizeof(uint16_t))) { 
        if (buffer == 0xfeff || buffer == 0x20) { 
            out << endl; 
            s += (char)buffer;
            continue; 
        }
        if (buffer <= 0x007f) {
            out << (char)(buffer);
            s+= (char)(buffer);
        }
        else if (buffer <= 0x07ff)
            out << (char)(0xc0 | ((buffer >> 6) & 0x1f)) << (char)(0x80 | (buffer & 0x3f)); 
        else 
            out << (char)(0xe0 | ((buffer >> 12) & 0x0f)) << (char)(0x80 | ((buffer >> 6) & 0x3f)) << (char)(0x80 | (buffer & 0x3f)); 
    }
    return s;
}
// Stack push2arr(string filename){
//     Stack s;
//     init(s);
//     ifstream inp(filename, ios::binary); 
//     ofstream out("a.out"); 
//     uint16_t buffer; 
//     while (inp.read((char*)(&buffer), sizeof(uint16_t))) { 
//         if (buffer == 0xfeff || buffer == 0x20) { 
//             out << endl; 
//             node p = initNode(char(buffer));
//             Push(s,p);
//             continue; 
//         }
//         if (buffer <= 0x007f) {
//             out << (char)(buffer);
//             // s+= (char)(buffer);
//         }
//         else if (buffer <= 0x07ff)
//             out << (char)(0xc0 | ((buffer >> 6) & 0x1f)) << (char)(0x80 | (buffer & 0x3f)); 
//         else 
//             out << (char)(0xe0 | ((buffer >> 12) & 0x0f)) << (char)(0x80 | ((buffer >> 6) & 0x3f)) << (char)(0x80 | (buffer & 0x3f)); 
//     }
//     return s;
// } 
void word2vec(){
     double * a= new double[1024];
    ifstream inp("tv.txt"); 
    ofstream out("test.out"); 
    Stack s;
    init(s);
    string str; 
    while (inp >> str) { 
        node p = initNode(str);
        Push(s,p);
        // out << str << endl; 
    }
    for (node i = s.top;i!=NULL;i=i->next){
        out<<i->data<<endl;
    }
    int count =0;
    Stack dict ;
    init(dict);
    for (node p = s.top;p!= NULL;p = p->next){
        // count+=1;
        int i =0;
        node k = p->next;
        int check =0;
        while (k!=NULL){
            if (p->data==k->data){
                check = 1;
                // cout<<count<<" \n";
                Pop(s,k->data);
                count --;
                break;
            }
            else{
                check = 0;
            }
            k = k->next;
        }
        // int u = count-1;
        a[count]= check;
        count++;
    }
    for (int i =0;i<count;i++){
        cout<<a[i]<<" ";
    }
}
void swap(string& a, string& b){
    string tmp =  a;
     a =  b;
     b = tmp;
}
void quickSort(string *a, int l, int r)
{
    srand(time(NULL));  //khoi tao tham so ham rand()
    string key = a[l + rand() % (r-l+1)];  //lay khoa la gia tri ngau nhien tu a[l] -> a[r]
    //int key = a[(l+r)/2];
    int i = l, j = r;

    while(i <= j)
    {
        while(a[i] < key) i++;       // tim phan tu ben trai ma >=key
        while(a[j] > key) j--;       // tim phan tu ben trai ma <=key
        if(i <= j)
        {
            if (i < j)
                swap(a[i], a[j]);  // doi cho 2 phan tu kieu int a[i], a[j].
            i++;
            j--;
        }
    }
    //bay gio ta co 1 mang : a[l]....a[j]..a[i]...a[r]
    if (l < j) quickSort(a, l, j);   // lam lai voi mang a[l]....a[j]
    if (i < r) quickSort(a, i, r); // lam lai voi mang a[i]....a[r]
}
int check_exist(dict* a,dict s, int n){
    int check = 0;
    for (int i = 0;i<n;i++){
        if (a[i].word == s.word){
            check = i;
            return check;
        }
        // else{
        //     continue;
        // }
    }
    return -1;
}
dict* wordindex(dict*u,int cn){
    dict* uw = new dict[cn];
    for (int i =0;i<cn;i++){
        if (check_exist(uw,u[i],cn)!=-1){
            // cout<<"in this case \n";
            int index = check_exist(uw,u[i],cn);
            uw[i].index=uw[index].index;
            uw[i].word=uw[index].word;
            // cout<<"["<<uw[i].word<<" "<<uw[i].index<<" ]\n";
            // cout<<"end \n";
        }
        else if (check_exist(uw,u[i],cn)==-1) {
        int dem=0;
        for (int j = i;j<cn;j++){
            if (u[i].word==u[j].word){
                dem+=1;
            }
        }
        // uw[i].index= (double)dem/cn;
        uw[i].index=dem;
        uw[i].word= u[i].word;
        // cout<<"["<<uw[i].word<<" "<<uw[i].index<<" ]\n";
        }
    }
    int lk = cn;
    // cout<<" \n ..... \n";
    // for (int i =0;i<cn;i++){
    //     cout<<"["<<uw[i].word<<" "<<uw[i].index<<" ]\n";
    // }
    return uw;
}
void remove_stopword(string stopword, string& mainStr){
   size_t found = mainStr.find(stopword);
    if (found != std::string::npos){
        mainStr.erase(found,stopword.size()), mainStr.insert(found, " ");
    }
}
bool check_exist(Stack s,string a){
    if (s.top==NULL){
        return 0;
    }
    for (node u = s.top;u!=NULL;u=u->next){
        if (u->data==a){
            return 1;
        }
    }
    return 0;
}
bool check_stopword(string s){
    ifstream in("stopword_no.txt");
    string stopword;
    while(getline(in,stopword)){
        if (s == stopword){
            return 1;
        }
    }
    return 0;
}
dict* gen_dict(string filename){
    ifstream inp(filename);
    ifstream in("stopword_no.txt");
    // ofstream out("out.txt");
    string stopword;
    Stack s;
    init(s);
    string str; 
    while (inp >> str) {
        int check = 1;
        while(in>>stopword){
            if (stopword== str){
                check=0;
            }
            else{
                check=1;
            }
        }
        if (check ==1){
            node p = initNode(str);
            Push(s,p); 
        }
    }
    int cn = countNode(s);
    dict* u = new dict[cn];
    node k = s.top;
    for (int i = 0;i <cn;i++){
        u[i].word= k->data;
        k = k->next;
    }
    dict* uw = wordindex(u,cn);
    tf(uw,cn);
    return uw;
}
int get_num(string filename){
    ifstream inp(filename);
    // ofstream out("out.txt");
    Stack s;
    init(s);
    string str; 
    while (inp >> str) { 
        node p = initNode(str);
        Push(s,p);
        // out << str << endl; 
    }
    int cn = countNode(s);
    dict* u = new dict[cn];
    node k = s.top;
    for (int i = 0;i <cn;i++){
        u[i].word= k->data;
        k = k->next;
    }
    dict* uw = wordindex(u,cn);
    tf(uw,cn);
    // cout<<" \n ..... \n";
    // for (int i =0;i<cn;i++){
    //     cout<<"["<<uw[i].word<<" "<<uw[i].index<<" ]\n";
    //     out<<uw[i].word<<" "<<uw[i].index<<"\n";
    // }
    return cn;
}