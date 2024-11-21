#include <iostream>
#include <math.h>
#include <string>
#include "leEquacao.h"

using namespace std;

double equacao(double x){
    double result =log(x) + x + 4;
    return result;
}

double derivada(double x){
    return (x+1)/x;
}

double funcItera(double x){
    double result = cos(x) - pow(EulerConstant, -1*(pow(x, 2))) + x;
    return result;
}

double bisseccao(double r1, double r2, double prec, int max, int *itera, string equacao, int casasDecimais){
    string aux;
    *itera = 0;
    double fIn, meio, fMeio;
    if(moduloEq(r1,r2) > prec){
        while(moduloEq(r1,r2) > prec && *itera < max){
            meio = (r1+r2)/2;
            (*itera)++;
            cout << setprecision(casasDecimais) <<  fixed << "x" << *itera << " = " << meio<<  endl;
            aux = equacao;
            fIn = realizaEquacao(aux, r1);
            aux = equacao;
            fMeio = realizaEquacao(aux, meio);
            if(fIn* fMeio < 0){
                r2 = meio;
            } else{
                r1 = meio;
            }
        }
        return meio;
    } else{
        return r1;
    }
}

double mil(double x, double prec, int MAX, int *itera, string equacao, string equacaoIterativa, int casasDecimais){
    *itera = 1;
    double result;
    double antX = x;
    if(moduloVar(realizaEquacao(equacao,x)) > prec){
        x = realizaEquacao(equacaoIterativa, antX);
        cout << setprecision(casasDecimais) << fixed << "x" << *itera << " = " << x<<  endl;
        while(moduloVar(realizaEquacao(equacao,x)) > prec && moduloEq(x, antX) > prec && *itera < MAX){
            (*itera)++;    
            antX = x;
            x = realizaEquacao(equacaoIterativa, antX);
            cout <<  "x" << *itera << " = " << x<< endl;
        }
    }
    return x;
}

double newton(double x0, double prec, double max,int *itera, string equacao, string derivada, int casasDecimais){
    *itera = 1;
    double fx, fxlinha, x1;
    fx = realizaEquacao(equacao, x0);
    if(moduloVar(fx) > prec){
        fxlinha = realizaEquacao(derivada, x0);
        x1 = x0 - (fx/fxlinha);
        cout << setprecision(casasDecimais) << fixed << "x" << *itera << " = " << x1 <<  endl;
        fx = realizaEquacao(equacao, x1);
        while((moduloVar(fx) > prec && moduloEq(x1,x0) > prec) && (*itera) <= max){
            (*itera)++;
            x0 = x1;
            fxlinha = realizaEquacao(derivada, x0);
            x1 = x0 - (fx/fxlinha);
            fx = realizaEquacao(equacao, x1);
            cout << "x" << *itera << " = " << x1 << endl;
        }
        return x1;
    } else{
        return x0;
    }
}

double secante( double x0, double x1, double prec, int max, string equacao, int *it, int casasDecimais){
    *it = 0;
    double x2;
    if(moduloVar(realizaEquacao(equacao, x0)) < prec){
        return x0;
    } else{
        if(moduloVar(realizaEquacao(equacao, x1)) < prec && moduloEq(x1, x0) < prec){
            return x1;
        } else{
            while(moduloVar(realizaEquacao(equacao, x1)) > prec && moduloEq(x1,x0) > prec && (*it) < max){
                x2 = x1;
                x1 = x1 - (realizaEquacao(equacao, x1)*(x1 - x0))/(realizaEquacao(equacao, x1) - realizaEquacao(equacao, x0));
                x0 = x2;
                cout << setprecision(casasDecimais) << fixed << "x" << (*it) + 2 << " =" << x1 <<  endl;
                (*it)++;
            }
            return x1;
        }
    }
}

double falsi( double a, double b, double prec1, double prec2, int max, string equacao, int *itera, int casasDecimais){
    *itera = 0;
    double x, m;
    if(moduloEq(a,b) < prec1){
        return a+b/2;
    } else{
        if(moduloVar(realizaEquacao(equacao, a)) < prec2 || moduloVar(realizaEquacao(equacao, b)) < prec2){
            return a;
        } else{
            x = (a*realizaEquacao(equacao, b) - b*realizaEquacao(equacao, a)) / (realizaEquacao(equacao,b) - realizaEquacao(equacao,a));
            
            m = realizaEquacao(equacao, a);
            cout << setprecision(casasDecimais) << fixed <<"x" << *itera << " = " << x << endl;
            (*itera)++;
            while(moduloVar(realizaEquacao(equacao, x)) > prec2 &&  (*itera) < max && moduloEq(a,b)){
                if(m*(realizaEquacao(equacao, x)) > 0){
                    a = x;
                } else{
                    b = x;
                }
                x = (a*realizaEquacao(equacao, b) - b*realizaEquacao(equacao, a)) / (realizaEquacao(equacao,b) - realizaEquacao(equacao,a));
                m = realizaEquacao(equacao, a);
                cout << "x" << *itera << " = " << x << endl;
                (*itera)++;
            }
            return x;
        }
    }
}
