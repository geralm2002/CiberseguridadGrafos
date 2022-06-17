//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include <ctype.h>  // isalpha, isupper
/*============================================================================================================================================*/
//Menus y recoleccion de datos

#define MAX_DATOSAFECTADOS 5000
#define MAX_TIEMPO 5000
#define INFINITO 1.0E+38
#define T 25
#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97
#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo
#define ROTACIONES 4 //n desplazamientos

#define TAMMENSAJE 250
/*==================================================================================================================
 *
 *
 *
 *
 *
 *
 *                                        Estructuras de datos
 *
 *
 *
 *
 *
 *
 *==================================================================================================================*/

/*===================*=======================*=======================*=======================*===========================
 *                                                  tipociberataque
 **=======================*=======================*=======================*=======================*======================= */
typedef struct TipoDeCiberataque TipoDeCiberataque;

TipoDeCiberataque* listaTC = NULL;
TipoDeCiberataque* finalTC = NULL;

struct TipoDeCiberataque {
    int codigo;
    char nombre[25];
    char descripcion[100];
    char canales[3][25];
    struct TipoDeCiberataque *siguiente;
};
typedef struct Ciberdelincuente Ciberdelincuente;

struct Ciberdelincuente {
    int id;
    char grupo[25];
    char paisorigen[30];
    char ataques[3][25];
    struct Ciberdelincuente *siguiente;
};

typedef struct Pais Pais;

struct Pais {
    int codigo;
    char nombre[25];
    int habitantes;
    char continente[25];
    struct Pais *izquierda;
    struct Pais *derecha;
};Pais* raiz = NULL;

int getTamannoTipoCiberAtaque(){
    TipoDeCiberataque * puntero = listaTC;
    int cantidad = 0;
    while(puntero!= NULL){
        cantidad = cantidad+1;
        puntero = puntero->siguiente;
    }
    return cantidad;
}
typedef struct {
    int  ultimo;
    float tiempo;
} EstadoVertice;
EstadoVertice D[T];

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
typedef struct NodoPila{
    struct mensaje *mensaje;
    struct nodoPila *siguiente;
}NodoPila;
typedef struct Mensaje{
    char receptor[25];
    char detalle[TAMMENSAJE];
}Mensaje;

NodoPila tope;



NodoGrafo * primeroGrafo = NULL;
NodoPila * pila ;
Ciberdelincuente* listaCD = NULL;
Ciberdelincuente* finalCD = NULL;






int F[T];
float matPesos[T][T];
const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
        *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const int TERRITORIOS[249] = {1,1 ,1242,1246,1264,1268,1284,1340,1345,1441,1473,1649,1664,1670,1671,1672,1684,1721,1758,
                              1767,1784,1787,1808,1809,1868,1869,1876,20,211,212,21229,213,216,218,220,221,222,223,224,
                              225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,
                              248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,
                              27,290,291,297,298,299,30,31,32,33,34,350,351,352,353,354,355,356,357,358,35818,359,36,
                              370,371,372,373,374,375,376,377,378,379,380,381,382,385,386,387,389,39,40,41,420,421,423,
                              43,44,44,44,44,45,46,47,47,47,48,49,500,501,502,503,504,505,506,507,508,509,51,52,53,54,55,
                              56,57,58,590,590,591,592,593,594,595,596,597,598,599,5997,60,61,61,61,62,63,64,64,65,66,
                              670,6721,6723,673,674,675,676,677,678,679,680,681,682,683,685,686,687,688,689,690,691,692,
                              7,7,81,82,84,850,852,853,855,856,86,880,886,90,91,92,93,94,95,960,961,962,963,964,965,966,
                              967,968,670,671,972,973,974,975,976,977,98,992,993,994,995,996,998};




NodoGrafo * nuevoVertice(NodoGrafo** ngrafo, char * nombre);
NodoGrafo * obtenerVertice(NodoGrafo* pGrafo, char * nombre); //obtiene el vertice del grafo, null si no existe
void insertarVertice(NodoGrafo** pGrafo, NodoGrafo* nuevo);
Arista * crearArista(int tipoDeCiberataque, int ciberdelincuente, int datos, float tiempo);
Arista * buscarArista(NodoGrafo** paisGrafo,char * origen ,char * destino); //obtiene un arista
int modficarCiberAtaque(NodoGrafo ** primero);
int eliminarUnCiberAtaque(NodoGrafo ** grafo, char * origen ,char * destino);
void cifrar(char *mensaje, char *destino);
void descifrar(char *mensaje, char *destino);
int ord(char c);

void crearPila(NodoPila** pila);
void push(NodoPila** pila,Mensaje *mensaje);
void pop(NodoPila** pila);//quita el último elemento
int pilaVacia(NodoPila* pila);
Mensaje *cima(NodoPila* pila);
void Notificar(NodoPila** pila ,char * paisdestino);
Mensaje* crearMensaje(char * pais, char m[TAMMENSAJE]);





