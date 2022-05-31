//
// Created by Esteb on 5/31/2022.
//

#ifndef MPAULA_C_CIBERDELINCUENTE_H
#define MPAULA_C_CIBERDELINCUENTE_H

typedef struct Ciberdelincuente Ciberdelincuente;

struct Ciberdelincuente {
    int id;
    char grupo[25];
    char paisorigen[30];
    char ataques[3][25];
    struct Ciberdelincuente *siguiente;
};
Ciberdelincuente* listaCD = NULL;
Ciberdelincuente* finalCD = NULL;
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

#endif //MPAULA_C_CIBERDELINCUENTE_H
