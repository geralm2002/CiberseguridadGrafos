//
// Created by Esteb on 5/31/2022.
//

#ifndef MPAULA_C_GRAFO_H
#define MPAULA_C_GRAFO_H
#include <stdlib.h>
#include <stdio.h>
#include "Pais.h"
#include "Ciberdelincuente.h"
#include "TipoCiberataque.h"


/*=====================================================================================================================
 *                      Declaración de Registros
=====================================================================================================================*/

typedef struct NodoGrafo{
    char nombrePais[25];
    struct Grafo *enlace;
    struct Ataques *listaAtaques;
}NodoGrafo;

typedef struct Ataques{
    char  destino[25];
    struct Arista *arista;
    struct Ataque *siguiente;
}Ataques;
typedef struct Arista{

    int  idtipo;
    int   idciberdelincuente;
    int datosAfectados; //en Gigabytes
    double tiempo; //duración del ciberataque en segundos similar al peso
}Arista;
/*=====================================================================================================================
 *                      Declaración de funciones
=====================================================================================================================*/
NodoGrafo * primeroGrafo = NULL;

NodoGrafo * nuevoVertice(NodoGrafo** ngrafo, char * nombre);
NodoGrafo * obtenerVertice(NodoGrafo** pGrafo, char * nombre); //obtiene el vertice del grafo, null si no existe
NodoGrafo * insertarVertice(NodoGrafo** pGrafo, NodoGrafo* nuevo);
Arista * crearArista(int tipoDeCiberataque, int ciberdelincuente, int datos, double tiempo);
Arista * buscarArista(NodoGrafo** paisGrafo,char * origen ,char * destino); //obtiene un arista

int eliminarUnCiberAtaque(NodoGrafo ** grafo, char * origen ,char * destino);

/*=====================================================================================================================
 *                          Funciones
=====================================================================================================================*/

NodoGrafo* nuevoVertice(NodoGrafo** ngrafo,char *pais){
    NodoGrafo * nuevo;
    nuevo = (NodoGrafo*) malloc(sizeof(NodoGrafo));
    strcpy(nuevo->nombrePais, pais);
    nuevo->enlace = NULL;
    nuevo->listaAtaques = (Ataques*) malloc(sizeof(Ataques));
    nuevo->listaAtaques =NULL;
    return nuevo;
}
NodoGrafo * insertarVertice(NodoGrafo** pGrafo, NodoGrafo* nuevo){
    NodoGrafo * primero  = *pGrafo; //el primero se recorre hasta el útlimo
    if(primero == NULL){
        *pGrafo = nuevo; //será el primero
    }else{
        for(;primero->enlace;){
            primero = primero->enlace;//recorre hasta que llegue al ultimo
        }
        primero->enlace = nuevo; //se asigna una vez que llegue al final
    }
}
NodoGrafo * obtenerVertice(NodoGrafo** primero, char * nombre){ //obtiene un nodo en el grafo
    NodoGrafo * recorrido = *primero;
    for(; recorrido->enlace;){
        if(strcmp(recorrido->nombrePais, nombre)){
            return recorrido;
        }else{
            recorrido = recorrido->enlace;
        }
    }
    return NULL;
}
Arista * crearArista(int tipoDeCiberataque, int ciberdelincuente, int datos, double tiempo){
    Arista* nuevaArista;
    nuevaArista = (Arista*) malloc(sizeof (Arista));
    nuevaArista->idciberdelincuente = ciberdelincuente;
    nuevaArista->idtipo = tipoDeCiberataque;
    nuevaArista->tiempo  = tiempo;
    nuevaArista->datosAfectados = datos;
    return nuevaArista;
}
Arista * buscarArista(NodoGrafo** paisGrafo,char * origen ,char * destino){ //obtiene la arista
    //El parámetro de los datos es necesario para especificar el ciber ataque a buscar
    NodoGrafo * nodoGrafo = obtenerVertice(paisGrafo, origen);
    Ataques * ataque = nodoGrafo->listaAtaques;
    Arista * arista;
    for(;ataque->siguiente;){
        if(strcmp(ataque->destino, destino)){
            return arista;
        }
        ataque = ataque->siguiente;
    }
    return NULL; //retorna null si no existe
}
Ataques * buscarAtaque(NodoGrafo* procedenteGrafo, char *destino){
    NodoGrafo * pais = procedenteGrafo;
    Ataques * primero  = pais->listaAtaques;
    for (; primero->siguiente;){
        if(strcmp(primero->destino, destino)){
            return primero;
        }
        primero = primero->siguiente;
    }
    return NULL;
}
void agregarAtaque(NodoGrafo * procedente, Ataques * ataque){

    Ataques * primero = procedente->listaAtaques;
    if(primero == NULL){
        primero = ataque;
    }else {
        Ataques *ultimo;
        for (; primero->siguiente;) {
            primero = primero->siguiente;
        }
        ultimo = primero;
        ultimo->siguiente = ataque;
    }
}
Ataques * crearAtaque(NodoGrafo * procedente, char * destino, TipoDeCiberataque * lTipos, Ciberdelincuente * lDelicuentes){
    Ataques * nuevoAtaque;
    nuevoAtaque = (Ataques*) malloc(sizeof (Ataques));
    nuevoAtaque->destino;
    int tipo, idCiberDelincuente,datos;
    double tiempo;
    do {

        printf("Ingrese el tipo del ciberataque: ");
        scanf("%d", &tipo);

    }while(tipoExiste(lTipos, &tipo));
    do {

        printf("Ingrese el id del delincuente: ");
        scanf("%d", &idCiberDelincuente);

    }while(tipoExiste(lTipos, &tipo));

    printf("Ingrese el tiempo que duró el ciber ataque: ");
    scanf("%lf", &tiempo);
    printf("Ingrese la cantidad de datos que fueron afectados ");
    scanf("%d", &datos);
    Arista * arista = crearArista(tipo,idCiberDelincuente, datos, tiempo);
    nuevoAtaque->arista = arista;
    agregarAtaque(procedente, nuevoAtaque);
}








