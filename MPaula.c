//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estructuras

typedef struct TipoDeCiberataque TipoDeCiberataque;
typedef struct Ciberdelincuente Ciberdelincuente;
typedef struct Pais Pais;

struct TipoDeCiberataque {
    int codigo;
    char nombre[25];
    char descripcion[30];
    char canales[3][25];
    struct TipoDeCiberataque *siguiente;
};

struct Ciberdelincuente {
    int id;
    char grupo[25];
    char paisorigen[30];
    char ataques[3][25];
    struct Ciberdelincuente *siguiente;
};

struct Pais {
    int codigo;
    char nombre[25];
    int habitantes;
    char continente[25];
    struct Pais *izquierda;
    struct Pais *derecha;
};

//Inicializadores
TipoDeCiberataque* listaTC = NULL;
TipoDeCiberataque* finalTC = NULL;

Ciberdelincuente* listaCD = NULL;
Ciberdelincuente* finalCD = NULL;

Pais* raiz = NULL;

/*============================================================================================================================================*/
//Funciones Tipo Ciber Ataque

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
            scanf(" %[^\t\n]s", &lista->nombre);
            printf("Ingrese la nueva descripcion: ");
            scanf(" %[^\t\n]s", &lista->descripcion);
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

/*============================================================================================================================================*/
//Funciones Ciberdelincuente

void insertarCiberdelinciente(int id, char* grupo, char* paisorigen, char* ataques[]) {
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
            scanf(" %[^\t\n]s", &lista->grupo);
            printf("Ingrese el nuevo pais de origen: ");
            scanf(" %[^\t\n]s", &lista->paisorigen);
        }
        lista = lista->siguiente;
    }
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

void modificarPais(Pais* nodo, int codigo) {
    if(nodo == NULL){                       //Validacion de no tener un registro
        printf("Codigo no encontrado!");
        return;
    }
    else if(nodo->codigo == codigo) {
        printf("Ingrese el nuevo codigo del pais: ");
        scanf("%d", &nodo->codigo);
        printf("Ingrese el nuevo nombre del pais: ");
        scanf(" %[^\t\n]s", &nodo->nombre);
        printf("Ingrese la nueva cantidad de habitantes: ");
        scanf("%d", &nodo->habitantes);
        printf("Ingrese el nuevo continente: ");
        scanf("%s", &nodo->continente);
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
            Pais* temp = nodo->derecha;
            free(nodo);
            return temp;
        }
        else if (nodo->derecha == NULL) {
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

/*============================================================================================================================================*/
//Menus y recoleccion de datos

void titulo() {
    system("cls");
    printf("\n     ------------------------------------------------------------------------------\n");
	printf("\t\t\t\t CIBERSEGURIDAD \n");
	printf("\t\t  Proyecto Programado II - Primer Semestre 2022\n");
	printf("\t\t                 Paula Catillo \n");
	printf("     ------------------------------------------------------------------------------\n");
}

int datosTipoCiberataques() {
    int opcion;
    char repite = 1;
    printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
    scanf("%d" , &opcion);
    switch (opcion) {
        case 1:
            modificarTipoDeCiberataque();
            break;
        case 2:
            printf("Por implementar");
            break;
        case 3:
            mostrarTiposDeCiberataques();
            break;
        case 4:
            return 0;
        default:
			printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!");
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

int datosCiberdelincuentes() {
    int opcion;
    printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
    scanf("%d" , &opcion);
    switch (opcion) {
        case 1:
            modificarCiberdelincuente();
            break;
        case 2:
            printf("Por implementar");
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

int datosPaises() {
    int codigo;
    int habitantes;
    char nombre[25];
    char continente[25];

    int opcion;
    char repite = 1;
    printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
    scanf("%d" , &opcion);
    switch (opcion) {
        case 1:
            printf("Ingrese el codigo del pais: ");
            scanf("%d", &codigo);
            printf("Ingrese el nombre del pais: ");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese la cantidad de habitantes: ");
            scanf("%d", &habitantes);
            printf("Ingrese el continente: ");
            scanf("%s", &continente);
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
			printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!");
    };
    return 1;
}

void menuPaises(int repite) {
    do {
        titulo();
        printf("\t\t[01]. Insertar pais\n");
        printf("\t\t[02]. Modificar pais\n");
        printf("\t\t[03]. Eliminar pais\n");
        printf("\t\t[04]. Ver paises en orden\n");
        printf("\t\t[05]. Ver paises en jerarquia\n");
        printf("\t\t[06]. Salir\n");
        repite = datosPaises();
    } while(repite);
}

void Menu() {
    titulo();
    printf("\t\t[01]. Registro tipo ciberataque\n");
    printf("\t\t[02]. Registro ciberdelincuente\n");
    printf("\t\t[03]. Registro de informacion de paises\n");
    printf("\t\t[04]. Gestion de informacion de ciberataques\n");
    printf("\t\t[05]. Registro de mensaje de seguridad de notificacion de ciberataque\n");
    printf("\t\t[06]. Simulacion de ciberataques\n");
    printf("\t\t[07]. Obtener rutas de ciberataques\n");
    printf("\t\t[08]. Analisis de datos\n");
    printf("\t\t[10]. Salir\n");
}

/*============================================================================================================================================*/
int main() {
    //CARGA DE DATOS (solo voy a meter un registro por cada uno para que ustedes metan sus propios datos)
    char* canales[] = {"Canal1" , "Canal2" , "Canal3"};
    insertarTipoCiberAtaque(1, "Tipo1" , "Malware" , canales);

    char* ataques[] = {"Ataque 1" , "Ataque 2" , "Ataque 3"};//procuren que siempre sean 3 ataques
    insertarCiberdelinciente(1, "n/a", "costa rica", ataques);

    insertarPais(raiz, 506, "Costa Rica" , 200000, "America");
    insertarPais(raiz, 47, "Noruega" , 537900, "Europa");
    insertarPais(raiz, 81, "Japon" , 125800, "Asia");
    insertarPais(raiz, 54, "Argentina" , 4538000, "America");
    insertarPais(raiz, 61, "Australia" , 2569000, "Asia");
    insertarPais(raiz, 380, "Ucrania" , 4413000, "Europa");
    int opcion = 0;
    char repite = 1;
    
    do{
        system("cls");
        Menu();
        printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
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
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                repite = 0;
                break;
            default:
			    printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!");
        }
    } while (repite);
    return 0;
}