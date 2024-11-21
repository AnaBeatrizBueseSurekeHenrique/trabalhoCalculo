#include <iostream>
#include <iomanip>
#include <string>
#include "metodos.h"
using namespace std;

struct no{
    no* link;
    string equacao;
    double valorx;
    int numx;
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
int encontrarPos(string str, string x, int num){
    int encontradas = 0;
    int pos = 0;
    while(encontradas < num){
        pos = str.find(x, pos);
        pos++;
        encontradas++;
    }
    return pos - 1;
}

string recriaEquacao(string str, int num){
    int pos = encontrarPos(str, "x", num);
    string div = "", numeros;
    int i = pos, aux1, valor;
    aux1 = i;
    while(aux1 >= 0 && (isdigit(str[aux1-1]) || (str[aux1-1] == '.') || (str[aux1-1] == 'x'))){
        aux1--;
    }
    if(aux1 > 0 && str[aux1-1] == '-'){
        div = "-";
    }
    div += str.substr(aux1, i - aux1);
    string aux;
    aux = str.substr(i+2, str.find('=') - (i+2));
    aux = inverteSinais(aux);
    i = str.find('=') + 1;
    numeros = str.substr(i, str.size() - 1);
    string novaString;
    pos++;
    valor = numero(str, &pos);
    novaString = "x" + to_string(valor);
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
/*
    x3 = 2
    Insira a equacao:  2x1+1x2+3x3=9
    Insira o valor inicial para x1:0
    Insira a equacao: 0x1-1x2+1x3=1
    Insira o valor inicial para x2:0
    Insira a equacao: 1x1+0x2+3x3=3
    COISAS PRA FAZER: NUM MAXIMO DE ITERACOES NAO TA FUNCIONANDO
    ALTERNAR TAMBEM O VALOR DE X NO MUDA COLUNAS!!!!
*/
no *insereNo(no *L, string str, double x, int num) {
	no *N, *P;
	N = new no;
	N->equacao = str;
    N->valorx = x;
    N->numx = num;
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

no* mudarEquacao(no *L, int no1, int no2){
    no* aux = L, *aux2 = L;
    string eq;
    for(int i = 1; i < no1; i++){
        aux = aux->link;
    }
    for(int i = 1; i < no2; i++){
        aux2 = aux2->link;
    }
    eq = aux->equacao;
    aux->equacao = aux2->equacao;
    aux2->equacao = eq;
    return L;
}


bool criterioSassenfeld (no *L, int qntdequacoes){
    no *valorPrincipal = inicializaNo(valorPrincipal);
    no *atribuirValor = L;
    int num = 1, linhaErro;
    double max = -1;
    while(atribuirValor != NULL){
        valorPrincipal = insereNo(valorPrincipal,atribuirValor->equacao, 1, atribuirValor->valorx);
        atribuirValor = atribuirValor->link;
    }
    no*aux = valorPrincipal;
    while(aux != NULL){
        string eq = "(";
        string div;
        no*aux2 = valorPrincipal;
        for(int soma = 1; soma <= qntdequacoes; soma++){
            int pos = encontrarPos(aux->equacao, "x", soma);
            int aux1;
            aux1 = pos;
            while(aux1 >= 0 && (isdigit(aux->equacao[aux1-1]) || (aux->equacao[aux1-1] == '.') || (aux->equacao[aux1-1] == 'x'))){
                aux1--;
            } 
            if(soma != num){
                eq += aux->equacao.substr(aux1, pos - aux1) + "*(" + to_string(aux2->valorx) + ")+";
            } else{
                div = aux->equacao.substr(aux1, pos - aux1);
            }
            aux2 = aux2->link;
        }  
        eq.pop_back();
        eq += ")/" + div;
        if(div != "0"){
            double max2 = realizaEquacao(eq, 0);
            aux->valorx = max2;
            if(max < max2){
                max = max2;
            }
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
no* mudarColunas(no* L, int no1, int no2){
    no *aux = L;
    double xValor;
    while(aux != NULL){
        string str = aux->equacao;
        if(str[0] != '-'){
            str = "+" + str;
        }
        int pos1 = str.find("x" + to_string(no1));
        int aux1 = pos1, max1, max2, min1, min2, tam1, tam2;
        while(isdigit(str[pos1+1])){
            pos1++;
        }
        max1 = pos1;
        int pos2 = str.find("x" + to_string(no2));
    
        int aux2 = pos2, min, max;
        while(isdigit(str[pos2+1])){
            pos2++;
        }
        max2 = pos2;
        while(aux1 >= 0 && (isdigit(str[aux1-1]) || (str[aux1-1] == '.') || (str[aux1-1] == 'x'))){
            aux1--;
        }
        while(aux2 >= 0 && (isdigit(str[aux2-1]) || (str[aux2-1] == '.') || (str[aux2-1] == 'x'))){
            aux2--;
        }
        min1 = aux1;
        min2 = aux2;
        tam1 = max1 - min1 + 1;
        tam2 = max2 - min2 + 1;
        string x1 = "", x2 = "";
        if(aux2 > 0 && str[aux2 - 1] == '-'){
            aux2--;
            tam1++;
            tam2++;
            if(min1 > 0){
                min1--;
            }
            if(min2 > 0){
                min2--;
            }
            x1 = "+";
        }
        if(aux1 > 0 && str[aux1 - 1] == '-'){
            aux1--;
            tam2++;
            tam1++;
            if(min2 > 0){
                min2--;
            }
            if(min1 > 0){
                min1--;
            }
            x2 = "+";
        }
        x1 += str.substr(aux1, pos1 - aux1 + 1);
        x2 += str.substr(aux2, pos2 - aux2 + 1);
        str.replace(min1, tam1, x2);
        str.replace(min2, tam2, x1);
        if(str[0] == '+'){
            str.erase(0, 1);
        }
        aux->equacao = str;
        aux = aux->link;
    }
    aux = L;
    for(int i = 1; i < no1; i++){
        aux = aux->link;
    }
    no *aux2 = L;
    for(int i = 1; i < no2; i++){
        aux2 = aux2->link;
    }
    xValor = aux->valorx;
    aux->valorx = aux2->valorx;
    aux2->valorx = xValor;
   
    xValor = aux->numx;
    aux->numx = aux2->numx;
    aux2->numx = xValor;
    return L;
}

void mostrarEquacao(no *L){
    no* aux = L;
    while(aux != NULL){
        cout << "EQ: " << aux->equacao << endl;
        cout << "VAL: " << aux->numx << endl;
        aux = aux->link;
    }
}
no* criterioAplicacao(no *L, int qntdequacoes, bool *resolucao){
    int i = 1;
    *resolucao = criterioSassenfeld(L, qntdequacoes);
    while(i <= qntdequacoes && !(*resolucao)){
        int j = 1;
        while(j <= qntdequacoes && !(*resolucao)){
            if(j != i){
                L = mudarEquacao(L, i, j);
                *resolucao = criterioSassenfeld(L, qntdequacoes);
                if(!*resolucao){               
                    L = mudarColunas(L, i, j);
                    *resolucao = criterioSassenfeld(L, qntdequacoes);
                    if(!resolucao){
                        L = mudarColunas(L, i,j);
                        L = mudarEquacao(L, i, j);
                    }
                }
            }
            j++;
        }
        i++;
    }
    return L;
}


bool calculoPrec(double prec, no*L, no *N){
    no* Aux = L;
    double maxEq = -1, maxNum = -1;
    while(Aux != NULL){
        if(moduloEq(N->valorx, Aux->valorx) > maxEq){
            maxEq = moduloEq(N->valorx, Aux->valorx);
        }
        if(moduloVar(Aux->valorx) > maxNum){
            maxNum = moduloVar(Aux->valorx);
        }
        N = N->link;
        Aux = Aux->link;
    }
    double max = (maxEq)/(maxNum);

    if(moduloVar(max) < prec){
        return true;
    } else{
        return false;
    }
}

void mostraValores(no *L, int casasDecimais){
    no *aux = L;
    int i = 1, x;
    cout << endl;
    string str = "";

     while(aux != NULL){
        int pos = 0;
        while(!(isdigit(aux->equacao[pos]))){
            pos++;
        }
        x = numero(aux->equacao, &pos);
        cout << "x" << x  << " = " << setprecision(casasDecimais) <<  fixed << aux->valorx <<endl;
        aux = aux->link;
        i++;
    }
}


no* realiza(no* L, double prec, int *it, int max, int casaDecimais){
    no* aux = L;
    no* aux2 = L;
    no* aux3 = inicializaNo(aux3);
    int j;
    while(aux != NULL){
        aux3 = insereNo(aux3, aux->equacao, aux->valorx, aux->numx);
        aux3->equacao = aux->equacao;
        for(int i = aux3->equacao.find('='); i < aux3->equacao.size(); i++){
            if(aux3->equacao[i] == 'x'){
                int l = i+1;
                j = numero(aux3->equacao, &(l));
                while(aux2->numx != j){
                    aux2 = aux2->link;
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
    }
    (*it)++;
    cout << "Iteracao: " << *it;
    mostraValores(L, casaDecimais);
    if(calculoPrec(prec, L, aux3) && (*it) < max){
        return L;
    } else{
        realiza(L, prec, it, max, casaDecimais); 
    }
}

