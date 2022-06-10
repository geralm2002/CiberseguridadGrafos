//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include "TipoCiberataque.h"
# include "Ciberdelincuente.h"
# include "Pais.h"
#include "MensajePila.h"

/*============================================================================================================================================*/
//Menus y recoleccion de datos
NodoGrafo * primeroGrafo = NULL;
NodoPila pila ;


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
        printf("\n->Inserte codigo del país de destino: ");
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
    printf("\nInserte el tiempo de duracinn: ");
    scanf("%f", &tiempoDuracion);
    realizarAtaque(&grafo, pProcedente, pDestino, ciberataque, ciberdelincuente, tiempoDuracion, datosAfectados);
    printf( "Enviar notificacion a %s ",pDestino->nombre);
    Notificar(&pila, pDestino->nombre);
    fflush(stdin);
    primeroGrafo = grafo;
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
            char procedente[25], destino[25];
            printf("->Ingrese el nombre del pais que realizo el ataque");
            scanf("%s", &procedente);
            printf("->Ingrese el nombre del pais de destino");
            scanf("%s", &destino);
            int resultado  =eliminarUnCiberAtaque(&primeroGrafo, procedente, destino);
            if(resultado){
                printf("Ataque eliminado exitosamente!");
            }else{
                printf("El ciberataque no se encontró");
            }
            break;
        case 4:
            //eliminar todos los ataques de un pais
            printf("\n->Ingrese el nombre del pais que desea eliminar");
            char pais[25];
            scanf("%s", &pais);
            NodoGrafo * nodo = obtenerVertice(&primeroGrafo, pais);
            if(nodo != NULL){
                eliminarAtaquesPorPais(nodo);
                printf("\nAtaques eliminados\n");
            }else{
                printf("\nPor favor ingrese un pais registrado en el grafo\n");
            }
            break;
        case 5:
            consultarGrafo(primeroGrafo);
            break;
        case 6:
            return 0;
        default:
            printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!\n");
    }
    return 1;
}
void menuGestionarCiberAtaques(){
    int repite = 0;
    do{
        printf("\n     ---------------Submenu gestion de ciberataques(grafos)----------------------------------\n");
        printf("\t\t[01]. Registrar ciberataque\n");
        printf("\t\t[02]. Editar informacion de un ciberataque\n");
        printf("\t\t[03]. Eliminar un ciberataque\n");
        printf("\t\t[04]. Eliminar todos los ciberataques de un país\n");
        printf("\t\t[05]. Consultar toda la información de ciberataques\n");
        printf("\t\t[06]. Volver\n");
        repite = datosGestionarCiberAtaques();
    } while (repite);

}
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
                //registro de mensaje de seguridad
                break;
            case 6:
                //simluacion
                break;
            case 7:
                //obtener rutas
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