void insertarTipoCiberAtaque(int codigo, char* nombre, char* descripcion, char* canales[]) {
    TipoDeCiberataque* puntero = (TipoDeCiberataque*) malloc(sizeof(TipoDeCiberataque));    //Se crea un puntero en donde se guarda el nuevo nodo

    puntero->codigo = codigo;                       //Se asignan las variables
    strcpy(puntero->nombre, nombre);
    strcpy(puntero->descripcion, descripcion);
    for (int i = 0; i < 3; i++) {
        strcpy(puntero->canales[i], canales[i]);
    }

    if(listaTC == NULL){                   //Si la lista esta vacia se asigna al inicio
        listaTC = puntero;
        listaTC->siguiente = NULL;
        finalTC = puntero; }
    else {
        finalTC->siguiente = puntero;      //Se asigna el nodo al final de la lista
        puntero->siguiente = NULL;
        finalTC = puntero;
    }
}

void modificarTipoDeCiberataque() {
    TipoDeCiberataque* lista = listaTC;                  //Se crea un puntero hacia la lista

    int codigo = 0;
    printf("Ingrese el codigo del tipo: ");
    scanf("%d", &codigo);

    while (lista != NULL) {                             //Se recorre la lista
        if(lista->codigo == codigo) {
            printf("Ingrese el nuevo nombre: ");
            scanf(" %[^\t\n]s", lista->nombre);
            printf("Ingrese la nueva descripcion: ");
            scanf(" %[^\t\n]s", lista->descripcion);
        }
        lista = lista->siguiente;
    }
}

