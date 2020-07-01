#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paises.h"
#include "time.h"
#include "LinkedList.h"


int mapearInfectados(void* unPais);
int filtrarxExito(void* unPais);
int filtrarxHorno(void* unPais);
int comparaPaises(void* a,void* b);
int ordenarPaises(LinkedList* pArrayListEmployee);
int guardarPaises(char* path, LinkedList* pArrayListEmployee);
int listarPaisMuertos(LinkedList* pArrayListEmployee);

int menu();

int main()
{

    char seguir = 's';
    char confirma;

    LinkedList* lista = ll_newLinkedList();
    LinkedList* listaMapeada;
    LinkedList* listaFiltradaExito;
    LinkedList* listaFiltradaHorno;
    srand(time(NULL));

    if(lista != NULL)
    {
        do
        {
            switch(menu())
            {
            case 1:
                system("cls");
                if(ll_isEmpty(lista))
                {
                    if(cargarCsvPandemia("pandemia.csv",lista))
                    {
                        printf("Se han cargado los paises correctamente!\n");
                        system("pause");
                    }
                }
                else
                {

                    printf("Ya se cargaron los datos anteriormente.\n");
                    system("pause");
                }
                break;
            case 2:
                if(ll_isEmpty(lista))
                {
                    system("cls");
                    printf("La lista esta vacia\n");
                    system("pause");

                }
                else
                {
                    system("cls");
                    listarPais(lista);
                    system("pause");
                }
                break;
            case 3:
                system("cls");
                if(ll_isEmpty(lista))
                {
                    system("cls");
                    printf("La lista esta vacia\n");
                    system("pause");

                }
                else
                {
                    listaMapeada = ll_map(lista, mapearInfectados);
                    if(listaMapeada != NULL)
                    {

                        printf("Paises Mapeados!\n\n");

                    }
                    else
                    {

                        printf("Error al mapear\n");
                    }
                    system("pause");
                }
                break;
            case 4:

                listaFiltradaExito = ll_filter(listaMapeada, filtrarxExito);
                listarPais(listaFiltradaExito);
                system("pause");

                break;
            case 5:
                system("cls");

                listaFiltradaHorno = ll_filter(listaMapeada, filtrarxHorno);
                listarPais(listaFiltradaHorno);
                system("pause");
                break;

            case 6:
                listarPais(listaMapeada);
                system("pause");
                break;
            case 7:

                system("cls");
                if(ordenarPaises(listaMapeada))
                {

                    printf("\nOrdenamiento Exitoso!\n");
                    system("pause");
                }

                break;
            case 8:
                system("cls");
                if(guardarPaises("paisesFiltradosExito.csv", listaFiltradaExito))
                {
                    printf("\nGuardados!\n");
                    system("pause");
                }
                break;
            case 9:
                system("cls");
                if(guardarPaises("paisesFiltradosHorno.csv", listaFiltradaHorno))
                {
                    printf("\nGuardados!\n");
                    system("pause");
                }

                break;

            case 10:
                system("cls");
                listarPaisMuertos(listaMapeada);
                system("pause");

                break;

            case 11:
                system("cls");

                if(ll_clear(lista)==0)
                {

                    printf("Elementos eliminados\n");
                    system("pause");
                }

                break;
            case 12:
                printf("Confirma salida?:\n");
                fflush(stdin);
                scanf("%c", &confirma);
                if(confirma == 's')
                {
                    ll_deleteLinkedList(lista);
                    seguir = 'n';

                }
                break;
            }

        }
        while(seguir == 's');
    }

    system("cls");



    return 0;
}

