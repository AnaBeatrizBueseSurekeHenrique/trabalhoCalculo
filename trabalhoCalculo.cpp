#include <iostream>
#include "gaussSeiden.h"
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

void guia();
void calculadora();
void metodos();
double realizaEquacao();
int main(){
    char entrada;
    cout << "1. Calculadora" << endl;
    cout << "2. Metodos" << endl;
    cout << "3. Gauss-Seiden" << endl;
    cin >> entrada;
    switch(entrada){
        case '1':
            calculadora();
            break;
        case '2':
            metodos();
            break;
        case '3':
            realizaEquacao();
            break;
    }
}
void guia(){
    cout << "+: soma              |   -: subtracao" << endl;
    cout << "*: multiplicacao     |   /: divisao" << endl;
    cout << "^: potencia          |   (nota: raiz e denotada por ^(1/n) com n sendo o numero da raiz)" << endl;
    cout << "sin OU sen: seno     |   sec: secante" << endl;
    cout << "cos: cosseno         |   cot: cotangente" << endl;
    cout << "cossec: cossecante   |   tan OU tg = tangente" << endl;
    cout << "ln: log de base e    |   log OU lg: log de base 10" << endl;
    cout << "e: numero de euler   |   x: sempre usado como variavel" << endl;
}
void calculadora(){
    string str;
    double x;
    cout << "Exemplo de equacao: x*2+5^(1/2)" << endl;
    cout << "Nota: utilize sempre * para multiplicar x!" << endl;
    guia();
    cout << "Insira a equacao: ";
    cin.ignore();
    getline(cin, str);
    cout << "Insira o valor de x: ";
    cin >> x;
   str.erase(remove_if(str.begin(), str.end(), ::isspace),
        str.end());
    cout << realizaEquacao(str, x);
}

