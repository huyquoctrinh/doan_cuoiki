#include<iostream>
#include "data_preprocessing.h"
#include<string>
#include <io.h>
#include<locale>
#include <fcntl.h>
#include<fstream>
#include "stack_str.h"
#include <iomanip>
#include "vector_string.h"
#include<codecvt>
#include<stdio.h>
#include<iomanip>
// #include "stack.h"
using namespace std;
void function1();
bool function2();

struct metadata{
    string data;
    string filename;
    int index;
    metadata* next;
};
struct stack_met{
    metadata* top;
};
metadata* initMet(string value,string filename,int index){
    metadata* p = new metadata();
    if (p==NULL){
        return NULL; 
    }
    p->data = value;
    p->filename = filename;
    p->index = index;
    p->next=NULL;
    return p;
}
void init_met(stack_met &a){
    a.top= NULL;
}
bool checkEmpty1(stack_met a){
    if (a.top==NULL) return 1;
    else return 0;
}
void push(stack_met& a, metadata* p){
    if (checkEmpty1(a)){
        a.top = p;
    }
    else{
        p->next = a.top;
        a.top = p;
    }
}
bool pop(stack_met& a, string value){
    if (checkEmpty1(a)) return 0;
    metadata* p = a.top;
    a.top=a.top->next;
    value = p->data;
    return 1;
}
// void get_meta(string filename){
//     ifstream in(filename);
//     ofstream out("out.out");
//     ifstream stop("stopword_no.txt");
//     string stopword;
//     string str;
//     stack_met p;
//     init_met(p);
//     while(getline(in,str)){
//         string s;
//         ifstream inp(str);
//         while (getline(inp,s))
//         {
//             while (getline(stop,stopword))
//             {
//                  remove_stopword(stopword,str);
//             }
//             metadata* tmp = initMet(str,s);
//             push(p,tmp);
//     }
//     }
//     for (metadata* x = p.top;x!=NULL;x=x->next){
//             out<<x->filename<<" "<<x->data<<"\n";
//     }
// }
bool check(doc_arr s,string a){
    for (doc* p = s.top;p!=NULL;p=p->next){
        if (p->data.word==a){
            return 1;
        }
    }
    return 0;
}
bool gen_token(string s){
return 0;
}
string preprocess(string &s){
    // ifstream inp(filename);
    // string s,a,k;
    while (s.find(",") != std::string::npos){
        string x =",";
        s.erase(s.find(","),x.size());
    }
    while (s.find(".") != std::string::npos) {
        string a = ".";
        s.erase(s.find("."),a.size());
        // k+= s + " ";
    }
    while (s.find(":") != std::string::npos){
        string x =":";
        s.erase(s.find(":"),x.size());
    }
        while (s.find("...") != std::string::npos){
        string x ="...";
        s.erase(s.find("..."),x.size());
    }
    while (s.find("!") != std::string::npos){
        string x ="!";
        s.erase(s.find("!"),x.size());
    }
    while (s.find("-") != std::string::npos){
        string x ="-";
        s.erase(s.find("-"),x.size());
    }

    // cout<<s;
    return s;
}
void create_feature(dict* &uw,double threshold,int cn){
    for (int i=0;i<cn;i++){
        if (uw[i].index<threshold){
            uw[i].index=0;
            uw[i].word="";   
        }
    }
}
dict* tokenizer(string filename,string file_stopword,int&l){
    ifstream inp(filename);
    ifstream in(file_stopword);
    // ofstream out("out.txt");
    string stopword;
    Stack s;
    init(s);
    string str; 
    while (inp >> str) {
        preprocess(str);
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
    l = cn;
    dict* u = new dict[cn];
    node k = s.top;
    for (int i = 0;i <cn;i++){
        u[i].word= k->data;
        k = k->next;
    }
    dict* uw = wordindex(u,cn);
    tf(uw,cn);
    create_feature(uw,0.1,cn);
    return uw;
}

void del_stopword(string& s,string filename){
    ifstream in(filename);
    string a,k;
    while (in>>a){
        while (s.find(a) != std::string::npos){
            s.erase(s.find(a),a.size());
        }
    }
    // return s;
}
void gen_metadata(string dir,string output,string stopword){
    // string dir = "dir.csv";
    ofstream out(output);
    // string stopword="stopword_no.txt";
    ifstream in(dir);
    string s;
    int cn =0;
    int index =1;
    // dict* a = tokenizer("D:/doan_cuoiki/tv.txt",stopword,cn); 
   while (getline(in,s))
    {
        // cout<<index++;
        // cout<<s<<endl;
        dict* u = tokenizer(s,stopword,cn);
        out<<index<<" ";
        for (int i =0;i<cn;i++){
            if (u[i].word==""){
                out<<"";
            }
            else{
            out<<u[i].word<<" ";
            }
        }
        out<<endl;
        cn=0;
        index++;
    }
}

double check_num(string s,string b){
    int count =0;
    while (s.find(b) != std::string::npos){
        count+=1;
    }
    return (double)count/s.size();
}
double Freq(string &pat, string &txt)
{
    int M = pat.length();
    int N = txt.length();
    int res = 0;
    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
            if (txt[i+j] != pat[j])
                break;

        if (j == M) 
        {
           res++;
           j = 0;
        }
    }
    // cout<<res<<endl;
    // double kq = (double)res/txt.size();
    return res;
}

