

#ifndef MPAULA_C_TIPOCIBERATAQUE_H
#define MPAULA_C_TIPOCIBERATAQUE_H
//Inicializadores

typedef struct TipoDeCiberataque TipoDeCiberataque;

struct TipoDeCiberataque {
    int codigo;
    char nombre[25];
    char descripcion[30];
    char canales[3][25];
    struct TipoDeCiberataque *siguiente;
};
TipoDeCiberataque* listaTC = NULL;
TipoDeCiberataque* finalTC = NULL;

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


#endif //MPAULA_C_TIPOCIBERATAQUE_H