void mostrarTiposDeCiberataques() {
    TipoDeCiberataque* lista = listaTC;                 //Se crea un puntero hacia la lista

    printf("\n\t----------------------------\n");
    while (lista != NULL) {                              //Se recorre la lista
        printf("\tCodigo: %d\n", lista->codigo);
        printf("\tNombre: %s\n", lista->nombre);
        printf("\tDescripcion: %s\n", lista->descripcion);
        int i = 0;
        printf("\tCanales: \n");
        while (i < 3)
        {
            printf("\t\t%s\n", lista->canales[i]);
            i++;
        }
        printf("\t----------------------------\n");
        lista = lista->siguiente;
    }
    printf("\nPresione una tecla para continuar...");
    system("pause>nul");                                    //Se detiene la consola hasta recibir alguna entrada
}
int eliminarTipoDeCiberAtaque(){
    TipoDeCiberataque * lista =listaTC;
    TipoDeCiberataque * anterior = NULL;
    int codigo = 0;
    printf("Ingrese el codigo del tipo: ");
    scanf("%d", &codigo);
    while(lista!=NULL){
        if(lista->codigo == codigo){
            if(anterior==NULL){
                listaTC = lista->siguiente;
            }else{
                anterior->siguiente = lista->siguiente;
            }
            free(lista);
            return 1;
        }else{
            anterior = lista;
            lista = lista->siguiente;
        };
    }
    return 0;
}
int tipoExiste(TipoDeCiberataque * lista,int tipo){
    TipoDeCiberataque * actual;
    for(;actual->siguiente;){
        if(actual->codigo==tipo){
            return 1;
        }else{
            actual = actual->siguiente;
        }
    }
    return 0;
}
TipoDeCiberataque * obtenerTipoCiberataque(int tipo){
    TipoDeCiberataque * aux = listaTC;
    for(; aux->siguiente; )
    {
        if(aux->codigo == tipo){
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}
TipoDeCiberataque * getTipoByIndex(int i){
    TipoDeCiberataque * puntero = listaTC;
    for(int j = 0; j<i; j++){
        puntero = puntero->siguiente;
    }
    return puntero;
}


/*===================*=======================*=======================*=======================*===========================
 *                                                  ciberdelincuente
 **=======================*=======================*=======================*=======================*======================= */



//Funciones Ciberdelincuente
int getTamannoCiberdelincuente(){
    Ciberdelincuente * puntero = listaCD;
    int cantidad = 0;
    while (puntero!=NULL){
        cantidad = cantidad+1;
        puntero = puntero->siguiente;
    }
    return cantidad;
}
void insertarCiberdelincuente(int id, char* grupo, char* paisorigen, char* ataques[]) {

    Ciberdelincuente* puntero = (Ciberdelincuente*) malloc(sizeof(Ciberdelincuente));       //Se crea un puntero en donde se guarda el nuevo nodo

    puntero->id = id;                                   //Se asignan las variables
    strcpy(puntero->grupo, grupo);
    strcpy(puntero->paisorigen, paisorigen);
    for (int i = 0; i < 3; i++){
        strcpy(puntero->ataques[i], ataques[i]);
    }

    if(listaCD == NULL){                        //Si la lista esta vacia se asigna al inicio
        listaCD = puntero;
        listaCD->siguiente = NULL;
        finalCD = puntero;
    }
    else {                                      //Se asigna el nodo al final de la lista
        finalCD->siguiente = puntero;
        puntero->siguiente = NULL;
        finalCD = puntero;
    }
}

void modificarCiberdelincuente() {
    Ciberdelincuente* lista = listaCD;          //Se crea un puntero hacia la lista

    int id = 0;
    printf("Ingrese el identificador: ");
    scanf("%d", &id);

    while (lista != NULL) {                                 //Se recorre la lista
        if(lista->id == id) {                               //Se valida que sea el id ingresado
            printf("Ingrese el nuevo grupo: ");
            scanf(" %[^\t\n]s", lista->grupo);
            printf("Ingrese el nuevo pais de origen: ");
            scanf(" %[^\t\n]s", lista->paisorigen);
        }
        lista = lista->siguiente;
    }
}
void eliminarCiberDelincuente(){
    Ciberdelincuente* lista = listaCD;
    Ciberdelincuente* anterior;

    anterior = NULL;
    int id = 0;
    printf("Ingrese el identificador: ");
    scanf("%d", &id);
    while (lista != NULL ){
        if(lista->id == id){
            if(anterior != NULL){
                anterior->siguiente = lista->siguiente; //se salta el enlace
                free(lista);
                printf("¡Ciberdelincuente eliminado!\n");
                return;
            }else{
                listaCD = listaCD->siguiente;
                free(lista);
                printf("¡Ciberdelincuente eliminado!\n");
                return;
            }
        }
        anterior = lista;
        lista = lista->siguiente;
    }
    printf("El ciberdelincuente no se encuentra\n");
}
void mostrarciberdelincuentes() {
    Ciberdelincuente* lista = listaCD;
    printf("\n\t----------------------------\n");
    while (lista != NULL) {                                     //Se recorre la lista
        printf("\tIdentificador: %d\n", lista->id);
        printf("\tGrupo: %s\n", lista->grupo);
        printf("\tPais de origen: %s\n", lista->paisorigen);
        int i = 0;
        printf("\tAtaques mas reconocidos: \n");
        while (i < 3) {
            printf("\t\t%s\n", lista->ataques[i]);
            i++;
        }
        printf("\t----------------------------\n");
        lista = lista->siguiente;
    }
    printf("\nPresione una tecla para continuar...");
    system("pause>nul");                                    //Se detiene la consola hasta recibir alguna entrada
}
int ciberdelincuenteExiste(Ciberdelincuente* lista, int id){
    Ciberdelincuente * actual = lista;
    for(;actual->siguiente; ){
        if(actual->id == id){
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}
Ciberdelincuente * obtenerCiberdelicuente(int id){
    Ciberdelincuente * aux  = listaCD;
    for(;aux->siguiente;){
        if(aux->id == id){
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}
Ciberdelincuente * getDelincuenteByIndex(int i){
    Ciberdelincuente * puntero = listaCD;
    for(int j = 0 ; j< i ; j++){
        puntero = puntero ->siguiente;
    }
    return puntero;
}
/*===================*=======================*=======================*=======================*===========================
 *                                                  Pais
 **=======================*=======================*=======================*=======================*======================= */






/*============================================================================================================================================*/
//Funciones Paises

Pais* nuevoPais(int codigo, char nombre[], int habitantes, char continente[]) {
    Pais* puntero = (Pais*) malloc(sizeof(Pais));       //Se crea un puntero en donde se guarda el nuevo nodo

    puntero->codigo = codigo;                       //Se asignan las variables
    strcpy(puntero->nombre, nombre);
    puntero->habitantes = habitantes;
    strcpy(puntero->continente, continente);
    puntero->izquierda = NULL;
    puntero->derecha = NULL;
    return puntero;
}

void insertarPais(Pais* nodo, int codigo, char nombre[], int habitantes, char continente[]) {
    if(nodo == NULL){                                                               //Si la raiz esta vacia se asigna el nuevo pais en el mismo
        raiz = nuevoPais(codigo, nombre, habitantes, continente);
    }
    else if (codigo > nodo->codigo) {              //Se identifica si el nodo debe ir a la derecha
        if (nodo->derecha == NULL) {                                            //Se busca espacio en el nodo derecho
            nodo->derecha = nuevoPais(codigo, nombre, habitantes, continente);
        } else {                                                                //Si no hay se vuelve a buscar utilizando el nodo derecho como raiz
            insertarPais(nodo->derecha, codigo, nombre, habitantes, continente);
        }
    } else {                                       //Se asigna el nodo a la izquierda
        if (nodo->izquierda == NULL) {                                           //Se busca espacio en el nodo derecho
            nodo->izquierda = nuevoPais(codigo, nombre, habitantes, continente);
        } else {                                                                 //Si no hay se vulve a buscar utilizando el nodo izquierdo como raiz
            insertarPais(nodo->izquierda, codigo, nombre, habitantes, continente);
        }
    }
}
Pais * obtenerPais(Pais * nodo, int codigo){
    if(nodo == NULL){
        return NULL;
    }else if(nodo->codigo == codigo)
        return nodo;
    else if(codigo < nodo->codigo) //Se identifica si el nodo debe ir a la izquierda o derecha
        obtenerPais(nodo->izquierda, codigo);
    else
        obtenerPais(nodo->derecha, codigo);
}
void modificarPais(Pais* nodo, int codigo) {
    if(nodo == NULL){                       //Validacion de no tener un registro
        printf("Codigo no encontrado!");
        return;
    }
    else if(nodo->codigo == codigo) {
        printf("Ingrese el nuevo codigo del pais: ");
        scanf("%d", &nodo->codigo);
        printf("Ingrese el nuevo nombre del pais: ");
        scanf(" %[^\t\n]s", nodo->nombre);
        printf("Ingrese la nueva cantidad de habitantes: ");
        scanf("%d", &nodo->habitantes);
        printf("Ingrese el nuevo continente: ");
        scanf("%s", nodo->continente);
        printf("Modificado con exito!");
        printf("\nPresione una tecla para continuar...");
        system("pause>nul");
    }
    else if(codigo < nodo->codigo) {                //Se identifica si el nodo debe ir a la izquierda o derecha
        modificarPais(nodo->izquierda, codigo);
    }
    else {
        modificarPais(nodo->derecha, codigo);
    }
}

Pais* hojaMenor(Pais* nodo) {
    Pais* actual = nodo;                        //Se asigna un puntero al arbol
    while (actual && actual->izquierda) {
        actual = actual->izquierda;
    }
    return actual;
}

Pais* eliminarPais(Pais* nodo, int codigo) {
    if (nodo == NULL)                   //Se valida el no tener registro
        return nodo;

    if (codigo < nodo->codigo)
        nodo->izquierda = eliminarPais(nodo->izquierda, codigo);    //Se busca la hoja con el codigo ingresado a la izquierda

    else if (codigo > nodo->codigo)
        nodo->derecha = eliminarPais(nodo->derecha, codigo);        //Se busca la hoja con el codigo ingresado a la derecha
    else {
        if (nodo->izquierda == NULL) {
            printf("Pais eliminado\n");
            Pais* temp = nodo->derecha;
            free(nodo);
            return temp;
        }
        else if (nodo->derecha == NULL) {
            printf("Pais eliminado\n");
            Pais* temp = nodo->izquierda;
            free(nodo);
            return temp;
        }

        Pais* temp = hojaMenor(nodo->derecha);

        nodo->codigo = temp->codigo;
        nodo->derecha = eliminarPais(nodo->derecha, temp->codigo);
    }
}

void recorrerEnOrden(Pais* nodo) {
    if (nodo != NULL) {                                     //Se valida el no tener un registro
        recorrerEnOrden(nodo->izquierda);                   //Se recorre desde el menor
        printf("\n\t\t------------------\n");
        printf("\t\tCodigo: %d\n", nodo->codigo);
        printf("\t\tNombre: %s\n", nodo->nombre);
        printf("\t\tHabitantes: %d\n", nodo->habitantes);
        printf("\t\tContinente: %s\n", nodo->continente);
        recorrerEnOrden(nodo->derecha);                     //Se recorre por ultimo los mayores
        printf("\t\t------------------\n");
    }
}

void mostrarJerarquia(Pais* nodo, int primero, int nivel) {
    if(nodo!=NULL) {
        if(primero == 1) {          //Se imprime la informacion del nodo base
            printf("\n\n\tCodigo: %d , Nombre: %s, Habitantes: %d, Continente: %s\n", nodo->codigo, nodo->nombre, nodo->habitantes, nodo->continente);
        }
        if(nodo->izquierda != NULL) {
            for(int i = 0; i < nivel; i++){
                printf("\t");       //Se usan tabulaciones para representar la jerarquia
            }
            printf("Codigo: %d , Nombre: %s, Habitantes: %d, Continente: %s\n", nodo->izquierda->codigo, nodo->izquierda->nombre, nodo->izquierda->habitantes, nodo->izquierda->continente);
            mostrarJerarquia(nodo->izquierda, 0, nivel + 1);
        }
        if(nodo->derecha != NULL) {
            for(int i = 0; i < nivel; i++){
                printf("\t");
            }
            printf("Codigo: %d , Nombre: %s, Habitantes: %d, Continente: %s\n", nodo->derecha->codigo, nodo->derecha->nombre, nodo->derecha->habitantes, nodo->derecha->continente);
            mostrarJerarquia(nodo->derecha, 0, nivel + 1);
        }
    }
}
Pais * buscarPorCodigo(Pais * raiz, int codigo){
    int encontrado = 0; //1 si lo encuentra 0 si no
    while (!encontrado && raiz != NULL){
        if(codigo == raiz->codigo){
            encontrado=1;
        }else if(codigo< raiz->codigo){
            raiz = raiz->izquierda;
        }else if(codigo > raiz->codigo){
            raiz = raiz->derecha;
        }
    }
    return raiz; //retorna el nodo encontrado
}


/*===================*=======================*=======================*=======================*===========================
 *                                                  grafos
 **=======================*=======================*=======================*=======================*======================= */






/*=====================================================================================================================
 *                      Declaración de funciones
=====================================================================================================================*/



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
    NodoGrafo * nodoProcedente = obtenerVertice((*pGrafo), procedente->nombre);
    if(nodoProcedente ==NULL){ //en caso de que no exista deberá crear el vertice
        nodoProcedente = nuevoVertice(pGrafo, procedente->nombre); //lo crea
        insertarVertice(pGrafo,nodoProcedente); //inserta el nuevo en el grafo
        printf("\nNuevo nodo insertado\n");
    }else{
        printf("\nEl nodo ya está en el grafo\n");
    }
    NodoGrafo * nodoDestino = obtenerVertice((*pGrafo), destino->nombre); //el ataque guarda el nombre del destino, no el nodo, aún así debemos verificar que esté en el grafo
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
            printf("%s ataco a: \n", primero->nombrePais);
            while(ataquesXnodo !=NULL){
                printf("\n--> %s ",ataquesXnodo->destino);
                arista = ataquesXnodo->arista;
                printf("\n\t\t ID del ciberdelincuente: %d", arista->idciberdelincuente);
                printf("\n\t\t ID del tipo del ciber ataque: %d", arista->idtipo);
                printf("\n\t\t Cantidad de datos afectados: %d", arista->datosAfectados);
                printf("\n\t\t Tiempo de duracion del ciberAtaque: %f\n", arista->tiempo);
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
        printf("\nLa cantidad de ciberataques enviados/recibidos por el tipo de ciberataque %s  es: %d", lista->nombre, cantidad);
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
        printf("\nEl ciberdelincuente %d ha hecho %d ataques\n" ,lista->id, cantidad);
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
/*
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
}*/
/*
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

*/


/*===================*=======================*=======================*=======================*===========================
 *                                                  pila
 **=======================*=======================*=======================*=======================*======================= */

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
void consultarTodaLaPila(NodoPila** pila){
    Mensaje * mensaje;
    char msmDescifrado[TAMMENSAJE];
    while (!pilaVacia(*pila)){
        mensaje = cima(*pila);
        descifrar(msmDescifrado, mensaje->detalle);
        printf("->Pais receptor %s",mensaje->receptor);
        printf("->Detalle descifrado: \n %s", msmDescifrado);
        pop(pila);
    }
    printf("SIN MÁS MENSAJES QUE MOSTRÁR");
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

void Notificar(NodoPila** pila ,char * paisdestino){
    char mensaje[TAMMENSAJE] = "";
    char mensajeCifrado[TAMMENSAJE]="";
    printf("Escribe el mensaje a cifrar: \n");
    fflush(stdin);
    fgets(mensaje, TAMMENSAJE, stdin);
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

void consultarUltimoMensaje(NodoPila** pila){
    char descifrado[TAMMENSAJE];
    if(!pilaVacia(*pila)){
        Mensaje *msm = cima(pila);
        descifrar(msm->detalle,descifrado);
        printf("País de destino: %s",msm->receptor);
        printf("Mensaje: %s",descifrado);
        pop(pila);
    }else{
        printf("Ya no hay más mensajes");
    }
}


/*==================================================================================================================
 *
 *                                        dijsktra
 *
 *==================================================================================================================*/


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


/*==================================================================================================================
 *
 *
 *
 *
 *
 *
 *                                        OPCIONES MENÚS
 *
 *
 *
 *
 *
 *
 *==================================================================================================================*/
void titulo() {
    system("cls");
    printf("\n     ------------------------------------------------------------------------------\n");
	printf("\t\t\t\t CIBERSEGURIDAD \n");
	printf("\t\t  Proyecto Programado II - Primer Semestre 2022\n");
	printf("\t\t  Paula Catillo | Stephanny Salas | Hellen Peraza \n");
	printf("     ------------------------------------------------------------------------------\n");
}
/*==================================================================================================================
 *
 *                                        OPCIONES DEL SUBMENÚ DE TIPOS DE CIBERATAQUES
 *
 *==================================================================================================================*/
int datosTipoCiberataques() {
    int opcion;
    printf("\n\t\tIngrese su opcion: \b\b\b");
    scanf("%d" , &opcion);
    switch (opcion) {
        case 1:
            modificarTipoDeCiberataque();
            break;
        case 2: /*
            int resp = eliminarTipoDeCiberAtaque();     //No debe tener un ataque asociado
            if(resp)
                printf("Tipo de ciberataque eliminado exitosamente\n");
            else
                printf("No se ha podido eliminar el tipo de ciberataque\n");
                */
            break;
        case 3:
            mostrarTiposDeCiberataques();
            break;
        case 4:
            return 0;
        default:
			printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!\n");
    };
    return 1;
}

void menuTipoCiberataques(int repite) {
    do {
        titulo();

        printf("\t\t[01]. Modificar tipos de ciberataque\n");
        printf("\t\t[02]. Eliminar tipos de ciberataque\n");
        printf("\t\t[03]. Ver registros\n");
        printf("\t\t[04]. Salir\n");
        repite = datosTipoCiberataques();
    } while(repite);
}
/*==================================================================================================================
 *
 *                                        OPCIONES DEL SUBMENÚ DE CIBERDELINCUENTES
 *
 *==================================================================================================================*/

int datosCiberdelincuentes() {
    int opcion;
    printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
    scanf("%d" , &opcion);
    switch (opcion) {
        case 1:
            modificarCiberdelincuente();
            break;
        case 2:
            eliminarCiberDelincuente();
            break;
        case 3:
            mostrarciberdelincuentes();
            break;
        case 4:
            return 0;
        default:
			printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!");
    };
    return 1;
}

void menuCiberdelincuentes(int repite) {
    do {
        titulo();
        printf("\t\t[01]. Modificar ciberdelincuente\n");
        printf("\t\t[02]. Eliminar ciberdelincuente\n");
        printf("\t\t[03]. Ver ciberdelincuentes\n");
        printf("\t\t[04]. Salir\n");
        repite = datosCiberdelincuentes();
    } while(repite);
}
/*==================================================================================================================
 *
 *                                        OPCIONES DEL SUBMENÚ DE PAÍSES
 *
 *==================================================================================================================*/
int datosPaises() {
    int codigo;
    int habitantes;
    char nombre[25];
    char continente[25];

    int opcion;
    printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
    scanf("%d" , &opcion);
    switch (opcion) {
        case 1:
            printf("Ingrese el codigo del pais: ");
            scanf("%d", &codigo);
            printf("Ingrese el nombre del pais: ");
            scanf(" %[^\t\n]s", nombre);
            printf("Ingrese la cantidad de habitantes: ");
            scanf("%d", &habitantes);
            printf("Ingrese el continente: ");
            scanf("%s", continente);
            insertarPais(raiz, codigo, nombre, habitantes, continente);
            break;
        case 2:
            printf("Ingrese el codigo del pais: ");
            scanf("%d", &codigo);
            modificarPais(raiz, codigo);
            break;
        case 3:
            printf("Ingrese el codigo del pais: ");
            scanf("%d", &codigo);
            eliminarPais(raiz, codigo);
            break;
        case 4:
            recorrerEnOrden(raiz);
            printf("\nPresione una tecla para continuar...");
            system("pause>nul");
            break;
        case 5:
            mostrarJerarquia(raiz, 1, 2);
            printf("\nPresione una tecla para continuar...");
            system("pause>nul");
            break;
        case 6:
            return 0;
        default:
			printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!\n");
    };
    return 1;
}


void menuPaises(int repite) {
    do {
        printf("\t\t[01]. Insertar pais\n");
        printf("\t\t[02]. Modificar pais\n");
        printf("\t\t[03]. Eliminar pais\n");
        printf("\t\t[04]. Ver paises en orden\n");
        printf("\t\t[05]. Ver paises en jerarquia\n");
        printf("\t\t[06]. Salir\n");
        repite = datosPaises();
    } while(repite);
}
/*==================================================================================================================
 *
 *                               OPCIONES DEL SUBMENÚ DE MENSAJE DE CIFRADO EN PILA
 *
 *==================================================================================================================*/
int datosGestionarMensajes(){
    int opcion;
    fflush(stdin);
    printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
    scanf("%d" , &opcion);
    fflush(stdin);
    switch (opcion) {
        case 1:
            consultarUltimoMensaje(&pila);
            break;
        case 2:
            consultarTodaLaPila(&pila);
            break;
        case 3:
            return 0;
        default:
            printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!\n");
    }
    printf("\nPresione una tecla para continuar...");
    system("pause>nul");
    return 1;

}
void menuMensajeCifrado(){
    int repite = 0;
    do{
        printf("\n     ---------------Submenu gestion de mensajes cifrados(pila)----------------------------------\n");
        printf("\t\t[01]. Consultar el ultimo mensaje de la pila\n");
        printf("\t\t[02]. Consultar toda la pila\n");
        printf("\t\t[03]. Volver\n");
        repite = datosGestionarMensajes();
    } while (repite);

}
/*==================================================================================================================
 *
 *                                        OPCIONES DEL SUBMENÚ DE GRAFOS
 *
 *==================================================================================================================*/
void opcionRegistraCiberAtaque(){
    NodoGrafo * grafo = primeroGrafo;
    int codigoPaisProcedente,
    codigoPaisDestino,
    idTipoCiberataque,
    idCiberdelincuente,
    datosAfectados;
    float tiempoDuracion;

    Pais * pProcedente;
    Pais * pDestino;
    Ciberdelincuente * ciberdelincuente;
    TipoDeCiberataque * ciberataque;
    //Obtener país de prcedencia válido
    do{
        printf("\n->Inserte el codigo del pais que realiza el ataque: ");
        scanf("%d", &codigoPaisProcedente);
        pProcedente = buscarPorCodigo(raiz, codigoPaisProcedente);
        if(pProcedente==NULL)
            printf("El pais de origen no se encuentra registrado! intente de nuevo\n");
    } while (pProcedente==NULL);
    //Obtener país de destino válido
    do{
        printf("\n->Inserte codigo del pais de destino: ");
        scanf("%d", &codigoPaisDestino);
        pDestino = buscarPorCodigo(raiz, codigoPaisDestino);
        if(pDestino==NULL)
            printf("El pais de destino no se encuentra registrado! intente de nuevo\n");
    } while (pDestino==NULL);
    //Obtener país tipo ciberataque
    do{
        printf("\n->Inserte el id del tipo de ciberataque: ");
        scanf("%d", &idTipoCiberataque);
        ciberataque = obtenerTipoCiberataque(idTipoCiberataque);
        if(ciberataque==NULL){
            printf("El tipo del ciberataque no se encuentra registrado\n");
        }
    } while (ciberataque ==NULL);
    //Obtener país ciberdelincuente
    do{
        printf("\n->Inserte el ciberdelincuente: ");
        scanf("%d", &idCiberdelincuente);
        ciberdelincuente = obtenerCiberdelicuente(idCiberdelincuente);
        if(ciberdelincuente==NULL)
            printf("Por favor ingrese un ciberdelincuente registrado\n");
    } while (ciberdelincuente== NULL);
    printf("\nInserte la cantidad de datos afectados en gigabytes: ");
    scanf("%d", &datosAfectados);
    printf("\nInserte el tiempo de duracion: ");
    scanf("%f", &tiempoDuracion);
    NodoGrafo* respuesta = realizarAtaque(&grafo, pProcedente, pDestino, ciberataque, ciberdelincuente, tiempoDuracion, datosAfectados);
    if(respuesta){
        printf( "Enviar notificacion a %s ",pDestino->nombre);
        fflush(stdin);
        Notificar(&pila, pDestino->nombre);
        fflush(stdin);
        primeroGrafo = grafo;
    }
}

void opcionEliminarTodoAtaque(){
    int idprocedente;
    Pais * paisProcedente;
    do {
        printf("\n->Ingrese el id del pais que desea eliminar todos sus ataques: ");
        scanf("%d", &idprocedente);
        fflush(stdin);
        paisProcedente= obtenerPais(raiz,idprocedente);
        if(paisProcedente==NULL){
            printf("El país no existe registrado en el arbol\n intente de nuevo");
        }
    } while (paisProcedente== NULL);

    NodoGrafo * nodoPaisG = obtenerVertice(primeroGrafo, paisProcedente->nombre);
    if(nodoPaisG != NULL){
        eliminarAtaquesPorPais(nodoPaisG);
        printf("\nAtaques eliminados\n");
    }else{
        printf("\nPor favor ingrese un pais registrado en el grafo\n");
    }
}
void opcionEliminarUnCiberAtaque(){
    int idprocedente, iddestino;
    Pais * paisProcedente;
    Pais * paisDestino;
    do {
        printf("->Ingrese el id del pais que realizo el ataque: ");
        scanf("%d", &idprocedente);
        fflush(stdin);
        paisProcedente= obtenerPais(raiz,idprocedente);
        if(paisProcedente==NULL){
            printf("El país no existe registrado en el árbol\n intente de nuevo");
        }
    } while (paisProcedente== NULL);
    do{
        printf("->Ingrese el id del pais de destino");
        scanf("%d", &iddestino);
        fflush(stdin);
        paisDestino= obtenerPais(raiz,iddestino);
        if(paisDestino==NULL)
            printf("El país no existe registrado en el arbol");
    }while(paisDestino==NULL);
    //los whiles verfican que estén registrados mas no que estén en el grafo y que tengan un ciber ataque
    int resultado  =eliminarUnCiberAtaque(&primeroGrafo, paisProcedente->nombre, paisDestino->nombre);
    if(resultado){
        printf("Ataque eliminado exitosamente!");
    }else{
        printf("El ciberataque no se encontro, intente de nuevo");
    }
}
int datosGestionarCiberAtaques(){
    int opcion;
    fflush(stdin);
    printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
    scanf("%d" , &opcion);


    switch (opcion) {
        case 1:
            opcionRegistraCiberAtaque();
            break;
        case 2:
            modficarCiberAtaque(&primeroGrafo);
            break;
        case 3:
            opcionEliminarUnCiberAtaque();
            break;
        case 4:
            opcionEliminarTodoAtaque();
            break;
        case 5:
            consultarGrafo(primeroGrafo);
            break;
        case 6:
            return 0;
        default:
            printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!\n");
    }
    printf("\nPresione una tecla para continuar...");
    system("pause>nul");
    return 1;
}
void menuGestionarCiberAtaques(){
    int repite = 0;
    do{
        printf("\n     ---------------Submenu gestion de ciberataques(grafos)----------------------------------\n");
        printf("\t\t[01]. Registrar ciberataque\n");
        printf("\t\t[02]. Editar informacion de un ciberataque\n");
        printf("\t\t[03]. Eliminar un ciberataque\n");
        printf("\t\t[04]. Eliminar todos los ciberataques de un pais\n");
        printf("\t\t[05]. Consultar toda la informacion de ciberataques\n");
        printf("\t\t[06]. Volver\n");
        repite = datosGestionarCiberAtaques();
    } while (repite);

}
/*==================================================================================================================
 *
 *                                        OPCIONES MENÚ Y ANEXOS AL PROGRAMA PRINCIPAL
 *
 *==================================================================================================================*/
void Menu() {
    titulo();
    printf("\t\t[01]. Menu tipo ciberataque\n"); //
    printf("\t\t[02]. Menu ciberdelincuente\n"); //
    printf("\t\t[03]. Menu de informacion de paises\n"); //
    printf("\t\t[04]. Gestion de informacion de ciberataques\n");
    printf("\t\t[05]. Registro de mensaje de seguridad de notificacion de ciberataque\n");
    printf("\t\t[06]. Simulacion de ciberataques\n");
    printf("\t\t[07]. Obtener rutas de ciberataques\n");
    printf("\t\t[08]. Analisis de datos\n");
    printf("\t\t[09]. Salir\n");
}
void insertarDatosManuales(){
    char* canales[] = {"Canal1" , "Canal2" , "Canal3"};
    insertarTipoCiberAtaque(1, "Malware1" , "Infecta tu computadora con algún virus" , canales);
    insertarTipoCiberAtaque(2, "Troyen" , "Se esconde en tu computadora sin que te des cuenta" , canales);
    insertarTipoCiberAtaque(3, "Phishing" , "Abres algún correo y te robará datos o secuestrará tu computadora" , canales);
    insertarTipoCiberAtaque(4, "DDos" , "Satura la red de un servidor para evitar su acceso" , canales);
    char* ataques[] = {"Ataque 1" , "Ataque 2" , "Ataque 3"};//procuren que siempre sean 3 ataques
    insertarCiberdelincuente(1, "n/a", "Costa Rica", ataques);
    insertarCiberdelincuente(2, "Anonymous", "Alemania", ataques);
    insertarCiberdelincuente(3, "HackerSpace", "Inglaterra", ataques);

    insertarPais(raiz, 506, "Costa Rica" , 200000, "America");
    insertarPais(raiz, 47, "Noruega" , 537900, "Europa");
    insertarPais(raiz, 81, "Japon" , 125800, "Asia");
    insertarPais(raiz, 54, "Argentina" , 4538000, "America");
    insertarPais(raiz, 61, "Australia" , 2569000, "Asia");
    insertarPais(raiz, 380, "Ucrania" , 4413000, "Europa");
}
int getAleatorio(int max){
    int a=(int) ((double)rand() /((double)RAND_MAX +1) * max);
    return a;
}

void simularAtaques(){
    NodoGrafo * grafo = primeroGrafo;
    int cantidAtaques;
    printf("Ingrese la cantidad de ciberataques que desea simular: ");
    scanf("%d", &cantidAtaques);
    int tamTipo = getTamannoTipoCiberAtaque(); //maximo de tipos de la lista para generar un aleatorio en ese rango
    int tamDelincuente = getTamannoCiberdelincuente(); //maximo de la lista de ciber delincuentes para generar un aleatorio en ese rango
    for(int i = 0; i<cantidAtaques; i++){
        int paisO, paisD,datos, tiempo;
        Pais * origen, * destino;
        Ciberdelincuente * delicuente;
        TipoDeCiberataque * tipo;
        do{
            paisO=getAleatorio(248);
            paisO = TERRITORIOS[paisO];
            origen = obtenerPais(raiz, paisO);
        }while(origen ==NULL);
        do{
            paisD = TERRITORIOS[getAleatorio(248)];
            destino = obtenerPais(raiz, paisD); //obtiene hasta que exista en el arbol
        }while(destino ==NULL);

        delicuente = getDelincuenteByIndex(getAleatorio(tamDelincuente));
        tipo = getTipoByIndex(getAleatorio(tamTipo-1));
        datos = getAleatorio(MAX_DATOSAFECTADOS);
        tiempo = getAleatorio(MAX_TIEMPO);
        realizarAtaque(&grafo, origen, destino, tipo, delicuente, tiempo, datos);
        primeroGrafo = grafo;
    }
    printf("Todos los ataques han sido registrados exitosamente");

}
void analisisDeDatos(){
    int cantidadTotal = 0;
    printf("\n\n-----------Analisis de datos -----------\n\n");
    cantidadTotal = cantidadtotalCiberAtaques(&primeroGrafo);
    printf("La cantidad total de ciberataques enviados/recibidos es: %d \n", cantidadTotal);
    printf("La cantidad de ataques efectuados por pais: \n");
    cantidadEnviadosRecibidosXpais(&primeroGrafo);
    printf("La cantidad de ataques efectuados por ciberataque: \n");
    cantidadPorTipoCiberataque(&primeroGrafo);
    printf("La cantidad total de ataques efectuados por ciberdelincuente corresponde a: \n");
    cantidadPorCiberDelincuente(&primeroGrafo);
    //topTresPaisesAtacados(&primeroGrafo);
    //topTresCiberDelincuentes(&primeroGrafo);
}
/*============================================================================================================================================*/
int main() {
    insertarDatosManuales();
    crearPila(&pila); //crea una pila vacía
    int opcion = 0;
    char repite = 1;
    setbuf(stdout, 0);
    do{
        system("cls");
        Menu();

        printf("\n\t\tIngrese su opcion: \b\b\b");
        scanf("%d" , &opcion);

        switch (opcion) {
            case 1:
                menuTipoCiberataques(1);
                break;
            case 2:
                menuCiberdelincuentes(1);
                break;
            case 3:
                menuPaises(1);
                break;
            case 4:
                menuGestionarCiberAtaques();
            case 5:
                menuMensajeCifrado();
                break;
            case 6:
                simularAtaques();
                break;
            case 7:
                //obtener rutas3
                break;
            case 8:
                analisisDeDatos();
                break;
            case 9:
                repite = 0;
                break;
            default:
			    printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!");
        }
    } while (repite);
    return 0;
}