int fun1(const std::string& sub, const std::string& str)
{
	int num = 0;
	for (size_t i = 0; (i = str.find(sub, i)) != std::string::npos; num++, i++);
	return num;
}

struct last{
    int index;
    string content;
    string filename;
};
void swap(last &a, last&b){
    last tmp = a;
    a = b;
    b= tmp;
}
void quickSort(last* a, int l, int r)
{
    srand(time(NULL)); 
    last key = a[l + rand() % (r-l+1)];  
    int i = l, j = r;

    while(i <= j)
    {
        while(a[i].index < key.index) i++;       
        while(a[j].index > key.index) j--;       
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
void search1time(string a,int soluong){
    int index = 1;
    int i;
    string s;
    ifstream in("metadata.txt");
    ifstream fn("dir.csv");
     dict uw;
    cout<<"finding ..."<<endl;
    last*  kq= new last[100000];
    index = 1;
    string fname;
    while(in>>i,getline(in,s),getline(fn,fname)){
        ifstream tv(fname);
        // string uq;getline(tv,uq);
        // int tmp = Freq(a,s);
        int tmp = fun1(a,s);
        // cout<<tmp<<endl;
        kq[i].index=tmp;
        kq[i].content = s;
        kq[i].filename= fname;
        // if (tmp>max){
        //     max = tmp;
        //     mem = index;
        //     uw.word= s;
        //     uw.index= index;
        // }
        // cout<<max<<endl;
        index++;
    }
    quickSort(kq,1,index);
    ofstream outp("kqtim.txt");
    int kta=0;
    for (int i=index-1;i>index-1-soluong;i--){
        if (kq[i].index!=0){
            outp<<kq[i].filename<<" "<<kq[i].index<<endl;
            cout<<kq[i].filename<<" "<<kq[i].index<<endl;
            // outp<<kq[i].content<<endl;
            // cout<<kq[i].content<<endl;
        }
        else{
            outp<<"Khong co ket qua"<<endl;
            cout<<"Khong co ket qua"<<endl;
        }
    }
}
void function1(){
    string a;
    // cout<<"input string \n"<<endl;
    getline(cin,a);
    a=" "+ a+ " ";
    int soluong;
    cout<<"so luong ket qua muon tim \n"<<endl;
    cin>>soluong;
    search1time(a,soluong);
    cout<<"end";
}
std::wstring RemoveVietnameseTone(const std::wstring& text) {
  std::wstring result(text);

  return result;
}
void remove_anccent(wstring& a){
    wstring s1 = L"ÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚÝàáâãèéêìíòóôõùúýĂăĐđĨĩŨũƠơƯưẠạẢảẤấẦầẨẩẪẫẬậẮắẰằẲẳẴẵẶặẸẹẺẻẼẽẾếỀềỂểỄễỆệỈỉỊịỌọỎỏỐốỒồỔổỖỗỘộỚớỜờỞởỠỡỢợỤụỦủỨứỪừỬửỮữỰựỲỳỴỵỶỷỸỹ";
    wstring s0 = L"AAAAEEEIIOOOOUUYaaaaeeeiioooouuyAaDdIiUuOoUuAaAaAaAaAaAaAaAaAaAaAaAaEeEeEeEeEeEeEeEeIiIiOoOoOoOoOoOoOoOoOoOoOoOoUuUuUuUuUuUuUuYyYyYyYy";
    string res=" ";
    for (int i=0;i<a.size();i++){
        int check = 1;
        for (int j = 0;j<s1.size();j++){
            if (a[i]==s1[j]){
                a[i]=s0[j];
                break;
            }
        }
    }
}
char rma(char& a){
    string s1 = "ÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚÝàáâãèéêìíòóôõùúýĂăĐđĨĩŨũƠơƯưẠạẢảẤấẦầẨẩẪẫẬậẮắẰằẲẳẴẵẶặẸẹẺẻẼẽẾếỀềỂểỄễỆệỈỉỊịỌọỎỏỐốỒồỔổỖỗỘộỚớỜờỞởỠỡỢợỤụỦủỨứỪừỬửỮữỰựỲỳỴỵỶỷỸỹ";
    string s0 = "AAAAEEEIIOOOOUUYaaaaeeeiioooouuyAaDdIiUuOoUuAaAaAaAaAaAaAaAaAaAaAaAaEeEeEeEeEeEeEeEeIiIiOoOoOoOoOoOoOoOoOoOoOoOoUuUuUuUuUuUuUuYyYyYyYy";
    for (int i =0;i<s1.size();i++){
        if (a==s1[i]){
            a =s0[i];
        }
    }
    return a;
}
wstring readfile(const char* filename) {
    FILE *inp = fopen(filename, "rb"); 
    fseek(inp, 0, SEEK_END);
    int file_size = ftell(inp);
    fseek(inp, 0, SEEK_SET);
    wchar_t *buffer = new wchar_t[file_size / 2 + 1]; 
    fread(buffer, 2, file_size / 2, inp); 
    buffer[file_size / 2] = L'\0'; 
    wstring wss(buffer); 
    delete [] buffer; 
    return wss; 
}
void rm_dau(const char* filein){
    _setmode(_fileno(stdout), 0x40000);
    wofstream testFile;
    FILE* f = fopen("tmp.out","wb+");
    wstring wstr = readfile(filein);
    remove_anccent(wstr); 
    wcout<<wstr;
    wchar_t* ptr = _wcsdup(wstr.c_str());
    fwrite(ptr, sizeof(wchar_t),wcslen(ptr) , f);
}
void to_utf8_file(string filein){
    _setmode(_fileno(stdout), 0x40000);
    ifstream inp(filein, ios::binary); 
    ofstream out("tmp1.out"); 

    uint16_t buffer; 
    while (inp.read((char*)(&buffer), sizeof(uint16_t))) { 
        if (buffer == 0xfeff || buffer == 0x20) { 
            out << " "; 
            continue; 
        }
        if (buffer <= 0x007f) 
            out << (char)(buffer);
        else if (buffer <= 0x07ff)
            out << (char)(0xc0 | ((buffer >> 6) & 0x1f)) << (char)(0x80 | (buffer & 0x3f)); 
        else 
            out << (char)(0xe0 | ((buffer >> 12) & 0x0f)) << (char)(0x80 | ((buffer >> 6) & 0x3f)) << (char)(0x80 | (buffer & 0x3f)); 
    }
}
void gen_new_metadata(string filename,int log){
    string s;
    ofstream out("metadata.txt",std::fstream::app);
    rm_dau(filename.c_str());
    int cn =0;
    int index=1;
    to_utf8_file("tmp.out");
    string stopword = "stopword_no.txt";
    cout<<s<<endl;
    dict* u = tokenizer("tmp1.out",stopword,cn);
    out<<"\n"<<log<<" ";
        // out<<index<<" ";
    for (int i =0;i<cn;i++){
        if (u[i].word==""){
            out<<"";
        }
        else{
            out<<u[i].word<<" ";
        }
    }
}
void add_file(string filename){
    ifstream log("log.txt",std::fstream::in);
    int exist_file; log>>exist_file;
    gen_new_metadata("D:/doan_cuoiki/new test/Am nhac/AN_TN_T_ (762).txt",exist_file+1);
    ofstream outlog("log.txt");
    exist_file+=1;
    outlog<<exist_file;
    ofstream out("dir.csv",std::fstream::app);
    out<<filename<<endl;
    return;
}
bool function2(){
    
    int choice;
    // while ()
    string s;
    cout<<"nhap file ";
    getline(cin,s);
    add_file(s);
    return 1;
}
void menu(){

}
void function3(){
    string line;
    string deleteline;
    getline(cin,deleteline);
    deleteline;
    ifstream in("dir.csv");
    ofstream temp("temp.csv");
    while (getline(in,line)){
        // line+="\n";
        if (deleteline==line){
            line="";
        }
        temp << line << endl;
    }
    temp.close();
    in.close();
    remove("dir.csv");
    rename("temp.csv","dir.csv");
}
int main()
{
int choice;
bool gameOn = true;
while (gameOn != false){
cout << "*******************************\n";
cout << " 1 - Search \n";
cout << " 2 - Add File\n";
cout << " 3 - Delete File \n";
cout << " 4 - Exit.\n";
cout << " Enter your choice and press return: \n";

// cin >> choice;
scanf("%d \n ", &choice);

    switch (choice)
    {
        case 1:
        cout << "Search File\n";
        // cout<<"Input string \n";
        function1();
        break;
        case 2:

        cout << "Add File\n";
        function2();
        // return 0;
        break;

        case 3:
        cout << "Delete File\n";
        function3();
        // rest of code here
        break;
        case 4:
        cout << "End of Program.\n";
        gameOn = false;
        // return 0;
        break;
        default:
        cout << "Not a Valid Choice. \n";
        cout << "Choose again.\n";
        cin >> choice;
        break;
    }

}
// return 0;
}

