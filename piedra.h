#ifndef PIEDRA_H_INCLUDED
#define PIEDRA_H_INCLUDED

#include "global.h"

#define D_IZQUIERDA 1
#define D_DERECHA   2

typedef struct
{
    Punt posicion;
    int  segunda_oportunidad; //bool eliminado
    int direccion; // Indica hacia que direccion tienen la inercia si hacia la izquierda o hacia la derecha.
} Lista_Piedras;

typedef struct
{
    Lista_Piedras *lista;
    int elementos;
} Piedras;

#endif // PIEDRA_H_INCLUDED
