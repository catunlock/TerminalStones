#include "diamante.h"

#include "nivel.h"

#include <ncurses.h>

/**Funcio que s'encarrega de dir quan ha pasat el temps suficient  per ejecutar una altra funcio.
    @arg Indica els microsegons que cal esperar.
    @return retorna 1 si ya ha pasat el temps, retorna 0 si encara no ha pasat el temps.
*/
int busca_id_diamant(Lista_Diamantes *l_diamantes, int f, int c)
{
    int i=0;
    while(l_diamantes[i].posicion.fila != f || l_diamantes[i].posicion.columna != c)
    {
        i++;
    }
    return i;
}

void mostrarDiamantesAlmacenados(Nivel *nivel)
{
    int i = 0;

    Lista_Diamantes *l_diamantes = nivel->diamantes.lista;

    for(i=0; i < nivel->diamantes.elementos; i++)
    {
        printw("Piedra Almacenada (%d): F:%d C:%d = %c\n", i,
               l_diamantes[i].posicion.fila,
               l_diamantes[i].posicion.columna,
               nivel->caracteres[l_diamantes[i].posicion.fila][l_diamantes[i].posicion.columna]
              );
    }
}

int moverDiamantes(Diamantes *diamantes, struct Tiempo *time)
{
    int i = 0;
    chtype debajo;
    int resultat = 0;

    int n_elements = diamantes->elementos;
    Lista_Diamantes *elementos = diamantes->lista;

    if( timer(time) )
    {
        for(i=0; i<n_elements; i++)
        {
            if(elementos[i].eliminado != 1)
            {
                debajo  = mvinch(elementos[i].posicion.fila +1, elementos[i].posicion.columna);

                if( debajo == ' ') //Comproba si esta flotant
                {
                    mvaddch(elementos[i].posicion.fila, elementos[i].posicion.columna, ' '); //Imprimeix un espai en blanc on estaba abans, perque ha començat a caure.
                    elementos[i].posicion.fila +=1; //Li indiquem al diamant que ara esta una posicio mes baixa.
                    mvaddch(elementos[i].posicion.fila, elementos[i].posicion.columna, DIAMANT); //Imprimeix el diamant on li toca.
                }
            }

        }

    }
    return resultat;
}
