#include<iostream>
#include<math.h>
#include "vector_string.h"
#include "data_preprocessing.h"
int count_vec(double* a){
    return sizeof(a)/sizeof(a[0]);
}
double euclid_dis(double* a,double *b){
    int n1 = count_vec(a);
    int n2= count_vec(b);
    double sum =0;
    for (int i = 0;i<n1;i++){
        if (i == n2){
            b[i]=0;        
        }
        sum+= pow((a[i]-b[i]),2);
    }
    return sqrt(sum);
}
double cosine_similarity(double* a,double *b){
    int n1 = count_vec(a);
    double sum =0, denoma =0,denomb = 0;
    for (int i =0;i<n1;i++){
        sum+= a[i]*b[i];
        denoma += a[i]*a[i];
        denomb += b[i]*b[i];
    }
    return sum/(sqrt(denoma)*sqrt(denomb));
}
void tf(dict* &a,int cn){
    int max_w = a[0].index;
    for (int i = 0;i<cn;i++){
        if (max_w<a[i].index){
            max_w = a[i].index;
        }
    }
    for (int i =0;i<cn;i++){
        a[i].index= (double)a[i].index/max_w;
    }

}

// void tf_idf(doc_arr& a){
//     int n = count_doc(a);
//     for (doc* p = a.top;p!=NULL;p=p->next){
//         tf(p->data,n);
//     }
//     // for (doc* p = a.top;p!=NULL;p=p->next){
//     //     for (int i = 0;i<n;i++)
//     // } 
// }
doc* initDoc(dict data){
    doc* p = new doc();
    if (p==NULL){
        return NULL;
    }
    p->data= data;
    p->next=NULL;
    return p;
}
bool isEmpty(doc_arr a){
    if (a.top==NULL) return 1;
    else return 0;
}
void initDoc_arr(doc_arr& a){
    a.top = NULL;
    
}
bool PUSH(doc_arr& a, dict data) {
	doc* p = initDoc(data);
	if (isEmpty(a)) {
		a.top = p;
		return 0;
	}
	else {
		p->next = a.top;
		a.top = p;
		return 1;
	}
}
doc* Pop(doc_arr& a) {
	if (isEmpty(a)) {
		return NULL;
	}
	doc* p = a.top;
	a.top = a.top->next;
	return a.top;
}
int count_doc(doc_arr a){
    int count = 0;
    for (doc* p = a.top;p!=NULL;p=p->next){
        count++;
    }
    return count;
}