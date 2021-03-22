/* ------------ Advanced Algorithms 2020/2021 ------------*/
/* ------------ Project 1 - String Matching --------------*/

/* Andreia Pereira  | n. 89414 */
/* Pedro Nunes      | n. 89525 */

/* --------------------------------------------------------- */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
/* --------------------------------------------------------- */

#define TSIZE 32
#define PSIZE 16

/* --------------------------------------------------------- */
char* saveNewString(char *S, int *S_cap, int *S_size);
char* increaseMemory(char* S, int *S_cap);
void buildPi(int *pi, char *P, int P_size);
void decreaseMemory(char* S, int *S_cap);
void naiveMatch(char *T, char *P);
void KMPMatch(char *T, char *P, int T_size, int P_size);
void BMMatch(char *T, char *P);
/* --------------------------------------------------------- */

int main(int argc, char *argv[]){

/* --------------------------------------------------------- */
    /* Allocate memory for T (text) string */
    char* T = malloc(TSIZE);
    if(T == NULL){
        printf("Could not allocate memory for T vector\n");
        exit(1);
    }
    int T_cap = TSIZE;
    int T_size = 0;
    bool checkT = false;

/* --------------------------------------------------------- */
    /* Allocate memory for P (pattern) string */
    char* P = malloc(PSIZE);
    if(T == NULL){
        printf("Could not allocate memory for P vector\n");
        exit(1);
    }
    int P_size = 0;
    int P_cap = PSIZE;

/* --------------------------------------------------------- */
    char c;
    c = getchar();
    while ( c != 'X'){
        switch (c){
            case 'T':   /* Gives new T string*/
                T = saveNewString(T, &T_cap, &T_size);
                checkT = true;
                break;
            case 'N':   /*Command for Naive String Matching*/
                if(checkT){
                    P = saveNewString(P, &P_cap, &P_size);
                    naiveMatch(T, P);
                }
                break;
            case 'K':   /* Command for KMP String Matching Algorithm */
                if(checkT){
                    P = saveNewString(P, &P_cap, &P_size);
                    
                    KMPMatch(T, P, T_size, P_size);
                }
                break;
            case 'B':   /* Command for BM String Matching Algortihm */
                if(checkT){
                    P = saveNewString(P, &P_cap, &P_size);
                    
                }
                break;
            default:
                break;
        }
        c = getchar();
    }
    
    /* TODO: Check that all memory is freed*/
    free(T);
    free(P);
    return 0;
}

char* saveNewString(char *S, int *S_cap, int *S_size){
    char c;
    int n;
    c = getchar(); /*Space char*/

    if (c == ' '){
        n = 0;
        c = getchar();
        while (c != '\n'){
            if( (n+1) == *S_cap){
                S = increaseMemory(S, S_cap);
            }
            S[n] = c;
            n++;
            c = getchar();  
        }
        S[n] = '\0';
        *S_size = n;  
    }
    else{
        printf("Bad command format\n");
    }
    return S;
}

/*
Increases allocated memory of char* S by a factor of 2
*/
char* increaseMemory(char* S, int *S_cap){

    *S_cap = *S_cap * 2;
    S = realloc(S,*S_cap);
    if(S == NULL){
        printf("Error in realloc\n");
        exit(1);
    } 

    return S;
}

void decreaseMemory(char* S, int *S_cap){
    
}

void naiveMatch(char *T, char *P){
    int i = 0;                  /* iterates over T */
    int j = 0;                  /* iterates over P */
    char p = P[0];
    bool match = true;
    bool alreadyMatched = false;

    while (T[i] != '\0'){
        j = 0;
        p = P[0];
        while( p != '\0'){
            if(T[i+j] != p){
                match = false;
                break;
            }
            j++;
            p = P[j];
        }
        if((p == '\0') && (match == true)){
            if(alreadyMatched)
                printf(" ");
            else
                alreadyMatched = true;
            printf("%d", i);
        }    
        i++;
    }
    printf("\n");
}

void KMPMatch(char *T, char *P, int T_size, int P_size){
/* num comparacoes = tamanho T + #chamadas da função de falha
 se P e T acabam ate ao fim, nao chamar a funcao de falha*/
    
    int Pi[P_size+1];
  
    buildPi(Pi, P, P_size); /* Pre processing P to build Pi array */
   
    int q = 0;              /*Num of characters matched*/
    int i;
    int n_comp = T_size+1;         /*Num of comparissions*/    
    bool alreadyMatched = false;

    for(i = 0; i < T_size; i++){
        while( (q > 0) && (P[q] != T[i])){ /* While mismatch*/
            q = Pi[q];
            n_comp++;
        }
        
        if( P[q] == T[i]) {
            q++;
        }
        if ( q == P_size){
            if(alreadyMatched)
                printf(" %d", i-P_size+1);
            else{
                printf("%d", i-P_size+1);
                alreadyMatched = true;
            }
            q = Pi[q];
        } 
    }
    printf("\n%d \n", n_comp);
    
}

void buildPi(int *pi, char *P, int P_size){

    pi[1] = 0;

    int k = 0;
    int q;
    for (q = 2; q <= P_size ; q++){
        while((k > 0) && (P[k + 1] != P[q])){
            k = pi[k];
        }

        if(P[k + 1] == P[q])
            k++;

        pi[q] = k;
    }
}

void BMMatch(char *T, char *P){

}