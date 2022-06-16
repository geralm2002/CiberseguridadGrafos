

#ifndef PP2_C_DIJSKTRA_H
#define PP2_C_DIJSKTRA_H
#include "Grafo.h"
#include <stdlib.h>
#include <stdio.h>
#define INFINITO 1.0E+38
#define T 25
int F[T];
float matPesos[T][T];
typedef struct {
    int  ultimo;
    float tiempo;
} EstadoVertice;
EstadoVertice D[T];

int minimo(int F[], EstadoVertice D[],int n);
void caminoMinimos(EstadoVertice D[], float matPesos[][T], int n);

int minimo(int F[], EstadoVertice D[], int n){
    float mx;
    int j, v;
    mx = INFINITO;
    for(j = 1; j < n; j++){
        if(!F[j] && (mx >= D[j].tiempo)){
            mx = D[j].tiempo;
            v = j;
        }
    }
    return v;
}

void caminoMinimos(EstadoVertice D[], float matPesos[][T], int n){

    int v, w, i;
    int s = 0;
    F[s] = 1;

    for(i = 1; i<n; i++){
        F[i] = 0;
        D[i].tiempo = matPesos[0][i];
        D[i].ultimo = 0;
    }
    for(i = 1; i<n; i++){
        v = minimo(F,D,n);
        F[v] = 1;
        for(w =1; w<n; w++){
            if(!F[w]){
                if((D[v].tiempo+matPesos[v][w]) < D[w].tiempo){
                    D[w].tiempo = D[v].tiempo+matPesos[v][w];
                    D[w].ultimo = v;
                }
            }
        }
    }
}
int llenarMatriz(float matPesos[][T], NodoGrafo ** pGrafo, int n){
    NodoGrafo * primero = *pGrafo;
    NodoGrafo * aux = *pGrafo;
    int i = 0, j = 0;
    while(primero !=NULL){
        Ataques * lista = primero->listaAtaques;
        aux  = *pGrafo; //reinicio
        j= 0;
        while (aux !=NULL){
            Arista * a = lista->arista;
            while(lista !=NULL){
                if(strcmp(aux->nombrePais, lista->destino)== 0){
                    matPesos[i][j]=a->tiempo;
                }else{
                    matPesos[i][j]=INFINITO;
                }
                lista = lista->siguiente;
            }

            j++;
            aux = aux->enlace;

        }
        primero = primero->enlace;
        i++;
    }
}




void iniciarDijsktra(NodoGrafo ** pgrafo, char * vertice){

    int n = getLenGrafo(*pgrafo);
    llenarMatriz(matPesos, pgrafo, n);
    caminoMinimos(D, matPesos,  n);
    for(int i = 0; i<n; i ++){
        printf("\nValores al nodo: %d", i);
        for(int j = 0; j<n; j++){
            printf("%f", matPesos[i][j]);
        }
    }

}


#endif //PP2_C_DIJSKTRA_H
