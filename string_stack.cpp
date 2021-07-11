#include<iostream>
#include "stack_str.h"
#include<fstream>
using namespace std;
void init(Stack&a){
    a.top=NULL;
}
bool isEmpty(node p ){
    if (p==NULL) return 1;
    return 0;
}
node initNode(string s){
    node p = new SNode();
    if (p==NULL) return NULL;
    p->data=s;
    p->next=NULL;
    return p;
}
bool checkEmpty(Stack a){
    if (a.top == NULL){
        return 1;
    }
    return 0;
}
bool Push(Stack &a, node p){
    if (isEmpty(p)){
        return 0;
    }
    if (checkEmpty(a)) {
        a.top = p ;
        return 1;
    }
    else{
        p->next=a.top;
        a.top = p; 
        return 1;
    } 
}
string Pop(Stack& a, string s){
    if (checkEmpty(a)){
        return 0;
    }
    node p = a.top;
    a.top = a.top->next;
    s = p->data;
    return s;
}
void print(Stack a) {
    uint16_t buffer; ;
    ofstream out("out_stack.txt");
	for (node p = a.top; p != NULL; p = p->next) {
		// cout << p->data<<" ";
        if (buffer == 0xfeff || buffer == 0x20) { 
            out << endl; 
            continue; 
        }
        if (buffer <= 0x007f) {
            out << (char)(buffer);
        }
        else if (buffer <= 0x07ff)
            out << (char)(0xc0 | ((buffer >> 6) & 0x1f)) << (char)(0x80 | (buffer & 0x3f)); 
        else 
            out << (char)(0xe0 | ((buffer >> 12) & 0x0f)) << (char)(0x80 | ((buffer >> 6) & 0x3f)) << (char)(0x80 | (buffer & 0x3f)); 
    }
	}
int countNode(Stack a){
    int count =0;
    for (node p = a.top;p!=NULL;p=p->next){
        count+=1;
    }
    return count;
}