int menu()
{

    int opcion;

    system("cls");
    printf("Menu de Opciones\n\n");
    printf("1. Cargar Paises de paises.csv\n");
    printf("2. Listar Paises\n");
    printf("3. Mapear autos\n");
    printf("4. Filtrar Exito\n");
    printf("5. Filtrar Horno\n");
    printf("6. Listar Paises Mapeados\n");
    printf("7. Ordenar paises\n");
    printf("8. Guardar paises con exito\n");
    printf("9. Guardar paises al horno\n");
    printf("10. Listar mas muertos\n");
    printf("11. Eliminar todos los autos\n");
    printf("12. Salir\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;

}

/** \brief Le otorga valores aleatorios a los campos de ePaises.
 *
 * \param void unPais, elemento de la lista.
 * \param
 * \return retorna 1 si salio todo correctamente, 0 unPais es NULL.
 *
 */


int mapearInfectados(void* unPais)
{

    int auxReturn = 0;
    ePais* auxPais;

    if(unPais != NULL)
    {

        auxPais = (ePais*) unPais;
        auxPais->recuperados= rand()%(1000001) + 50000;
        auxPais->infectados = rand()%(2000001) + 40000;
        auxPais->muertos = rand()%(5001) + 1000;
        auxReturn = 1;
    }

    return auxReturn;
}

/** \brief Filtra la lista por paises con muertos entre 1000 y 5000
 *
 * \param void unPais, elemento de la lista.
 * \param
 * \return 1 si funciono, 0 si no funciono.
 *
 */


int filtrarxExito(void* unPais)
{

    int auxReturn = 0;
    ePais* auxPais;

    if(unPais != NULL)
    {

        auxPais = (ePais*) unPais;
    }

    if(auxPais->muertos >= 1000 && auxPais->muertos <= 5000)
    {
        auxReturn = 1;
    }

    return auxReturn;
}


/** \brief Filtra la lista por paises con triple de infectados que recuperados
 *
 * \param void unPais, elemento de la lista.
 * \param
 * \return 1 si funciono, 0 si no funciono.
 *
 */

int filtrarxHorno(void* unPais)
{

    int auxReturn = 0;
    float num;
    ePais* auxPais;

    if(unPais != NULL)
    {

        auxPais = (ePais*) unPais;
    }

    num = (float) auxPais->infectados / 3;

    if(num >= auxPais->recuperados)
    {
        auxReturn = 1;
    }

    return auxReturn;
}

/** \brief compara paises por numero de infectados
 *
 * \param void a
 * \param void b
 * \return 1 si se logro correctamente, 0 si hubo error.
 *
 */


int comparaPaises(void* a,void* b)
{
    int retorno = 0;
    ePais* a1;
    ePais* a2;

    if(a != NULL && b != NULL)
    {

        a1 = (ePais*) a;
        a2 = (ePais*) b;
    }

    if(a1->infectados < a2->infectados)
    {

        retorno = 1;

    }
    else if(a1->infectados > a2->infectados)
    {

        retorno = -1;

    }

    return retorno;
}

/** \brief llama a la funcion ll_sort para ordenar
 *
 * \param Linkedlist* list
 * \param
 * \return 1 si funciono
 *
 */


int ordenarPaises(LinkedList* pArrayListEmployee)
{
    int retorno = 0;
    printf("Ordenar Paises\n\n");

    if(pArrayListEmployee!=NULL)
    {
        printf("\nOrdenando...\n");
        ll_sort(pArrayListEmployee, comparaPaises, 1);
        retorno = 1;

    }


    return retorno;
}

int guardarPaises(char* path, LinkedList* pArrayListEmployee)
{
    int i = 0;
    int tam;
    int id;
    int muertos;
    int infectados;
    char nombre[20];
    int recuperados;
    FILE* pFile;
    ePais* auxPais;

    pFile = fopen(path, "w");

    if(pFile != NULL)
    {
        tam = ll_len(pArrayListEmployee);
        fprintf(pFile, "id, nombre, recuperados, infectados, muertos\n");

        while(i < tam)
        {

            auxPais = (ePais*) ll_get(pArrayListEmployee, i);
            if(auxPais != NULL && pais_getInfectados(auxPais, &infectados)
                    && pais_getId(auxPais, &id)
                    && pais_getMuertos(auxPais, &muertos)
                    && pais_getNombre(auxPais, nombre)
                    && pais_getRecuperados(auxPais, &recuperados))
            {

                fprintf(pFile, "%d, %s, %d, %d, %d\n", id, nombre, recuperados,  infectados, muertos);
            }

            i++;
        }
    }

    fclose(pFile);

    return 1;
}

int listarPaisMuertos(LinkedList* pArrayListEmployee)
{
    int tam = ll_len(pArrayListEmployee);
    int flag = 0;
    ePais* auxPais;
    ePais* auxMayor;

    printf("Pais con mas muertos\n\n");

    if( pArrayListEmployee != NULL  )
    {
        for(int i= 0; i < tam; i++)
        {
            auxPais = (ePais*) ll_get(pArrayListEmployee, i);
            if(flag == 0)
            {
                auxMayor = auxPais;
                flag = 1;
            }
            else if(auxMayor->muertos <= auxPais->muertos)
            {

                auxMayor= auxPais;
            }

        }
    }

    printf("%10s\n\n", auxMayor->nombre);
    return 1;
}
