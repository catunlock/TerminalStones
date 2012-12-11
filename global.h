#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#define VERSION "Term Stones v0.1"

#define JOC_CLOCK 200 //Indica els microsegons que cal esperar entre accio i accio.

#define COLOR_TIERRA        1
#define COLOR_LIMITE        2
#define COLOR_PIEDRA        3
#define COLOR_PARED         4
#define COLOR_DIAMANTE      5
#define COLOR_PLAYER        6
#define COLOR_SALIDA        7
#define COLOR_TITULO        8

#define COLOR_PERDER        10
#define COLOR_GANAR         11

#define PEDRA   'O' | COLOR_PAIR(COLOR_PIEDRA) | A_BOLD
#define DIAMANT 'V'| COLOR_PAIR(COLOR_DIAMANTE) | A_BOLD
#define PLAYER '@'| COLOR_PAIR(COLOR_PLAYER)
#define TERRA   '.' | COLOR_PAIR(COLOR_TIERRA)
#define LIMITE 'X' |  COLOR_PAIR(COLOR_LIMITE)
#define PARED '#' | COLOR_PAIR(COLOR_PARED)
#define SALIDA 'D' | COLOR_PAIR(COLOR_SALIDA)
#define SALIDA_ABIERTA 'C' | COLOR_PAIR(COLOR_SALIDA)

typedef struct
{
    int fila;
    int columna;
} Punt;

#endif // GLOBAL_H_INCLUDED
