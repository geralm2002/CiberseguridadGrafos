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
                printf("Tipo de ciber ataque eliminado exitosamente");
            else
                printf("No se ha podido eliminar el tipo de cirber ataque");
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
            //insertarCiberdelincuente();
            break;
        case 2:
            modificarCiberdelincuente();

            break;
        case 3:
            eliminarCiberDelincuente();
            break;
        case 4:
            mostrarciberdelincuentes();
            break;
        case 5:
            return 0;
        default:
			printf("Error: Favor ingresar uno de los numeros que se muestran en el menu!");
    };
    return 1;
}

void menuCiberdelincuentes(int repite) {
    do {
        titulo();
        printf("\t\t[01]. Agregar ciberdelincuente\n");
        printf("\t\t[02]. Modificar ciberdelincuente\n");
        printf("\t\t[03]. Eliminar ciberdelincuente\n");
        printf("\t\t[04]. Ver ciberdelincuentes\n");
        printf("\t\t[05]. Salir\n");
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
    //insertarCiberdelinciente(1, "n/a", "costa rica", ataques);

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