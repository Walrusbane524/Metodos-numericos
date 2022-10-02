#include <math.h>
#include <iostream>
#include <cstdio>
#include <exception>
using namespace std;

struct expr{

    expr* esq;
    char op;
    expr* dir;
    long double val;

    void iniciar(long double n){
        esq = NULL;
        dir = NULL;
        op = ' ';
        val = n;
    }

    void var(){
        esq = NULL;
        dir = NULL;
        op = 'x';
        val = 0;
    }

    void iniciar (){
        esq = NULL;
        dir = NULL;
        op = ' ';
    }

    void iniciar (expr& e, expr& d, char o){
        esq = &e;
        dir = &d;
        op = o;
    }

    long double avaliar(long double x){

       switch(op){

            case '+':
                return (esq->avaliar(x) + dir->avaliar(x));
                break;

            case '-':
                return (esq->avaliar(x) - dir->avaliar(x));
                break;

            case '/':
                return(esq->avaliar(x) / dir->avaliar(x));
                break;

            case '*':
                return (esq->avaliar(x) * dir->avaliar(x));
                break;

            case '^':
                return pow(esq->avaliar(x), dir->avaliar(x));
                break;

            case 'x':
                return x;
                break;

            default:
                return val;
       }
    }

    // Exemplo de string recebida pela função:
    // ((3) * (4)) - ((2) * (x))
    void preencher(string s, int& idx){
        for (idx; idx < s.size(); idx++){
            //cout << "s[" << idx << "] = " << s[idx] << '\n';

            switch(s[idx]){

                case '(':
                    idx++;
                    if (esq == NULL){
                        esq = new expr();
                        esq->preencher(s, idx);
                    }
                    else{
                        dir = new expr();
                        dir->preencher(s, idx);
                    }
                    break;

                case ')':
                    return;
                    break;

                case '+':
                    op = '+';
                    break;

                case '-':
                    op = '-';
                    break;

                case '*':
                    op = '*';
                    break;

                case '/':
                    op = '/';
                    break;

                case '^':
                    op = '^';
                    break;

                case 'x':
                    op = 'x';
                    break;

                case ' ':
                    continue;
                    break;

                default:
                    int x = idx;
                    while(s[x] != ' ' && s[x] != ')'){
                        //cout << "Número: s[" << x << "] = " << s[x] << '\n'; 
                        x++;
                    }    
                    val = stod(s.substr(idx, x - 1));
                    idx = x - 1;
            }
        }
        //cout << "saiu\n";
    }
};