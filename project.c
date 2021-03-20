/* ------------ Advanced Algorithms 2020/2021 ------------*/
/* ------------ Project 1 - String Matching --------------*/

/* Andreia Pereira  | n. 89414 */
/* Pedro Nunes      | n. 89525 */

// ---------------------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
// ---------------------------------------------------------

#define TSIZE 32
#define PSIZE 16

// ---------------------------------------------------------
void saveNewString(char *S, int *S_cap);
void increaseMemory(char* S, int *S_cap);
void decreaseMemory(char* S, int *S_cap);
void naiveMatch(char *T, char *P);
void KMPMatch(char *T, char *P);
void BMMatch(char *T, char *P);
// ---------------------------------------------------------

int main(int argc, char *argv[]){

// ---------------------------------------------------------
    // Allocate memory for T (text) string 
    char* T = malloc(TSIZE);
    if(T == NULL){
        printf("Could not allocate memory for T vector\n");
        exit(1);
    }
    int T_cap = TSIZE;
    bool checkT = false;

// ---------------------------------------------------------
    // Allocate memory for P (pattern) string 
    char* P = malloc(PSIZE);
    if(T == NULL){
        printf("Could not allocate memory for P vector\n");
        exit(1);
    }
    int P_cap = PSIZE;

// ---------------------------------------------------------
    char c;
    c = getchar();
    while ( c != 'X'){
        switch (c){
            case 'T':   // Gives new T string
                saveNewString(T, &T_cap);
                checkT = true;
                break;
            case 'N':   // Command for Naive String Matching
                if(checkT){
                    saveNewString(P, &P_cap);
                    naiveMatch(T, P);
                }
                break;
            case 'K':   // Command for KMP String Matching Algorithm
                if(checkT){
                    saveNewString(P, &P_cap);
                    
                }
                break;
            case 'B':   // Command for BM String Matching Algortihm
                if(checkT){
                    saveNewString(P, &P_cap);
                    
                }
                break;
            default:
                break;
        }
        c = getchar();
        //printf("%c", c);
    }
    
    /* TODO: Check that all memory is freed*/
    free(T);
    free(P);
    return 0;
}

void saveNewString(char *S, int *S_cap){
    char c;
    int n;
    c = getchar(); //Space char

    if (c == ' '){
        n = 0;
        c = getchar();
        while (c != '\n'){
            
            if( (n+1) == *S_cap){
                increaseMemory(S, S_cap); 
            }
            S[n] = c;
            n++;
            c = getchar();  
        }
        S[n] = '\0';  
        //printf(" %s\n", S);
    }
    else{
        printf("Bad command format\n");
    }
    
}

/*
Increases allocated memory of char* S by a factor of 2
*/
void increaseMemory(char* S, int *S_cap){

    *S_cap = *S_cap * 2;
    S = realloc(S,*S_cap);
    if(S == NULL){
        printf("Error in realloc\n");
        exit(1);
    } 
}

void decreaseMemory(char* S, int *S_cap){
    
}

void naiveMatch(char *T, char *P){
    int i = 0;                  // iterates over T
    int j = 0;                  // iterates over P
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

void KMPMatch(char *T, char *P){
// num comparações = tamanho T + #chamadas da função de falha
// se P e T acabam até ao fim, não chamar a função de falha
}

void BMMatch(char *T, char *P){

}