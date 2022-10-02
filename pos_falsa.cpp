#include <math.h>
#include <iostream>
#include <cstdio>
#include <exception>
#include "expr.h"

using namespace std;

long double pos_falsa (long double a, long double b, long double e1, long double e2, expr func, int max){
    long double fa, fb, x, fx;
    int k = 1;

    while(k <= max){
        fa = func.avaliar(a);
        fb = func.avaliar(b);
        if (b - a < e1) return ((a + b)/2);
        if (abs(fa) < e2) return a;
        if (abs(fb) < e2) return b;
        
        
        x = (a * fb - b * fa)/(fb - fa);
        fx = func.avaliar(x);

        cout << "Passo " << k << ":\n";
        cout << "a  = " << a << " f(a) = " << fa << '\n';
        cout << "b  = " << b << " f(b) = " << fb << '\n';
        cout << "x  = " << x << " f(x) = " << fx << '\n';

        if(fx < e2) return x;
        if(fa * fx > 0){
            a = x;
            if (b - a < e1) return ((a + b)/2);
        }
        else{
            b = x;
            if (b - a < e1) return ((a + b)/2);
        }
        k++;
    }
    return ((a + b)/2);
}

int receber(expr* ex, long double* a, long double* b, long double* e1, long double* e2, int* max){
    string s;
    int idx = 0;
    int x = 1;

    cout << "Insira a expressão (Digite \"Sair\" para sair):\n";
    cin >> s;
    if(s == "Sair") return 1;
    cout << "Insira o intervalo [a,b] (no formato \"a, b\"):\n";
    x += scanf("%Lf, %Lf", a, b);
    cout << "Insira as precisões e1 e e2 (no formato \"e1, e2\")\n";
    x += scanf("%Lf, %Lf", e1, e2);
    cout << "Insira o número máximo de iterações:\n";
    x += scanf("%d", max);
    
    cout << x << "\n";
    if (x == 6){
        try {
            ex->preencher(s, idx);
        }
        catch (exception e){
            cout << "Erro: expressão inválida!\n";
            receber(ex, a, b, e1, e2, max);
        }
        return 0;
    }
    else{
        cout << "Erro: input inválido!\n";
        receber(ex, a, b, e1, e2, max);
    }
    return 1;
}

int main(){

    expr ex;
    ex.iniciar();
    long double a, b, e1, e2;
    int max;

    if (receber(&ex, &a, &b, &e1, &e2, &max)) return 0;

    if (ex.esq == NULL) cout << "nulo esq\n";
    if (ex.dir == NULL) cout << "nulo dir\n";

    printf("Raiz de f(x): %Lf\n", pos_falsa(a, b, e1, e2, ex, max));
}