#include <math.h>
#include <iostream>
#include <cstdio>
#include <exception>
#include "expr.h"

long double secante(long double e1, long double e2, long double apx1, long double apx2,  expr ex, int max){
    long double fx0, fx1, fx2, x0 = apx1, x1 = apx2, x2;
    int k = 1;

    if(abs(ex.avaliar(x0)) < e1) return apx1;
    if(abs(ex.avaliar(x1)) < e1) return apx2;

    while(k <= max){
        x2 = x1 - ((ex.avaliar(x1)/(ex.avaliar(x1) - ex.avaliar(x0))) * (x1 - x0));
        fx2 = ex.avaliar(x2);

        cout << "Passo " << k << ":\n";
        cout << "x0  = " << x0 << '\n';
        cout << "x1  = " << x1 << '\n';
        cout << "x2  = " << x2 << " f(x1) = " << fx2 << '\n';

        if(abs(fx2) < e1 || (abs(x2 - x1) < e2)) return x2;
        x0= x1;
        x1 = x2;
        k++;
    }
    return x0;
}

int receber(expr* ex, long double* e1, long double* e2, long double* apx1, long double* apx2, int* max){
    string s;
    int idx = 0;
    int x = 1;

    cout << "Insira a expressão da função f(x) (Digite \"Sair\" para sair):\n";
    cin >> s;
    if(s == "Sair") return 1;
    cout << "Insira as precisões e1 e e2 (no formato \"e1, e2\")\n";
    x += scanf("%Lf, %Lf", e1, e2);
    cout << "Insira as duas aproximações iniciais da raiz (no formato \"apx1, apx2\"):\n";
    x += scanf("%Lf, %Lf", apx1, apx2);
    cout << "Insira o número máximo de iterações:\n";
    x += scanf("%d", max);
    
    if (x == 6){
        try {
            ex->preencher(s, idx);
        }
        catch (exception e){
            cout << "Erro: expressão inválida!\n";
            receber(ex, e1, e2, apx1, apx2, max);
        }
        return 0;
    }
    else{
        cout << "Erro: input inválido!\n";
        receber(ex, e1, e2, apx1, apx2, max);
    }
    return 1;
}

int main(){

    expr ex, fi;
    ex.iniciar();
    fi.iniciar();
    long double a, b, e1, e2, apx1, apx2;
    int max;

    if (receber(&ex, &e1, &e2, &apx1, &apx2, &max)){
        cout << "Você saiu\n"; 
        return 0;
    }

    if (ex.esq == NULL) cout << "nulo esq\n";
    if (ex.dir == NULL) cout << "nulo dir\n";

    printf("Raiz de f(x): %Lf\n", secante(e1, e2, apx1, apx2, ex, max));
}