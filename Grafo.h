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
int getLenGrafo(NodoGrafo* ngrafo){
    NodoGrafo * primero = ngrafo;
    int cant = 0 ;
    while(primero !=NULL){
        cant++;
        primero = primero->enlace;
    }
    return cant;
}
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
    (*pGrafo) = nuevo;
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


NodoGrafo * realizarAtaque(NodoGrafo** pGrafo,Pais* procedente, Pais * destino,
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
        (*pGrafo) = nodoProcedente;
        return nodoProcedente;
    }else{
        printf("\n->El ataque ya existe en el registro<-\n");
        printf("\n== Nombre del país atacado: %s", destino->nombre);
        printf("\n== id ciberlincuente: %d", ataque->arista->idciberdelincuente);
        printf("\n== id tipo del ciberataque: %d", ataque->arista->idtipo);
        printf("\n== Cantidad de datos afectados: %d", ataque->arista->datosAfectados);
        printf("\n== Tiempo de duración: %f", ataque->arista->tiempo);
        printf("\n->Si desea modificarlo deberá ingresar a la opción de modificar ciberataques-\n");
        return NULL;
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
int eliminarUnCiberAtaque(NodoGrafo ** grafo, char * origen ,char * destino) {
    /*los datos afectados hacen más específica la búsqueda ya que un país podría tener varios ataques desde un mismo país
     * desde un mismo ciberdelincuente, del mismo tipo de ciber ataque también*/
    NodoGrafo *vertice = obtenerVertice(grafo, origen);
    if (vertice != NULL) {
        Ataques *ady = vertice->listaAtaques;
        Ataques *ant = NULL;
        while (ady) {
            if (strcmp(ady->destino, destino) == 0) {
                if (ant == NULL) { //anterior nulo
                    vertice->listaAtaques = ady->siguiente;
                } else {
                    ant->siguiente = ady->siguiente;
                }
                free(ady);
                ady = NULL;
                return 1;
            } else {
                ant = ady;
                ady = ady->siguiente;
            }

        }
    }else{

        return 0;
    }



    //para saber si el ataque que deseamos eliminar existe


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
    int idProcedente, idDestino;
    NodoGrafo * paisProcedente, * paisDestino;
    do {
        printf("\nIngrese el id pais que realizo el ciberAtaque: ");
        scanf("%d", &idProcedente);
        paisProcedente = obtenerPais(raiz, idProcedente);
        if(paisProcedente == NULL){
            printf("El pais no se encuentra registrado");
        }
    }while(paisProcedente== NULL);

    do{
        printf("\nIngrese el pais que recibio el ataque: ");
        scanf("%d", &idDestino);
        paisDestino = obtenerPais(raiz, idDestino);
        if(paisDestino==NULL){
            printf("El país de destino no esta registado");
        }
    } while (paisDestino== NULL);

    Arista * arista = buscarArista(primero, paisProcedente->nombrePais, paisDestino->nombrePais);
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
int cantidadtotalCiberAtaques(NodoGrafo ** pgrafo){
    NodoGrafo * unNodo = *pgrafo;
    Ataques  * listaAtaques = NULL;
    int cantidadTotal = 0;
    while (unNodo){
        listaAtaques = unNodo->listaAtaques;
        while (listaAtaques !=NULL){
            cantidadTotal++;
            listaAtaques = listaAtaques ->siguiente;
        }
        unNodo = unNodo->enlace;
    }
    return cantidadTotal;
}
void cantidadEnviadosRecibidosXpais(NodoGrafo ** pgrafo){
    NodoGrafo * unNodo = *pgrafo;
    NodoGrafo * otroNodo;
    Ataques  * listaAtaques;
    int totalEnviados = 0;
    int totalRecibidos = 0;
    while (unNodo !=NULL){
        otroNodo = *pgrafo;
        totalEnviados = 0;
        totalRecibidos = 0;
        while (otroNodo != NULL){
            listaAtaques = otroNodo->listaAtaques;
            while (listaAtaques !=NULL){
                if(strcmp(unNodo->nombrePais, listaAtaques->destino)==0){
                    totalRecibidos++;
                }
                if(strcmp(otroNodo->nombrePais, unNodo->nombrePais)==0){
                    totalEnviados++;
                }
                listaAtaques = listaAtaques->siguiente;
            }

            otroNodo = otroNodo->enlace;
        }
        printf("-> %s envio un total de %d ciberataques. \n", unNodo->nombrePais, totalEnviados);
        printf("-> %s recibio un total de %d ciberataques.\n", unNodo->nombrePais, totalRecibidos );
        printf("-------------------------------------------------------------");
        unNodo = unNodo->enlace;
    }
}
void cantidadPorTipoCiberataque(NodoGrafo **pgrafo){
    NodoGrafo * unNodo = * pgrafo;
    TipoDeCiberataque * lista = listaTC;
    Ataques * listaAtaques;
    int cantidad =0;
    while (lista !=NULL){
        cantidad = 0;
        while (unNodo !=NULL){
            listaAtaques = unNodo->listaAtaques;
            while (listaAtaques!=NULL){
                if(listaAtaques->arista->idtipo == lista->codigo){
                    cantidad++;
                }
                listaAtaques = listaAtaques->siguiente;
            }
            unNodo = unNodo->enlace;
        }
        lista = lista->siguiente;
        printf("La cantidad de ciberataques enviados/recibidos por el tipo de ciberataque %s  es: %d", lista->nombre, cantidad);
    }

}
void cantidadPorCiberDelincuente(NodoGrafo ** pGrafo){
    NodoGrafo * unNodo = *pGrafo;
    Ciberdelincuente * lista = listaCD;
    Ataques * listaAtaques;
    int cantidad = 0;
    while (lista !=NULL){
        cantidad = 0;
        while(unNodo != NULL){
            listaAtaques = unNodo->listaAtaques;
            while (listaAtaques !=NULL){
                if(listaAtaques->arista->idciberdelincuente == lista->id){
                    cantidad++;
                }
                listaAtaques = unNodo->listaAtaques;
            }
            unNodo = unNodo->enlace;
        }
        printf("El ciberdelincuente %d ha hecho %d ataques\n" ,lista->id, cantidad);
        lista = lista->siguiente;
    }
}
int getCantidadDeUnPais(NodoGrafo ** pGrafo, char * nombre){
    NodoGrafo * primero = *pGrafo;
    int cantidad = 0;
    while (primero != NULL){
        Ataques * lista = primero->listaAtaques;
        while (lista !=NULL){
            if(strcmp(lista->destino, nombre)== 0){
                cantidad++;
            }
            lista = lista->siguiente;
        }
        primero = primero->enlace;
    }
    return cantidad;
}
int getCantidadPorCiberDelincuente(NodoGrafo** pGrafo, int id){
    NodoGrafo  * primero = *pGrafo;
    int cantidad = 0;
    while(primero !=NULL){
        Ataques * lista = primero->listaAtaques;
        while (lista !=NULL){
            if(lista->arista->idciberdelincuente == id ){
                cantidad++;
            }
            lista = lista->siguiente;
        }
        primero = primero->enlace;
    }
    return cantidad;
}

void intercambiarNum(int *a, int *b) {
    int temporal = *a;
    *a = *b;
    *b = temporal;
}
void intercambiarChar(char * a, char * b){
    char temporal = *a;
    *a = *b;
    *b  = temporal;
}
void burbujaPaises(int arreglo[], char * arrN, int longitud) {
    for (int x = 0; x < longitud; x++) {
        for (int indiceActual = 0; indiceActual < longitud - 1;indiceActual++) {
            int indiceSiguienteElemento = indiceActual + 1;
            // Si el actual es mayor que el que le sigue a la derecha...
            if (arreglo[indiceActual] > arreglo[indiceSiguienteElemento]) {
                // ...intercambiarlos, es decir, mover el actual a la derecha y el de la derecha al actual
                intercambiarNum(&arreglo[indiceActual], &arreglo[indiceSiguienteElemento]);
                intercambiarChar( &arrN[indiceActual], &arrN[indiceSiguienteElemento]);

            }
        }
    }
}
void burbujaCiberdelincuentes(int arreglo[], int arrN[], int longitud) {
    for (int x = 0; x < longitud; x++) {
        for (int indiceActual = 0; indiceActual < longitud - 1;indiceActual++) {
            int indiceSiguienteElemento = indiceActual + 1;
            // Si el actual es mayor que el que le sigue a la derecha...
            if (arreglo[indiceActual] > arreglo[indiceSiguienteElemento]) {
                // ...intercambiarlos, es decir, mover el actual a la derecha y el de la derecha al actual
                intercambiarNum(&arreglo[indiceActual], &arreglo[indiceSiguienteElemento]);
                intercambiarNum( &arrN[indiceActual], &arrN[indiceSiguienteElemento]);
            }
        }
    }
}
void topTresPaisesAtacados(NodoGrafo ** pgrafo){
    NodoGrafo * primero = *pgrafo;
    int lenGrafo = getLenGrafo(*pgrafo);
    int cantidadXpais[lenGrafo]; //para ordenar la lista de mayor a menor
    char topList[lenGrafo][25];

    int i = 0;
    int ataques = 0;
    while (primero !=NULL){
        ataques = getCantidadDeUnPais(pgrafo, primero->nombrePais);
        strcpy(topList[i], primero->nombrePais);
        cantidadXpais[i] = ataques;
        i++;
        primero = primero -> enlace;
    }
    burbujaPaises(cantidadXpais, topList, lenGrafo);
    printf("Los top tres paises mas atacados son: \n");
    for (int j = 0 ; i < 3; i++){ //imprime del 1 al tres
        printf("%d . %s \n", i, topList[i]);
    }
}
void topTresCiberDelincuentes(NodoGrafo ** pGrafo){
    NodoGrafo * primero = *pGrafo;
    Ciberdelincuente * ciberDlist = listaCD;
    int lenLista = getTamannoCiberdelincuente();
    int listaCantidad[lenLista];
    int listaid[lenLista]; //ambas son paralelas
    int i = 0;
    while(ciberDlist !=NULL){
        primero = * pGrafo;
        while (primero !=NULL){
            listaCantidad[i]=  getCantidadPorCiberDelincuente(pGrafo, ciberDlist->id);
            listaid[i] = ciberDlist->id;
            primero = primero ->enlace;
        }
        ciberDlist = ciberDlist->siguiente;
    }
    burbujaCiberdelincuentes(listaCantidad, listaid, lenLista);
    printf("Los top tres ciberdelincuentes: \n");
    for (int j = 0 ; i < 3; i++){ //imprime del 1 al tres
        printf("%d . ID: %d \n", i, listaid[i]);
    }

}




#endif //MPAULA_C_GRAFO_H
