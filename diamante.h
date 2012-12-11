#ifndef DIAMANTE_H_INCLUDED
#define DIAMANTE_H_INCLUDED

#include "global.h"
#include "timer.h"

typedef struct
{
    Punt posicion;
    int  eliminado; //bool eliminado
} Lista_Diamantes;

typedef struct
{
    int elementos;
    int elementos_necesarios;
    Lista_Diamantes *lista;
} Diamantes;

int moverDiamantes(Diamantes *diamantes, struct Tiempo *timer);
int busca_id_diamant(Lista_Diamantes *l_diamantes, int f, int c);
int moverDiamantes(Diamantes *diamantes, struct Tiempo *time);

#endif // DIAMANTE_H_INCLUDED
