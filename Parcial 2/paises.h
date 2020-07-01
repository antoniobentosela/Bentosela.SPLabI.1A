#include "LinkedList.h"

#ifndef PAISES_H_INCLUDED
#define PAISES_H_INCLUDED

typedef struct
{
    int id;
    char nombre [20];
    int recuperados;
    int infectados;
    int muertos;

}ePais;

#endif // PAISES_H_INCLUDED

ePais* pais_new();
ePais* new_PaisParam(int id, char* nombre, int recuperados, int infectados, int muertos);
ePais* pais_newParametros(char* idStr,char* nombreStr,char* recuperadosStr, char* infectados, char* muertos);
int mostrarPaisP(ePais* vec);
int listarPais(LinkedList* pArrayListEmployee);
int cargarCsvPandemia(char* path, LinkedList* pArrayListEmployee);
int pais_setId(ePais* this,int id);
int pais_getId(ePais* this,int* id);
int pais_setNombre(ePais* this,char* nombre);
int pais_getNombre(ePais* this,char* nombre);
int pais_setRecuperados(ePais* this,int  recuperados);
int pais_getRecuperados(ePais* this,int* recuperados);
int pais_setInfectados(ePais* this,int infectados);
int pais_getInfectados(ePais* this,int* infectados);
int pais_setMuertos(ePais* this,int muertos);
int pais_getMuertos(ePais* this,int* muertos);
