
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
void agregarCiberDelincuente(){
    int id;
    char grupo[25];
    char paisOrigen[30];

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
            scanf(" %[^\t\n]s", &lista->grupo);
            printf("Ingrese el nuevo pais de origen: ");
            scanf(" %[^\t\n]s", &lista->paisorigen);
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
        if(lista->id = id){
            if(anterior != NULL){
                 anterior->siguiente = lista->siguiente; //se salta el enlace
                 free(lista);
                 printf("¡Ciberdelincuente eliminado!");
                 return;
            }else{


            }
        }
        anterior = lista;
        lista = lista->siguiente;
    }
    printf("El ciberdelincuente no se encuentra");
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
        if(actual->id = id){
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}


#endif //MPAULA_C_CIBERDELINCUENTE_H