int realizarAtaque(NodoGrafo** pGrafo,Pais* procedente, Pais * destino,
                   TipoDeCiberataque * tipo, Ciberdelincuente* delincuente, double tiempo, int datos){
    NodoGrafo * nodoProcedente = obtenerVertice(pGrafo, procedente->nombre);
    char * nombDestino = destino->nombre;
    Ataques * ataque;
    ataque = buscarAtaque(nodoProcedente, procedente->nombre);
    if(ataque==NULL){
        //crear el ataque para agregarlo

    }


}

//obtiene el vertice según el codigo, devuleve null en caso de no encontrarlo
int eliminarAtaquesPorPais(NodoGrafo* pais){
    Ataques * ataques = pais->listaAtaques;
    Ataques * aux = ataques;
    for(;ataques->siguiente;){
        aux = ataques;
        ataques = ataques->siguiente;
        free(aux);
    }
    pais->listaAtaques = NULL;
}
int eliminarUnCiberAtaque(NodoGrafo ** grafo, char * origen ,char * destino){
    /*los datos afectados hacen más específica la búsqueda ya que un país podría tener varios ataques desde un mismo país
     * desde un mismo ciberdelincuente, del mismo tipo de ciber ataque también*/
    NodoGrafo * procedente = obtenerVertice(grafo, origen);
    if(procedente==NULL){
        return 0;
    }
    NodoGrafo * encontrado  = buscarAtaque(procedente,  destino);
    //para saber si el ataque que deseamos eliminar existe
    Ataques * actual;
    Ataques * anterior;
    if(encontrado!= NULL){
        actual = encontrado->listaAtaques;
        anterior= NULL;
        actual = actual->siguiente;
        /*Enlace del nodo anterior con siguiente*/
        if (actual!=NULL){
            if(actual == encontrado->listaAtaques){//distingue entre el nodo cabecera o el resto de la lista
                encontrado->listaAtaques = actual->siguiente;
            }else{
                anterior ->siguiente = actual->siguiente;
            }
            return 1;
        }
        free(actual);
    }
    return 0;
}




#endif //MPAULA_C_GRAFO_H
