#include "player.h"

#include <stdio.h>
#include <ncurses.h>

long unsigned int elementos_intraspasables[] = { LIMITE, //Aquests ints sels i fan un "or" perque els guarda amb color i tot per aixi poder detectar si a colisionat o no, per exemple una X verde es diferent de una X vermella.
        PEDRA,
        PARED,
        SALIDA,
        '\0'
                                               };

int movimientoPosible(int f, int c)
{
    int posible = 1;
    int i = 0;
    long unsigned int chache;

    chache = mvinch(f,c); //Agafa el caracter que hi havia en aquesta posicio a la pantalla

    while(elementos_intraspasables[i] != '\0')
    {
        if(chache == elementos_intraspasables[i])
        {
            posible = 0;
        }
        i++;
    }

    return posible;
}

void eliminarPlayer(Player *player)
{

    mvaddch(player->posicio.fila, player->posicio.columna, ' ');
}

void setPlayer(Player *player)
{

    mvaddch(player->posicio.fila, player->posicio.columna, player->caracter);
}

int movePlayer(Player *player, int direccion, Nivel *nivel)
{
    int mover = 1;
    int temp_f = player->posicio.fila;
    int temp_c = player->posicio.columna;
    int resultat = 0;

    if(direccion == KEY_UP)
    {
        temp_f--;
    }
    else if(direccion == KEY_DOWN)
    {
        temp_f++;
    }
    else if(direccion == KEY_LEFT)
    {
        temp_c--;
    }
    else if(direccion == KEY_RIGHT)
    {
        temp_c++;
    }
    else
    {
        mover = 0;
    }

    if(mover && movimientoPosible(temp_f, temp_c))
    {

        eliminarPlayer(player);

        player->posicio.fila = temp_f;
        player->posicio.columna = temp_c;

        player->caracter_recogido = mvinch(player->posicio.fila, player->posicio.columna);

        setPlayer(player);

        resultat = comprobarObjetoRecogido(player, nivel);
    }

    return resultat;
}

/**
 * Comprueba el objeto que ha recogido el jugador.
 * @param player
 * @return Siempre retorna 0, excepto, cuando el jugador llega al final con la puerta abierta, entonces retorna 1.
 */
int comprobarObjetoRecogido(Player *player, Nivel *nivel)
{

    int ganado = 0;
    int id_diamante;

    if( player->caracter_recogido == (DIAMANT) )
    {
        player->diamantes_totales++;
        player->diamantes_nivel++;
        player->puntos += 1000;

        //Buscar que diamante le toca i ponerlo como cogido.
        id_diamante = busca_id_diamant(nivel->diamantes.lista, player->posicio.fila, player->posicio.columna);
        nivel->diamantes.lista[id_diamante].eliminado = 1;

        if(player->diamantes_totales >= nivel->diamantes.elementos_necesarios)
        {
            mvaddch(nivel->posicioSortida.fila, nivel->posicioSortida.columna, SALIDA_ABIERTA);
        }
    }
    else if (player->caracter_recogido == (TERRA) )
    {
        player->puntos += 50;
    }
    else if (player->caracter_recogido == (SALIDA_ABIERTA) )
    {
        player->puntos += nivel->puntosPorGanar;
        ganado = 1;
    }

    player->caracter_recogido = ' ';

    return ganado;
}

void reset_pos_InicioNivel(Player *player, Nivel *nivel)
{

    eliminarPlayer(player);

    player->posicio.fila = nivel->posicioInicial.fila;
    player->posicio.columna = nivel->posicioInicial.columna;

    setPlayer(player);
}

void inicializaPlayer(Player *player, Nivel *nivel)
{

    player->caracter = PLAYER;
    player->posicio.fila = nivel->posicioInicial.fila;
    player->posicio.columna = nivel->posicioInicial.columna;
    player->caracter_recogido = 0; // nivelActual.caracteres[nivelActual.posicioInicial.fila][nivelActual.posicioInicial.columna]
    player->diamantes_totales = 0;
    player->diamantes_nivel = 0;
    player->puntos = 0;
    player->vidas = VIDAS;

    setPlayer(player);
}
