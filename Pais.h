//
// Created by Esteb on 5/31/2022.
//

#ifndef MPAULA_C_PAIS_H
#define MPAULA_C_PAIS_H

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


typedef struct Pais Pais;

struct Pais {
    int codigo;
    char nombre[25];
    int habitantes;
    char continente[25];
    struct Pais *izquierda;
    struct Pais *derecha;
};Pais* raiz = NULL;

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
Pais * buscarPorCodigo(Pais * raiz, int codigo){
    int encontrado = 0; //1 si lo encuentra 0 si no
    while (!encontrado && raiz != NULL){
        if(codigo == raiz->codigo){
            encontrado=1;
        }else if(codigo< raiz->codigo){
            raiz = raiz->izquierda;
        }else if(codigo> raiz->derecha){
            raiz = raiz->derecha;
        }
    }
    return raiz; //retorna el nodo encontrado
}

#endif //MPAULA_C_PAIS_H
