#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <sys/timeb.h>
#include "global.h"

struct Tiempo
{
    long unsigned int t_anterior;
    long unsigned int t_actual;
    int primeraVegada;
};

struct Formato_tiempo
{
    int minutos;
    int segundos;
    int decisegundos;
};

void formatear_tiempo(long unsigned int tiempo, struct Formato_tiempo *tiempo_f);
long unsigned int time_elapsed(struct Tiempo *t_inicio);
long unsigned int time_in_miliseconds();
int timer(struct Tiempo *tiempo);



#endif // TIMER_H_INCLUDED
