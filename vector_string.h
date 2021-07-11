#include<iostream>
#include "data_preprocessing.h"
struct doc{
    dict data;
    doc* next;
};
struct doc_arr{
    doc* top;
};
doc* initDoc(dict data);
bool isEmpty(doc_arr a);
void initDoc_arr(doc_arr& a);
void tf(dict* &a,int cn);
bool PUSH(doc_arr& a, dict data);
doc* Pop(doc_arr& a) ;
int count_doc(doc_arr a);