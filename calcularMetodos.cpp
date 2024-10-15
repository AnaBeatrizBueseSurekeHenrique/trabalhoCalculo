#include <iostream>
#include <math.h>
#include <string>
#include "lerString.h"

using namespace std;

double equacao(double x){
    double result =log(x) + x + 4;
    return result;
}

double derivada(double x){
    return (x+1)/x;
}
double moduloEq(double r1, double r2){
    double sub = r2-r1;
    if(sub < 0){
        return (sub*(-1));
    }else{
        return sub;
    }
}

double moduloVar(double x){
    if(x < 0){
        return x * -1;
    } else{
        return x;
    }
}

double funcItera(double x){
    double result = cos(x) - pow(EulerConstant, -1*(pow(x, 2))) + x;
    return result;
}

double bisseccao(double r1, double r2, double prec, int max, int *itera, string equacao){
    string aux;
    *itera = 0;
    double fIn, meio, fMeio;
    if(moduloEq(r1,r2) > prec){
        while(moduloEq(r1,r2) > prec && *itera < max){
            meio = (r1+r2)/2;
            cout << "MEIO: " << meio << endl;
            aux = equacao;
            fIn = realizaEquacao(aux, r1);
            aux = equacao;
            fMeio = realizaEquacao(aux, meio);
            if(fIn* fMeio < 0){
                r2 = meio;
            } else{
                r1 = meio;
            }
            *itera = *itera+1;
        }
        return meio;
    } else{
        return r1;
    }
}

double mil(double x, double prec, int MAX, int *itera, string equacao, string equacaoIterativa){
    *itera = 1;
    double result;
    double antX = x;
    if(moduloVar(realizaEquacao(equacao,x)) > prec){
        x = realizaEquacao(equacaoIterativa, antX);
        while(moduloVar(realizaEquacao(equacao,x)) > prec && moduloEq(x, antX) > prec && *itera < MAX){
            antX = x;
            x = realizaEquacao(equacaoIterativa, antX);
            (*itera)++;     
        }
    }
    return x;
}

double newton(double x0, double prec, double max,int *itera, string equacao, string derivada){
    *itera = 1;
    double fx, fxlinha, x1;
    fx = realizaEquacao(equacao, x0);
    cout << "FX" << fx << endl;
    if(moduloVar(fx) > prec){
        fxlinha = realizaEquacao(derivada, x0);
        x1 = x0 - (fx/fxlinha);
        cout << "X1" << x1 << endl;
        fx = realizaEquacao(equacao, x1);
        cout << "FX" <<fx << endl;
        while(moduloVar(fx) > prec && moduloEq(x1,x0) > prec && *itera <= max){
            *itera++;
            x0 = x1;
            fxlinha = realizaEquacao(derivada, x0);
            x1 = x0 - (fx/fxlinha);
            fx = realizaEquacao(equacao, x1);
        }
        return x1;
    } else{
        return x0;
    }
}

double secante( double x0, double x1, double prec, int max, string equacao){
    int k = 1;
    double x2;
    if(moduloVar(realizaEquacao(equacao, x0)) < prec){
        return x0;
    } else{
        if(moduloVar(realizaEquacao(equacao, x1)) < prec && moduloEq(x1, x0) < prec){
            return x1;
        } else{
            
            while(moduloVar(realizaEquacao(equacao, x1)) > prec && moduloEq(x1,x0) > prec &&  k < max){
                x2 = x1;
                x1 = x1 - (realizaEquacao(equacao, x1)*(x1 - x0))/(realizaEquacao(equacao, x1) - realizaEquacao(equacao, x0));
                x0 = x2;
                k++;
            }
            return x1;
        }
    }
}

double falsi( double a, double b, double prec1, double prec2, int max, string equacao){
    int k = 1;
    double x, m;
    if(moduloEq(a,b) < prec1){
        return a+b/2;
    } else{
        if(moduloVar(realizaEquacao(equacao, a)) < prec2 || moduloVar(realizaEquacao(equacao, b)) < prec2){
            return a;
        } else{
            x = (a*realizaEquacao(equacao, b) - b*(realizaEquacao(equacao, a)) / (realizaEquacao(equacao,b) - realizaEquacao(equacao,a)));
            m = realizaEquacao(equacao, a);
            cout << "X" << x << endl;
            while(moduloVar(realizaEquacao(equacao, x)) > prec2 &&  k < max && moduloEq(a,b)){
                if(m*(realizaEquacao(equacao, x)) > 0){
                    a = x;
                } else{
                    b = x;
                }
                 x = (a*realizaEquacao(equacao, b) - b*(realizaEquacao(equacao, a)) / (realizaEquacao(equacao,b) - realizaEquacao(equacao,a)));
                m = realizaEquacao(equacao, a);
                k++;
                cout << "x" << x << endl;
            }
            cout << "Iteracoes: " << k << endl;
            return x;
        }
    }
}

int main(){
    double r1, r2, prec, prec2;
    int max;
    int itera;
    int entrada;
    string equacao, equacao2;
    cout << "Quais dos metodos voce gostaria de utilizar?" << endl;
    cout << "1. Bisseccao" << endl << "2. Mil" << endl << "3. Newton" << endl << "4. Secante" << "5. Regula Falsi" << endl;
    cin >> entrada;
    switch(entrada){
        case 1:
            cout << "Insira o valor de a e b:" << endl;
            cin >> r1 >> r2;
            cout << "Insira o valor da precisao: " << endl;
            cin >> prec;
            cout << "Insira o valor maximo de iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equacao: " << endl;
            cin >> equacao;
            cout << "Raiz: " << bisseccao(r1,r2, prec, max, &itera, equacao) << endl;
            cout << "Numero de iteracoes: " << itera;
            break;
        case 2:
            cout << "Insira o valor de x0" << endl;
            cin >> r1;
            cout << "Insira o valor da precisao: " << endl;
            cin >> prec;
            cout << "Insira o valor maximo de iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equação: " << endl;
            cin >> equacao;
            cout << "Insira a equação iterativa: " << endl;
            cin >> equacao2;
            cout << "Raiz: " << mil(r1,prec,max, &itera, equacao, equacao2);
            cout << "Numero de iteracoes: " << itera;
            break;
        case 3:
            cout << "Insira o valor de x0" << endl;
            cin >> r1;
            cout << "Insira o valor da precisao: " << endl;
            cin >> prec;
            cout << "Insira o valor maximo de iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equacao: " << endl;
            cin >> equacao;
            cout << "Insira a derivada da equacao: " << endl;
            cin >> equacao2;
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
            cin >> equacao;
            cout << "Raiz: " << secante(r1, r2, prec, max, equacao);
            break;
        case 5:
            cout << "a: " << endl;
            cin >> r1;
            cout << "b: " << endl;
            cin >> r2;
            cout << "Prec1: " << endl;
            cin >> prec;
            cout << "Prec2: " << endl;
            cin >> prec2;
            cout << "Maximo iteracoes: " << endl;
            cin >> max;
            cout << "Insira a equacao: " << endl;
            cin >> equacao;
            cout << falsi(r1, r2, prec, prec2 , max, equacao);
            break;
    }
} 
