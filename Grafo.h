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
    struct Ataques * listaAtaques;
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
    float tiempo; //duración del ciberataque en segundos similar al peso
}Arista;
//VARIABLE INICIALIZADORA DEL GRAFO





/*=====================================================================================================================
 *                      Declaración de funciones
=====================================================================================================================*/


NodoGrafo * nuevoVertice(NodoGrafo** ngrafo, char * nombre);
NodoGrafo * obtenerVertice(NodoGrafo* pGrafo, char * nombre); //obtiene el vertice del grafo, null si no existe
void insertarVertice(NodoGrafo** pGrafo, NodoGrafo* nuevo);
Arista * crearArista(int tipoDeCiberataque, int ciberdelincuente, int datos, float tiempo);
Arista * buscarArista(NodoGrafo** paisGrafo,char * origen ,char * destino); //obtiene un arista
int modficarCiberAtaque(NodoGrafo ** primero);
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
void insertarVertice(NodoGrafo** pGrafo, NodoGrafo* nuevo){
    nuevo->enlace = *pGrafo;
    *pGrafo = nuevo;
}
NodoGrafo * obtenerVertice(NodoGrafo* primero, char * nombre){ //obtiene un nodo en el grafo
    if(primero == NULL){
        return NULL;
    }
    NodoGrafo * recorrido = primero;
    while(recorrido!=NULL){
        int rescmp=strcmp(recorrido->nombrePais, nombre);
        if(rescmp==0)
            return recorrido;
        else
            recorrido = recorrido->enlace;
    }
    return NULL;
}
Arista * crearArista(int tipoDeCiberataque, int ciberdelincuente, int datos, float tiempo){
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
    if(nodoGrafo!=NULL){
        Ataques * ataque = nodoGrafo->listaAtaques;
        Arista * arista;
        while (ataque!=NULL){
            if(strcmp(ataque->destino, destino)==0){
                return arista;
            }
            ataque = ataque->siguiente;
        }
    }
    return NULL; //retorna null si no existe
}
Ataques * buscarAtaque(NodoGrafo* procedenteGrafo, char *destino){
    NodoGrafo * pais = procedenteGrafo;
    Ataques * primero  = pais->listaAtaques;
    while (primero!=NULL){
        if(strcmp(primero->destino, destino)==0)
            return primero;
        primero = primero->siguiente;
    }
    return NULL;
}
void agregarAtaque(NodoGrafo * procedente, Ataques * ataque){
    ataque->siguiente = procedente ->listaAtaques;
    procedente->listaAtaques = ataque;
}
Ataques * crearAtaque(char * destino, TipoDeCiberataque * tipo, Ciberdelincuente * delicuente,
                      float tiempo, int datos){
    Ataques * nuevoAtaque;
    nuevoAtaque = (Ataques*) malloc(sizeof (Ataques));
    strcpy(nuevoAtaque->destino, destino);
    Arista * arista = crearArista(tipo->codigo,delicuente->id, datos, tiempo);
    nuevoAtaque->arista = arista;
    return nuevoAtaque;
}


int realizarAtaque(NodoGrafo** pGrafo,Pais* procedente, Pais * destino,
                   TipoDeCiberataque * tipo, Ciberdelincuente* delincuente, float tiempo, int datos){
    NodoGrafo * nodoProcedente = obtenerVertice(*pGrafo, procedente->nombre);
    if(nodoProcedente ==NULL){ //en caso de que no exista deberá crear el vertice
        nodoProcedente = nuevoVertice(pGrafo, procedente->nombre); //lo crea
        insertarVertice(pGrafo,nodoProcedente); //inserta el nuevo en el grafo
        printf("\nNuevo nodo insertado\n");
    }else{
        printf("\nEl nodo ya está en el grafo\n");
    }
    NodoGrafo * nodoDestino = obtenerVertice(*pGrafo, destino->nombre); //el ataque guarda el nombre del destino, no el nodo, aún así debemos verificar que esté en el grafo
    if(nodoDestino == NULL){
        nodoDestino = nuevoVertice(pGrafo, destino->nombre);
        insertarVertice(pGrafo,nodoDestino);
        printf("\nNuevo nodo insertado\n");
    }else{
        printf("\nEl nodo ya esta en el grafo\n");
    };


    Ataques * ataque;
    ataque = buscarAtaque(nodoProcedente, destino->nombre);
    if(ataque==NULL){
        ataque = crearAtaque(destino->nombre, tipo, delincuente, tiempo, datos);
        agregarAtaque(nodoProcedente, ataque);

        printf("\n¡Ataque registrado exitosamente!\n");
    }else{
        printf("\n->El ataque ya existe en el registro<-\n");
        printf("\n== Nombre del país atacado: %s", destino->nombre);
        printf("\n== id ciberlincuente: %d", ataque->arista->idciberdelincuente);
        printf("\n== id tipo del ciberataque: %d", ataque->arista->idtipo);
        printf("\n== Cantidad de datos afectados: %d", ataque->arista->datosAfectados);
        printf("\n== Tiempo de duración: %f", ataque->arista->tiempo);
        printf("\n->Si desea modificarlo deberá ingresar a la opción de modificar ciberataques-\n");
    }
}

