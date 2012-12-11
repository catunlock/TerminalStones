#include "piedra.h"

#include "nivel.h"

#include <ncurses.h>

void mostrarPiedrasAlmacenadas(Nivel *nivel)
{
    int i = 0;

    Lista_Piedras *l_piedras = nivel->piedras.lista;

    for(i=0; i < nivel->piedras.elementos; i++)
    {
        printw("Piedra Almacenada (%d): F:%d C:%d = %c\n", i,
               l_piedras[i].posicion.fila,
               l_piedras[i].posicion.columna,
               nivel->caracteres[l_piedras[i].posicion.fila][l_piedras[i].posicion.columna]
              );
    }
}

/**
 Mueve las piedras que hay en la pantalla, les aplica la fisica,
 @return retorna 0 si no ha pasado nada al mover las piedras. retorna 1 si ha chafado al player.
 */
int moverPiedras(Piedras *piedras, struct Tiempo *time)
{
    int i = 0;
    int resultado = 0;
    int mover = 0;
    chtype debajo;

    int temp_f, temp_c;
    int n_elements = piedras->elementos;
    Lista_Piedras *elementos = piedras->lista;


    if( timer(time) ) //Si es hora de fer baixar les pedres
    {
        for(i=0; i<n_elements; i++) //Bucle que recorre les pedres
        {
            mover = 0;
            temp_f = elementos[i].posicion.fila;
            temp_c = elementos[i].posicion.columna;

            debajo  = mvinch(elementos[i].posicion.fila +1, elementos[i].posicion.columna); //Obte el caracter que hi ha asota

            if( debajo == ' ') //Comproba si esta flotant
            {
                mover = 1;
                elementos[i].posicion.fila +=1; //Li indiquem al pedra que ara esta una posicio mes baixa.

            }
            else if( debajo == (PEDRA) )
            {

                chtype lateral_izquierdo = mvinch(elementos[i].posicion.fila, elementos[i].posicion.columna-1);
                chtype lateral_derecho   = mvinch(elementos[i].posicion.fila, elementos[i].posicion.columna+1);

                if(lateral_izquierdo == ' ' &&  lateral_derecho == ' ') //No hi ha res al seu voltant.
                {
                    mover = 1;

                    if(elementos[i].direccion == D_IZQUIERDA)
                    {
                        elementos[i].posicion.columna -=1; //La movem una posicio a la esquerra
                    }
                    else if (elementos[i].direccion == D_DERECHA)
                    {
                        elementos[i].posicion.columna +=1; // La movem una posicio a la dreta.
                    }
                    else // elementos[i].direccion == 0
                    {
                        elementos[i].direccion = (rand()%2)+1; // decidim aleatoriament per quin costat caura.
                    }

                }
                else if(lateral_izquierdo == ' ' && (elementos[i].direccion == 0 || elementos[i].direccion == D_IZQUIERDA) )
                {
                    mover = 1;
                    elementos[i].direccion = D_IZQUIERDA;
                    elementos[i].posicion.columna -=1;
                }
                else if(lateral_derecho == ' ' && (elementos[i].direccion == 0 || elementos[i].direccion == D_DERECHA) )
                {
                    mover = 1;
                    elementos[i].direccion = D_DERECHA;
                    elementos[i].posicion.columna +=1;
                }
            }
            else if( debajo == (PLAYER) )       //Si el player esta asota
            {
                if(elementos[i].segunda_oportunidad)  //Te una oportunitat de sortir corrents
                {
                    elementos[i].segunda_oportunidad = 0; //Li resto una oportunitat, ara no en te cap.
                }
                else
                {
                    resultado = 1; //Si encara estaba asota perd.
                }
            }
            else  //Si ya no esta asota
            {
                if(elementos[i].segunda_oportunidad == 0)  // i no te cap oportunitat
                {
                    elementos[i].segunda_oportunidad = 1; //li torno a dornar una altra oportunitat per quan torni a pasar per sota.
                }
            }

            if(mover)
            {
                mvaddch(temp_f, temp_c, ' '); //Imprimeix un espai en blanc on estaba abans, perque ha començat a caure.
                mvaddch(elementos[i].posicion.fila, elementos[i].posicion.columna, PEDRA); //Imprimeix el pedra on li toca.

            }

        }

    }
    return resultado;
}