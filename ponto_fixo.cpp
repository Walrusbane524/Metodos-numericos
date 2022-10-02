#include <math.h>
#include <iostream>
#include <cstdio>
#include <exception>
#include "expr.h"

long double ponto_fixo(long double e1, long double e2, long double apx,  expr ex, expr dex, int max){
    long double fx0, fx1, x0 = apx, x1;
    int k = 1;

    if(abs(ex.avaliar(x0)) < e1) return apx;

    while(k <= max){
        x1 = dex.avaliar(x0);
        fx1 = ex.avaliar(x1);

        cout << "Passo " << k << ":\n";
        cout << "x0  = " << x0 << '\n';
        cout << "x1  = " << x1 << " f(x1) = " << fx1 << '\n';

        if(abs(fx1) < e1 || (abs(x1 - x0) < e2)) return x1;
        x0 = x1;
        k++;
    }
    return x0;
}

int receber(expr* ex, expr* dex, long double* e1, long double* e2, long double* apx, int* max){
    string s, s2;
    int idx = 0;
    int x = 1;

    cout << "Insira a expressão da função f(x) (Digite \"Sair\" para sair):\n";
    cin >> s;
    if(s == "Sair") return 1;
    cout << "Insira a expressão da derivada da função f'(x):\n";
    cin >> s2;
    cout << "Insira as precisões e1 e e2 (no formato \"e1, e2\")\n";
    x += scanf("%Lf, %Lf", e1, e2);
    cout << "Insira a aproximação inicial da raiz:\n";
    x += scanf("%Lf", apx);
    cout << "Insira o número máximo de iterações:\n";
    x += scanf("%d", max);
    
    if (x == 5){
        try {
            ex->preencher(s, idx);
            idx = 0;
            dex->preencher(s2, idx);
            
        }
        catch (exception e){
            cout << "Erro: expressão inválida!\n";
            receber(ex, dex, e1, e2, apx, max);
        }
        return 0;
    }
    else{
        cout << "Erro: input inválido!\n";
        receber(ex, dex, e1, e2, apx, max);
    }
    return 1;
}

int main(){

    expr ex, dex;
    ex.iniciar();
    dex.iniciar();
    long double a, b, e1, e2, apx;
    int max;

    if (receber(&ex, &dex, &e1, &e2, &apx, &max)){
        cout << "Você saiu\n"; 
        return 0;
    }

    cout << "Teste\n";

    if (ex.esq == NULL) cout << "nulo esq\n";
    if (ex.dir == NULL) cout << "nulo dir\n";

    cout << "Teste\n";

    printf("Raiz de f(x): %Lf\n", ponto_fixo(e1, e2, apx, ex, dex, max));
}