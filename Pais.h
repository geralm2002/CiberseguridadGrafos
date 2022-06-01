//
// Created by Esteb on 5/31/2022.
//

#ifndef MPAULA_C_PAIS_H
#define MPAULA_C_PAIS_H


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




/*============================================================================================================================================*/

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

#endif //MPAULA_C_PAIS_H