void metodos(){
    double r1, r2, prec, prec2;
    int max;
    int itera;
    int entrada;
    string equacao, equacao2;
    guia();
    cout << "Quais dos metodos voce gostaria de utilizar?" << endl;
    cout << "1. Bisseccao" << endl << "2. Mil" << endl << "3. Newton" << endl << "4. Secante" << endl << "5. Regula Falsi" << endl;
    cin >> entrada;
    switch(entrada){
        case 1:
            cout << "Insira o valor de a: " << endl;
            cin >> r1;
            cout << "Insira o valor de b: " << endl;
            cin >> r2;
            cout << "Insira o valor da precisao: " << endl;
            cin >> prec;
            cout << "Insira o valor maximo de iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equacao: " << endl;
            cin.ignore();
            getline(cin, equacao);
            equacao.erase(remove_if(equacao.begin(), equacao.end(), ::isspace),
                equacao.end());
            cout << "Raiz: " << bisseccao(r1,r2, prec, max, &itera, equacao) << endl;
            cout << "Numero de iteracoes: " << itera;
            break;
        case 2:
            cout << "Insira o valor de x0: " << endl;
            cin >> r1;
            cout << "Insira o valor da precisao: " << endl;
            cin >> prec;
            cout << "Insira o valor maximo de iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equacao: " << endl;
            cin.ignore();
            getline(cin, equacao);
            equacao.erase(remove_if(equacao.begin(), equacao.end(), ::isspace),
                equacao.end());
            cout << "Insira a equacao iterativa: " << endl;
            getline(cin, equacao2);
            equacao2.erase(remove_if(equacao2.begin(), equacao2.end(), ::isspace),
                equacao2.end());
            cout << "Raiz: " << mil(r1,prec,max, &itera, equacao, equacao2) << endl;
            cout << "Numero de iteracoes: " << itera;
            break;
        case 3:
            cout << "Insira o valor de x0: " << endl;
            cin >> r1;
            cout << "Insira o valor da precisao: " << endl;
            cin >> prec;
            cout << "Insira o valor maximo de iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equacao: " << endl;
             cin.ignore();
            getline(cin, equacao);
            equacao.erase(remove_if(equacao.begin(), equacao.end(), ::isspace),
                equacao.end());
            cout << "Insira a derivada da equacao: " << endl;
            getline(cin, equacao2);
            equacao2.erase(remove_if(equacao2.begin(), equacao2.end(), ::isspace),
                equacao2.end());
            cout << "Raiz: " << newton(r1,prec,max, &itera, equacao, equacao2);
            cout << endl << "Numero de iteracoes: " << itera << endl;
            break;
        case 4:
            cout << "Insira o valor de x0: " << endl;
            cin >> r1;
            cout << "Insira o valor de x1: " << endl;
            cin >> r2;
            cout << "Insira o valor da precisao: " << endl;
            cin >> prec;
            cout << "Insira o valor maximo de iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equacao: " << endl;
            cin.ignore();
            getline(cin, equacao);
            equacao.erase(remove_if(equacao.begin(), equacao.end(), ::isspace),
                equacao.end());
            cout << "Raiz: " << secante(r1, r2, prec, max, equacao, &itera);
            cout << endl << "Numero de iteracoes: " << itera << endl;
            break;
        case 5:
            cout << "Insira o valor de a: " << endl;
            cin >> r1;
            cout << "Insira o valor de b: " << endl;
            cin >> r2;
            cout << "Insira o valor da Prec1: " << endl;
            cin >> prec;
            cout << "Insira o valor da Prec2: " << endl;
            cin >> prec2;
            cout << "Insira o valor maximo de iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equacao: " << endl;
            cin.ignore();
            getline(cin, equacao);
            equacao.erase(remove_if(equacao.begin(), equacao.end(), ::isspace),
                equacao.end());
            cout << setprecision(20) << "Raiz: " << falsi(r1, r2, prec, prec2 , max, equacao, &itera) << fixed;
            cout << endl << "Numero de iteracoes: " << itera << endl;
            break;
    }
}
double realizaEquacao(){
    no* noEquacao;
    string str;
    double x;
    int i;
    int pos;
    int max, itera = 0, casas;
    cout << "Insira a quantidade de equacoes: ";
    cin >> i;
    guia();
    cout << "Insira a equacao, usando a notacao x1, x2...xn para as variaveis" << endl;
    cout << "Exemplo: 1x1+2x2-0x3 = 2" << endl;
    noEquacao = inicializaNo(noEquacao);
    for(int j = 1; j <= i; j++){
            cout << "Insira a equacao: " ;
            cin.ignore();
            getline(cin, str);
            str.erase(remove_if(str.begin(), str.end(), ::isspace),
                str.end());
            pos = str.find("0x"+to_string(j));
            if(pos != string::npos && !isdigit(str[pos-1])){
            while(pos != string::npos){
                cout << "Nao ha multiplicador de x" << j << ", insira uma linha que contenha!" << endl;
                getline(cin, str);
                str.erase(remove_if(str.begin(), str.end(), ::isspace),
                    str.end());
                pos = str.find(("0x"+to_string(j)));
            }
        }
        cout << "Insira o valor inicial para x" << j << ":";
        cin >> x;
        noEquacao = insereNo(noEquacao, str, x);
    }
    double prec;
    cout << "Insira a precisao: " << endl;
    cin >> prec;
    cout << "Insira o numero maximo de iteracoes: " << endl;
    cin >> max;
    cout << "Insira a quantidade de casas decimais: " << endl;
    cin >> casas;
    if(criterioSassenfeld(noEquacao, i)){
        no *aux = noEquacao;
        int j = 1;
        for(int j = 1; j<= i; j++){
            aux->equacao = recriaEquacao(aux->equacao, j);
        }
        noEquacao = realiza(noEquacao, prec, &itera, max, casas);
        cout << endl << endl << "Valores finais: ";
        mostraValores(noEquacao, casas);
        cout << "Numero de iteracoes: " << itera;
    } else{
        cout << "Nao e possivel solucionar solucionar este sistema com Gauss-Seidel" << endl;
    }

}