#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paises.h"
#include "LinkedList.h"

ePais* pais_new()
{
    ePais* newPais =(ePais*) malloc(sizeof(ePais));

    if(newPais != NULL)
    {
        newPais->id = 0;
        strcpy(newPais->nombre, "");
        newPais->recuperados = 0;
        newPais->infectados = 0;
        newPais->muertos = 0;

    }

    return newPais;
}

ePais* new_AutoParam(int id, char* nombre, int recuperados, int infectados, int muertos)
{
    ePais* newPais = pais_new();

    if(newPais != NULL)
    {
        if(!(pais_setId(newPais, id)
                && pais_setNombre(newPais, nombre)
                && pais_setRecuperados(newPais, recuperados)
                && pais_setInfectados(newPais, infectados)
                && pais_setMuertos(newPais, muertos)))
        {
            free(newPais);
            newPais = NULL;
        }
    }
    return newPais;
}

ePais* pais_newParametros(char* idStr,char* nombreStr,char* recuperados, char* infectados, char* muertos)
{

    return new_AutoParam(atoi(idStr), nombreStr, atoll(recuperados), atoi(infectados), atoi(muertos));

}

int pais_setId(ePais* this,int id)
{
    int todoOk = 0;

    if(this != NULL && id >=0)
    {
        this->id = id;
        todoOk = 1;
    }
    return todoOk;
}

int pais_getId(ePais* this,int* id)
{
    int todoOk = 0;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        todoOk = 1;
    }
    return todoOk;
}

int pais_setNombre(ePais* this,char* nombre)
{

    int todoOk = 0;

    if(this != NULL && nombre != NULL && strlen(nombre) >= 3 && strlen(nombre)< 20)
    {
        strcpy(this->nombre, nombre);
        todoOk = 1;
    }
    return todoOk;

}

int pais_getNombre(ePais* this,char* nombre)
{
    int todoOk = 0;

    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        todoOk = 1;
    }
    return todoOk;
}

int pais_setRecuperados(ePais* this, int recuperados)
{
    int todoOk = 0;

    if(this != NULL && recuperados >=0)
    {
        this->recuperados = recuperados;
        todoOk = 1;
    }
    return todoOk;

}

int pais_getRecuperados(ePais* this, int* recuperados)
{
    int todoOk = 0;

    if(this != NULL && recuperados != NULL)
    {
        *recuperados = this->recuperados;
        todoOk = 1;
    }
    return todoOk;
}

int pais_setInfectados(ePais* this,int infectados)
{

    int todoOk = 0;

    if(this != NULL && infectados >=0)
    {
        this->infectados = infectados;
        todoOk = 1;
    }
    return todoOk;
}

int pais_getInfectados(ePais* this,int* infectados)
{
    int todoOk = 0;

    if(this != NULL && infectados != NULL)
    {
        *infectados = this->infectados;
        todoOk = 1;
    }
    return todoOk;
}

int pais_setMuertos(ePais* this,int muertos)
{

    int todoOk = 0;

    if(this != NULL && muertos >=0)
    {
        this->muertos = muertos;
        todoOk = 1;
    }
    return todoOk;
}

int pais_getMuertos(ePais* this,int* muertos)
{
    int todoOk = 0;

    if(this != NULL && muertos != NULL)
    {
        *muertos = this->muertos;
        todoOk = 1;
    }
    return todoOk;
}

int cargarCsvPandemia(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = 0;
    int flag = 1;
    char id[1204];
    char nombre[1204];
    char recuperados[1000000];
    char infectados[1204];
    char muertos[1204];
    ePais* auxPais;
    FILE* pFile;

    pFile = fopen(path, "r");

    if(pFile != NULL)
    {

        if(pFile==NULL)
        {

            printf("No se pudo abrir el archivo\n");

        }


        while(!feof(pFile))
        {

            if(flag)
            {

                fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, recuperados, infectados, muertos);
                flag = 0;
            }
            fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id, nombre, recuperados, infectados, muertos);
            auxPais = pais_newParametros(id, nombre, recuperados, infectados, muertos);

            if(auxPais != NULL)
            {

                ll_add(pArrayListEmployee, auxPais);
                retorno = 1;

            }
        }
    }

    fclose(pFile);
    return retorno;
}

int mostrarPaisP(ePais* vec)
{
    int todoOk = 0;

    if( vec != NULL  )
    {
        todoOk = 1;
        printf("%4d %10s        %d            %d            %d\n", vec->id, vec->nombre, vec->recuperados, vec->infectados, vec->muertos);
    }
    return  todoOk;
}

int listarPais(LinkedList* pArrayListEmployee)
{
    int tam = ll_len(pArrayListEmployee);

    ePais* auxPais;
    printf("  Id    Nombre     Recuperados     Infectados        Muertos\n");
    if( pArrayListEmployee != NULL  )
    {
        for(int i= 0; i < tam; i++)
        {
            auxPais = (ePais*) ll_get(pArrayListEmployee, i);

            if( auxPais != NULL)
            {
                mostrarPaisP(auxPais);
            }
        }
    }

    return 1;
}
