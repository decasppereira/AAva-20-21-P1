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
#define ALPHSIZE 4

/* --------------------------------------------------------- */
char* saveNewString(char *S, int *S_cap, int *S_size);
char* increaseMemory(char* S, int *S_cap);
void decreaseMemory(char* S, int *S_cap);

void naiveMatch(char *T, char *P);

void KMPMatch(char *T, char *P, int T_size, int P_size);
void buildPi_KMP(int *pi, char *P, int P_size);

void BMMatch(char *T, char *P, int T_size, int P_size);
int charPosition_BM(char c);
void buildR_BM(int *R, char* P, int P_size);
void buildL_BM(int *L, char* P, int P_size);
void buildNj_BM(int *Nj, char* P, int P_size);
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
                    BMMatch(T, P, T_size, P_size);
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
            printf("%d ", i);
        }    
        i++;
    }
    printf("\n");
}

void KMPMatch(char *T, char *P, int T_size, int P_size){
/* num comparacoes = tamanho T + #chamadas da funcao de falha
 se P e T acabam ate ao fim, nao chamar a funcao de falha*/
    
    int Pi[P_size+1];
  
    buildPi_KMP(Pi, P, P_size); /* Pre processing P to build Pi array */
   
    int q = 0;              /*Num of characters matched*/
    int i;
    int n_comp = 0;         /*Num of comparissions*/
    bool endMatch = false;
    for(i = 0; i < T_size; i++){
        while( (q > 0) && (P[q] != T[i])){ /* While mismatch*/
            q = Pi[q];
            n_comp++;
        }
        
        if( P[q] == T[i]) {
            q++;
        }
        if ( q == P_size){
            n_comp++;
            printf("%d ", i-P_size+1);
            q = Pi[q];
            if(i == T_size-1) endMatch = true;
        } 
        if(!endMatch) n_comp++;
    }
    printf("\n%d \n", n_comp);   
}

void buildPi_KMP(int *pi, char *P, int P_size){

    pi[1] = 0;

    int k = 0;
    int q;
    for (q = 1; q < P_size ; q++){
        while((k > 0) && (P[k] != P[q])){
            k = pi[k];
        }

        if(P[k] == P[q])
            k++;
        
        pi[q+1] = k;
    }
}

void buildR_BM(int *R, char* P, int P_size){
    int i = P_size -1;
    int num_chars = 0;
    int j;
    for(j = 0; j < ALPHSIZE; j++){
        R[j] = -1 ;
    }
    while((num_chars != ALPHSIZE) && (i >= 0)){
        if(R[charPosition_BM(P[i])] == -1)
            R[charPosition_BM(P[i])] = i;
        i--;
    }   
}

/*
Builds the L' array for the Boyer-Moore Algorithm
*/
void buildL_BM(int *L, char* P, int P_size){
    int Nj[P_size];
    buildNj_BM(Nj, P, P_size);
    int j;
    int i;
    for(int i = 0; i<P_size; i++){
        L[i] = 0;
    }

    for(j=0; j< P_size -1; j++){
        i = P_size - Nj[j] - 1;
        L[i] = j;
    }
     int c;
    printf("L': [");
    for (c = 0; c <P_size; c++){
        printf(" %d", L[c]);
    }
    printf(" ]\n");
}

/*
Builds the Nj array for the Boyer-Moore Algorithm
*/
void buildNj_BM(int *Nj, char* P, int P_size){
    int i = P_size - 1;
    int j;
    for(j = 0; j < P_size; j++){
        int k = j;
        int length = 0;
        while((k >= 0) && (P[k] == P[i])){
            /*printf("Here! P[%d] = %c and P[%d] = %c\n", k, P[k], i, P[i]);*/
            length++;
            k--;
            i--;
        }
        Nj[j] = length;
        i = P_size - 1;
    }
    int c;
    printf("Nj: [");
    for (c = 0; c <P_size; c++){
        printf(" %d", Nj[c]);
    }
    printf(" ]\n");
}

int charPosition_BM(char c){

    switch (c)
        {
        case 'A':
            return 0;
            break;
        case 'C':
            return 1;
            break;
        case 'G':
            return 2;
            break;
        case 'T':
            return 3;
            break;
        default: /* Should never happen*/
            return -1;
            break;
    }
}

void BMMatch(char *T, char *P, int T_size, int P_size){
    int R[ALPHSIZE];
    buildR_BM(R, P, P_size);
    int L[P_size];
    buildL_BM(L, P, P_size);
    
    
}