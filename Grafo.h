//
// Created by Esteb on 5/31/2022.
//

#ifndef MPAULA_C_GRAFO_H
#define MPAULA_C_GRAFO_H
#include "Pais.h"
#include "Ciberdelincuente.h"
#include "TipoCiberataque.h"

typedef struct NodoPais NodoPais;

struct Grafo{
    struct NodoPais *nodoPais;
    struct Grafo *siguiente;
    struct Ataques *listaAtaques;
};

struct NodoPais{ //País tiene Izquierda y derecha, entonces este nodo solo tiene país
    int codigo;
    char nombre[25];
    int habitantes;
    char continente[25];
};
struct Ataques{
    struct NodoPais *destino;
    struct Arista *arista;
    struct Ataques *siguiente;
};
struct Arista{

    struct TipoDeCiberataque *ciberataque;
    struct  Ciberdelincuente  *ciberdelincuente;
    int datosAfectados; //en Gigabytes
    int tiempo; //duración del ciberataque en segundos similar al peso
};

#endif //MPAULA_C_GRAFO_H
