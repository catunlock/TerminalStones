#include "timer.h"

void formatear_tiempo(long unsigned int tiempo, struct Formato_tiempo *tiempo_f)
{

    tiempo_f->decisegundos = (tiempo /10)%100;
    tiempo_f->segundos = (tiempo /1000)%60;
    tiempo_f->minutos = (tiempo /1000)/60;
}

long unsigned int time_in_miliseconds()
{
    struct timeb ahora;
    long unsigned int milisegundos=0;

    if( ftime(&ahora) == 0 )
    {
        milisegundos = (ahora.time * 1000) + ahora.millitm;
    }
    return milisegundos;
}

long unsigned int time_elapsed(struct Tiempo *t_inicio)
{
    t_inicio->t_actual = time_in_miliseconds();

    return t_inicio->t_actual - t_inicio->t_anterior;
}

int timer(struct Tiempo *tiempo)
{
    int resultat = 0;

    if(tiempo->primeraVegada)
    {
        tiempo->t_anterior = time_in_miliseconds();
        tiempo->primeraVegada = 0;
    }
    else
    {
        tiempo->t_actual = time_in_miliseconds();

        if(tiempo->t_actual > (tiempo->t_anterior + JOC_CLOCK) )
        {
            resultat = 1;
//			mvprintw(10, 60, "SI TOCA");
            tiempo->t_anterior = tiempo->t_actual;
        }
        else
        {
//			mvprintw(10, 60, "NO TOCA");
        }
    }

    return resultat;
}
