#include <iostream>
#include <iomanip>
#include "metodos.h"
using namespace std;

struct no{
    no* link;
    string equacao;
    double valorx;
};

no* inicializaNo(no* N){
    return NULL;
}

string inverteSinais(string str){
    int i = 0;
    while(str[i] != '=' && i < str.size()){
        if(i == 0 || isalpha(str[i-1]) || isdigit(str[i-1])){
            switch(str[i]){
                case '+':
                    str[i] = '-';
                    break;
                case '-':
                    str[i] = '+';
                    break;
            }
        }
        i++;
    }
    return str;
}

string recriaEquacao(string str, int num){
    int pos = str.find('x' + to_string(num));
    string div, numeros;
    int i = pos, aux1;
    aux1 = i;
    while(aux1 >= 0 && (isdigit(str[aux1-1]) || (str[aux1-1] == '.') || (str[aux1-1] == 'x'))){
        aux1--;
    }
    div = str.substr(aux1, i - aux1);
    string aux;
    aux = str.substr(i+2, str.find('=') - (i+2));
    aux = inverteSinais(aux);
    i = str.find('=') + 1;
    numeros = str.substr(i, str.size() - 1);
    string novaString;
    novaString = "x" + to_string(num);
    novaString += "=(" + numeros;
    if(aux1 > 0){
        string aux2;
        aux2 = str.substr(0, aux1 -1);
        aux2 = inverteSinais(aux2);
        if(isdigit(aux2[0])){
            aux2 = '-' + aux2;
        }
        novaString += aux2;
    }
    novaString += aux + ")/" + div; 
    return novaString;
}

no *insereNo(no *L, string str, double x) {
	no *N, *P;
	N = new no;
	N->equacao = str;
    N->valorx = x;
	N->link = NULL;
	if (L == NULL){
		L = N;
	}else {
		P = L;	
		while(P->link != NULL) {
			P = P->link;
		}
		P->link = N; 	
	} 
	return L;
}
bool criterioSassenfeld (no *L, int qntdequacoes){
    no * aux = L;
    int num = 1;
    double max = -1;
    while(aux != NULL){
        string eq = "(";
         string div;
        for(int soma = 1; soma <= qntdequacoes; soma++){
            int pos = aux->equacao.find('x' + to_string(soma));
            int aux1;
            aux1 = pos;
            while(aux1 >= 0 && (isdigit(aux->equacao[aux1-1]) || (aux->equacao[aux1-1] == '.') || (aux->equacao[aux1-1] == 'x'))){
                aux1--;
            } 
            if(soma != num){
                eq += aux->equacao.substr(aux1, pos - aux1) + "+";
            } else{
                div = aux->equacao.substr(aux1, pos - aux1);
            }
        }  
    eq.pop_back();
    eq += ")/" + div;
    double max2 = realizaEquacao(eq, 0);
    if(max < max2){
        max = max2;
    }
    aux = aux->link;
    num++;
    }
    if(max < 1){
        return true;
    } else{
        return false;
    }
}
bool calculoPrec(double prec, no*L, no *N){
    no* Aux = L;
    double max = (N->valorx - Aux->valorx);
    N = N->link;

    Aux = Aux->link;
    while(Aux != NULL){
        if((N->valorx - Aux->valorx) > max){
            max = (N->valorx - Aux->valorx);
        }
        N = N->link;
        Aux = Aux->link;
    }
    if(moduloVar(max) < prec){
        return true;
    } else{
        return false;
    }
}

void mostraValores(no *L, int casasDecimais){
    no *aux = L;
    int i = 1;
    cout << endl;
     while(aux != NULL){
        cout << "x" << i << " = " << setprecision(casasDecimais) <<  fixed << aux->valorx <<endl;
        aux = aux->link;
        i++;
    }
}
no* realiza(no* L, double prec, int *it, int max, int casaDecimais){
    no* aux = L;
    no* aux2 = L;
    no* aux3 = inicializaNo(aux3);
    int j;
    int m = 1;
    while(aux != NULL){
        aux3 = insereNo(aux3, aux->equacao, aux->valorx);
        aux3->equacao = aux->equacao;
        for(int i = aux3->equacao.find('='); i < aux3->equacao.size(); i++){
            if(aux3->equacao[i] == 'x'){
                int l = i+1;
                j = numero(aux3->equacao, &(l));
                int k = 1;
                while(k < j){
                    aux2 = aux2->link;
                    k++;
                }
                string substituir = "";
                if(isdigit(aux3->equacao[i-1])){
                    substituir = "*";
                }
                substituir += to_string(aux2->valorx);
                aux3->equacao.replace(i, l-i, substituir);
                aux2 = L;
            }
        }
        string subString = aux3->equacao.substr(aux3->equacao.find('=')+1, aux3->equacao.size() - aux3->equacao.find('=')+1);
        aux->valorx = realizaEquacao(subString, 0);   
        aux = aux->link;
        m++;
    }
    (*it)++;
    cout << "Iteracao: " << *it;
    mostraValores(L, casaDecimais);
    if(calculoPrec(prec, L, aux3) && *it < max){
        return L;
    } else{
        realiza(L, prec, it, max, casaDecimais); 
    }
}

