#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    struct no * esq;
    struct no * dir;
    char letra;
}t_no;

int i = 0;                                      //Contador da quantidade de caracteres

void preencher_arvore(t_no * raiz);
void code_to_text(t_no * raiz, char * text);


int main(void){
    char text[100];

    t_no * raiz = (t_no *)malloc(sizeof(t_no));
    raiz->letra = '-';
    preencher_arvore(raiz);


    printf("Ta aqui mesmo?");
    printf("%p", raiz->esq);
    code_to_text(raiz, text);
    for (; i >= 0; i--){
        printf("%c ", text[i]);
    }

    return 0;

}

void preencher_arvore(t_no * raiz){
    t_no * atual = (t_no *)malloc(sizeof(t_no));
    char c = 'a';
    char letra;
    FILE * pont_arq;
    pont_arq = fopen("morse.txt", "r");
    c = getc(pont_arq);
    do{
        atual = raiz;
        letra = c;
        while(c != '\n'){
            c = getc(pont_arq);
            if(c == '.'){
                if(atual->esq == NULL){
                    t_no * esq = (t_no *)malloc(sizeof(t_no));
                    atual->esq = esq;
                }
                atual = atual->esq;
            }
            else if (c == '-'){
                if(atual->dir == NULL){
                    t_no * dir = (t_no *)malloc(sizeof(t_no));
                    atual->dir = dir;
                }
                atual = atual->dir;
            }
        }
        atual->letra = letra;
        c = getc(pont_arq);
        printf("%c ", c);
        
    }while (c != EOF);
    fclose(pont_arq);
    free(atual);
}

void code_to_text(t_no * raiz, char * text){
    printf("? bugg0");
    t_no * atual2 = (t_no *)malloc(sizeof(t_no));
    atual2 = raiz;
    char c = 'a';
    FILE * pont_arq2;
    pont_arq2 = fopen("message.txt", "r");
    printf("?");
    do{
        atual2 = raiz;
        while(c != ' ' || c != '/'){
            c = getc(pont_arq2);
            printf("%c", c);
            if(c == '.'){
                atual2 = atual2->esq;
            }
            else if(c == '/'){
                atual2 = atual2->dir;
            }
        }
        text[i] = atual2->letra;
        i++;
        if (c == '/'){
            text[i] = ' ';
            i++;
        }
    }while(c != EOF);
    fclose(pont_arq2);
    free(atual2);
}