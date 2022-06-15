//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include "TipoCiberataque.h"
# include "Ciberdelincuente.h"
# include "Pais.h"
#include "MensajePila.h"
#include <time.h>
/*============================================================================================================================================*/
//Menus y recoleccion de datos
NodoGrafo * primeroGrafo = NULL;
NodoPila * pila ;
#define MAX_DATOSAFECTADOS 5000
#define MAX_TIEMPO 5000

void titulo() {
    system("cls");
    printf("\n     ------------------------------------------------------------------------------\n");
	printf("\t\t\t\t CIBERSEGURIDAD \n");
	printf("\t\t  Proyecto Programado II - Primer Semestre 2022\n");
	printf("\t\t                 Paula Catillo \n");
	printf("     ------------------------------------------------------------------------------\n");
}
/*==================================================================================================================
 *
 *                                        OPCIONES DEL SUBMENÚ DE TIPOS DE CIBERATAQUES
 *
 *==================================================================================================================*/
int datosTipoCiberataques() {
    int opcion;
    printf("\n\t\tIngrese su opcion: [  ]\b\b\b");
    scanf("%d" , &opcion);
    switch (opcion) {
        case 1:
            modificarTipoDeCiberataque();
            break;
        case 2:
            int resp = eliminarTipoDeCiberAtaque();     //No debe tener un ataque asociado
            if(resp)
                printf("Tipo de ciberataque eliminado exitosamente\n");
            else
                printf("No se ha podido eliminar el tipo de ciberataque\n");
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
            printf("El país no existe registrado en el árbol\n intente de nuevo");
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
            printf("El país no existe registrado en el árbol");
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
                //análisis de datos
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