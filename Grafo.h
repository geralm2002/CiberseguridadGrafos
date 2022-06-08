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
    struct NodoPais *nodoPais;
    struct Grafo *enlace;
    struct Ataque *listaAtaques;
}NodoGrafo;

typedef struct NodoPais{ //País tiene Izquierda y derecha, entonces este nodo solo tiene país
    int codigo;
    char nombre[25];
    char continente[25];
}NodoPais;
typedef struct Ataque{
    struct NodoPais *destino;
    struct Arista *arista;
    struct Ataque *siguiente;
}Ataque;
typedef struct Arista{

    struct TipoDeCiberataque *ciberataque;
    struct  Ciberdelincuente  *ciberdelincuente;
    int datosAfectados; //en Gigabytes
    double tiempo; //duración del ciberataque en segundos similar al peso
}Arista;
/*=====================================================================================================================
 *                      Declaración de funciones
=====================================================================================================================*/
NodoGrafo* nuevoVertice(NodoGrafo** ngrafo, NodoPais* pais);
int grafoVacio(NodoGrafo * pGrafo);
NodoPais * construirNodoPais(Pais * pais);
NodoGrafo* obtenerVertice(NodoGrafo* pGrafo, int codigo);
Ataque* atacarA(NodoPais** destino, Ataque** lista, Arista* arista);
Arista * crearArista(TipoDeCiberataque* tipoDeCiberataque, Ciberdelincuente * ciberdelincuente, int datos, double tiempo);
NodoPais * buscarCiberAtaque(NodoGrafo** paisGrafo, NodoPais* destino, int datos);
/*=====================================================================================================================
 *                          Funciones
=====================================================================================================================*/

NodoGrafo* nuevoVertice(NodoGrafo** ngrafo,NodoPais *pais){
    NodoGrafo * nuevo;
    nuevo = (NodoGrafo*) malloc(sizeof(NodoGrafo));
    nuevo->nodoPais = pais;
    nuevo->enlace = ngrafo;
    nuevo->listaAtaques = (Ataque*) malloc(sizeof(Ataque));
    nuevo->listaAtaques =NULL;
    return nuevo;
}
int realizarAtaque(NodoGrafo** pGrafo,Pais* procedente, Pais * destino,
                   TipoDeCiberataque * tipo, Ciberdelincuente* delincuente, double tiempo, int datos){
    NodoPais * nodoPaisProcedente;
    NodoPais * nodoPaisDestino;
    NodoGrafo * unPaisEnGrafo = obtenerVertice(pGrafo, procedente->codigo);
    NodoGrafo * otroPaisEnGrafo = obtenerVertice(pGrafo, destino->codigo);
    NodoGrafo * nodoGrafo;
    if(unPaisEnGrafo == NULL){
        printf("\nEl país procedente no se encuentra en el grafo, se agregará un nuevo nodo\n");
        nodoPaisProcedente = construirNodoPais(procedente);
        nodoGrafo = nuevoVertice(pGrafo,nodoPaisProcedente);
    }else{
        printf("\nPaís encontrado, se agregará una nueva arista\n");
        nodoGrafo = unPaisEnGrafo;
    }
    if(otroPaisEnGrafo== NULL){
        printf("\nEl país de destino no se encuentra en el grafo, se agregará un nuevo nodo\n");
        nodoPaisDestino = construirNodoPais(destino);
        nodoPaisDestino = nuevoVertice(pGrafo, nodoPaisDestino);
    }else{
        nodoPaisDestino = nodoPaisProcedente;

    }
    Arista * arista = crearArista(tipo, delincuente, datos, tiempo);
    nodoGrafo->listaAtaques = atacarA(nodoPaisDestino, nodoGrafo->listaAtaques,arista );


}
Ataque* atacarA(NodoPais** destino, Ataque** lista, Arista* arista){
    Ataque * nuevoAtaque;
    nuevoAtaque->destino = destino;
    nuevoAtaque->arista = arista;
    nuevoAtaque->siguiente = lista;// el enlace
    return nuevoAtaque;

}
Arista * crearArista(TipoDeCiberataque* tipoDeCiberataque, Ciberdelincuente * ciberdelincuente, int datos, double tiempo){
    Arista* nuevaArista;
    nuevaArista = (Arista*) malloc(sizeof (Arista));
    nuevaArista->ciberdelincuente = ciberdelincuente;
    nuevaArista->ciberataque = tipoDeCiberataque;
    nuevaArista->tiempo  = tiempo;
   nuevaArista->datosAfectados = datos;
   return nuevaArista;
}


NodoPais * construirNodoPais(Pais * pais){ //copia algunos valores del país a el nodo pais del grafo
    NodoPais * nuevo = (NodoPais*) malloc(sizeof(NodoPais));
    strcpy(nuevo->nombre,pais->nombre ); //copia la cadena
    nuevo->codigo = pais->codigo; // agarra la referencia del código
    strcpy(nuevo->continente,  pais->continente);
    return nuevo; // lo devuelve
}
//obtiene el vertice según el codigo, devuleve null en caso de no encontrarlo
NodoGrafo* obtenerVertice(NodoGrafo* pGrafo, int codigo){
    NodoPais * nodo  = pGrafo->nodoPais;
    while (!grafoVacio(pGrafo)){ //mientras el grafo no sea vacío
        if(nodo->codigo== codigo){
            return pGrafo; //retorna el nodo del grafo si tiene el mismo código
        }else{
            pGrafo = pGrafo->enlace;
        }
    }
    return NULL;
}

int grafoVacio(NodoGrafo* pgrafo){
    return pgrafo==NULL;
}
void eliminarUnCiberAtaque(NodoGrafo** paisGrafo,NodoPais* destino, int datos){
    /*los datos afectados hacen más específica la búsqueda ya que un país podría tener varios ataques desde un mismo país
     * desde un mismo ciberdelincuente, del mismo tipo de ciber ataque también*/
    NodoGrafo * encontrado  = buscarCiberAtaque(paisGrafo, destino,datos);
    //para saber si el ataque que deseamos eliminar existe
    Ataque * actual;
    Ataque * anterior;

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
        }
        free(actual);
    }
}
NodoPais * buscarCiberAtaque(NodoGrafo** paisGrafo, NodoPais * destino, int datos){
    //El parámetro de los datos es necesario para especificar el ciber ataque a buscar
    NodoGrafo * unNodo = *paisGrafo;
    Ataque * indice;
    for(indice = unNodo->listaAtaques; indice != NULL; indice = indice->siguiente){
        if(destino->codigo == indice->destino->codigo && datos == indice->arista->datosAfectados){
            return unNodo;
        }
    }
    return NULL;

}



#endif //MPAULA_C_GRAFO_H
