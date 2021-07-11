#include<iostream>
#include<string>
using namespace std;
typedef struct SNode* node;
struct SNode{
    string data;
    node next;
};

struct Stack{
    node top;
};
void init(Stack&a);
bool isEmpty(node p);
node initNode(string s);
bool checkEmpty(Stack a);
bool Push(Stack &a, node p);
string Pop(Stack& a, string s);
void print(Stack a);
int countNode(Stack a);