//obtiene el vertice según el codigo, devuleve null en caso de no encontrarlo
int eliminarAtaquesPorPais(NodoGrafo* pais){
    Ataques * ataques = pais->listaAtaques;
    Ataques * aux = ataques;
    while (ataques!=NULL){
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

void consultarGrafo(NodoGrafo * pNodoGrafo){
    NodoGrafo * primero = pNodoGrafo;
    Ataques * ataquesXnodo; //ataques por cada nodo del grafo
    Arista * arista;
    printf("\n--------Informacion del grafo-------\n");
    while(primero!=NULL){
        ataquesXnodo = primero->listaAtaques;
        if(ataquesXnodo==NULL){
            printf("%s no hizo ningun ataque \n", primero->nombrePais);
        }else{
            printf("%s ataco a: ", primero->nombrePais);
            while(ataquesXnodo !=NULL){
                printf("\n--> %s ",ataquesXnodo->destino);
                arista = ataquesXnodo->arista;
                printf("\n\t\t ID del ciberdelincuente: %d", arista->idciberdelincuente);
                printf("\n\t\t ID del tipo del ciber ataque: %d", arista->idtipo);
                printf("\n\t\t Cantidad de datos afectados: %d", arista->datosAfectados);
                printf("\n\t\t Tiempo de duracion del ciberAtaque: %f", arista->tiempo);
                ataquesXnodo = ataquesXnodo->siguiente;
            }
        }
        primero = primero->enlace;
    }
}
int modficarCiberAtaque(NodoGrafo ** primero){
    char paisProcedente[25], paisDestino[25];
    printf("\nIngrese eñ país que realiza el ciberAtaque: ");
    scanf("%s", &paisProcedente);
    printf("\nIngrese el pais atacado: ");
    scanf("%s", &paisDestino);
    Arista * arista = buscarArista(primero, paisProcedente, paisDestino);
    TipoDeCiberataque * ciberataque;
    Ciberdelincuente *  ciberdelincuente;
    if(arista!=NULL){
        int idciberataque, idciberdelincuente, datosAfectados;
        float tiempo;
        do{
            printf("\n->Inserte el id del tipo de ciberataque: ");
            scanf("%d", &idciberataque);
            ciberataque = obtenerTipoCiberataque(idciberataque);
            if(ciberataque==NULL){
                printf("El tipo del ciberataque no se encuentra registrado\n");
            }
        } while (ciberataque ==NULL);
        //Obtener ciberdelincuente
        do{
            printf("\n->Inserte el ciberdelincuente: ");
            scanf("%d", &idciberdelincuente);
            ciberdelincuente = obtenerCiberdelicuente(idciberdelincuente);
            if(ciberdelincuente==NULL)
                printf("Por favor ingrese un ciberdelincuente registrado\n");
        } while (ciberdelincuente== NULL);
        printf("\nInserte la cantidad de datos afectados en gigabytes: ");
        scanf("%d", &datosAfectados);
        printf("\nInserte el tiempo de duración: ");
        scanf("%f", &tiempo);
        //modifico valores
        arista->idtipo = idciberataque;
        arista->idciberdelincuente = idciberdelincuente;
        arista->datosAfectados = datosAfectados;
        arista->tiempo = tiempo;
        printf("Datos actualizados exitosamente! ");
        return 1;
    }else{
        printf("El ataque no se encuentra registrado");
    }
    return 0;
}


#endif //MPAULA_C_GRAFO_H
