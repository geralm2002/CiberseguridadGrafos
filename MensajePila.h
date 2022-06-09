
#ifndef MPAULA_C_MENSAJE_H
#define MPAULA_C_MENSAJE_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // isalpha, isupper
#include "Grafo.h"
//=====================================================================================================================
//                                           Definción de constantes
//=====================================================================================================================
#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97
#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo
#define ROTACIONES 4 //n desplazamientos

#define TAMMENSAJE 250

const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
        *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//=====================================================================================================================
//                                           Definción de registros
//=====================================================================================================================
typedef struct NodoPila{
    struct mensaje *mensaje;
    struct nodoPila *siguiente;
}NodoPila;
typedef struct Mensaje{
    char receptor[25];
    char detalle[TAMMENSAJE];
}Mensaje;

NodoPila * tope = NULL;
//=====================================================================================================================
//                                           Definción de funciones
//=====================================================================================================================
void cifrar(char *mensaje, char *destino);
void descifrar(char *mensaje, char *destino);
int ord(char c);

void crearPila(NodoPila** pila);
void push(NodoPila** pila,Mensaje *mensaje);
void pop(NodoPila** pila);//quita el último elemento
int pilaVacia(NodoPila* pila);
Mensaje *cima(NodoPila* pila);

Mensaje* crearMensaje(char * pais, char m[TAMMENSAJE]);
//=====================================================================================================================
//                                              Funciones
//=====================================================================================================================
void crearPila(NodoPila** pila){
    *pila = NULL; //crea la pila vacía
}
void push(NodoPila** pila, Mensaje*msm){
    NodoPila* nuevo;
    nuevo = (NodoPila*) malloc(sizeof (NodoPila));
    nuevo -> mensaje = msm;
    nuevo->siguiente = *pila;
    (*pila) = nuevo;
}
void pop(NodoPila** pila){
    if(!pilaVacia(*pila)){
        NodoPila* f;
        f = *pila;
        (*pila) = (*pila)->siguiente;
        free(f);
    }
}
Mensaje* crearMensaje(char * pais, char m[TAMMENSAJE] ){
    Mensaje *nuevo;
    nuevo = (Mensaje*) malloc(sizeof(Mensaje));
    strcpy(nuevo->receptor, pais);
    strcpy(nuevo->detalle,m);
    return nuevo;
}
void cifrar(char *mensaje, char *destino) {
    /*Recorrer cadena*/
    int i = 0;
    while (mensaje[i]) {
        char caracterActual = mensaje[i];
        int posicionOriginal = ord(caracterActual);
        if (!isalpha(caracterActual)) {
            destino[i] = caracterActual;
            i++;
            continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
        }
        if (isupper(caracterActual)) {
            destino[i] =
                    alfabetoMayusculas[(posicionOriginal - INICIO_ALFABETO_MAYUSCULAS +
                                        ROTACIONES) %
                                       LONGITUD_ALFABETO];
        } else {

            destino[i] =
                    alfabetoMinusculas[(posicionOriginal - INICIO_ALFABETO_MINUSCULAS +
                                        ROTACIONES) %
                                       LONGITUD_ALFABETO];
        }
        i++;
    }
}
void descifrar(char *mensaje, char *destino) {
    /*Recorrer cadena*/
    int i = 0;
    while (mensaje[i]) {
        char caracterActual = mensaje[i];
        int posicionOriginal = ord(caracterActual);
        if (!isalpha(caracterActual)) {
            destino[i] = caracterActual;
            i++;
            continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
        }
        if (isupper(caracterActual)) {
            destino[i] = alfabetoMayusculas[MOD(
                                                    posicionOriginal - INICIO_ALFABETO_MAYUSCULAS - ROTACIONES,
                                                    LONGITUD_ALFABETO)];
        } else {
            destino[i] = alfabetoMinusculas[MOD(
                                                    posicionOriginal - INICIO_ALFABETO_MINUSCULAS - ROTACIONES,
                                                    LONGITUD_ALFABETO)];
        }
        i++;
    }
}



int ord(char c)
{
    return (int)c;
}

void Notificar(NodoPila *pila,char * paisdestino){
    char mensaje[TAMMENSAJE], mensajeCifrado[TAMMENSAJE];
    printf("Escribe el mensaje a cifrar: ");
    fgets(mensaje,TAMMENSAJE,stdin); //evita desbordamientos
    mensaje[strcspn(mensaje, "\r\n")]=0; //quita saltos de linea
    cifrar(mensaje,mensajeCifrado);
    printf("El mensaje cifrado es: %s\n", mensajeCifrado);

    Mensaje *notificacion = crearMensaje(paisdestino,mensajeCifrado);
    push(pila,notificacion);
}


int pilaVacia(NodoPila* pila)
{
    return pila==NULL;
}
Mensaje * cima(NodoPila* pila){
    if(pilaVacia(pila)){
        printf("La pila está vacía");
        exit(1);
    }else{
        return pila->mensaje;
    }
}

void consultarUltimoMensaje(NodoPila *pila){
    char descifrado[TAMMENSAJE];
    if(!pilaVacia(pila)){
        Mensaje *msm = cima(pila);
        descifrar(msm->detalle,descifrado);
        printf("País de destino: %s",msm->receptor);
        printf("Mensaje: %s",descifrado);
    }else{
        printf("Ya no hay más mensajes");
    }
}
void consultarTodoMensaje(NodoPila *pila){
    while (!pilaVacia(pila)){
        consultarUltimoMensaje(pila);
        consultarTodoMensaje(pila->siguiente);
    }
}
#endif //MPAULA_C_MENSAJE_H
