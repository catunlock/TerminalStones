/*
 * File:   main.c
 * Author: Alberto Lopez Sanchez
 *
 * Created on 4 de abril de 2012, 10:43
 *
 NOMES FUNCIONA A LINUX o UNIX AMB TIPUS DE TERMINAL COMPATIBLE.

 * Aquet joc necesita per compilar les llibreries ncurses-dev i per executarse les ncurses,
 * es troban facilement al repositori de debian si no les tens ya instalades.
 * despres per que  compili al codeblocks hem de anar a settings -> compiler and debugger ->
 * pestanya linker settings -> i en l'apartat link libraries boto "add" -> escriure "ncurses"

 Per poder jugar adecuadament la terminal ha de estar configurada a 80x24, 80 columnas 24 filas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

#include "nivel.h"
#include "player.h"
#include "grafico.h"

#include "global.h"

void iniciar_curses();
void iniciar_juego(int numero);
int joc(Nivel *nivel, Player *jugador);
void gameover(int ganador);
int menu();

int main()
{

    int opcion;

    iniciar_curses();
    srand( time(NULL) );

    do
    {
        opcion = menu();

        switch(opcion)
        {
        case 1:
            iniciar_juego(1);
            break;
        case 2:
            mostrar_instrucciones();
            break;
        case 3:
            opcion = -1;
            break;
        }

    }
    while( opcion > 0);


    endwin();

    return 0;
}

int menu()
{

    int formato, opcion=1, tecla=0;

    clear();

    formato =  COLOR_PAIR(COLOR_PERDER) | A_BOLD;
    printCentrado(3, VERSION, formato);

    while( tecla != 13 )
    {

        if(tecla == KEY_UP)
        {

            opcion--;

            if(opcion<1)
            {
                opcion = 1;
            }

        }
        else if(tecla == KEY_DOWN)
        {

            opcion++;

            if(opcion>3)
            {
                opcion = 3;
            }
        }

        if(opcion == 1)
        {
            formato =  COLOR_PAIR(COLOR_DIAMANTE) | A_BOLD;
        }
        else
        {
            formato =  COLOR_PAIR(COLOR_GANAR) | A_BOLD;
        }
        printCentrado(7, "INICIAR", formato);

        if(opcion == 2)
        {
            formato =  COLOR_PAIR(COLOR_DIAMANTE) | A_BOLD;
        }
        else
        {
            formato =  COLOR_PAIR(COLOR_GANAR) | A_BOLD;
        }
        printCentrado(9, "Instrucciones", formato);

        if(opcion == 3)
        {
            formato =  COLOR_PAIR(COLOR_DIAMANTE) | A_BOLD;
        }
        else
        {
            formato =  COLOR_PAIR(COLOR_GANAR) | A_BOLD;
        }
        printCentrado(11, "Salir", formato);

        refresh();

        tecla = getch();

    }

    return opcion;
}

void iniciar_juego(int numero)
{

    Nivel nivel;
    Player jugador;

    int error;

    error = cargaNivel(numero, &nivel);

    if(!error)
    {
        copiarNivel(&nivel);
        inicializaPlayer(&jugador, &nivel);

        joc(&nivel, &jugador);

        liberaNivel(&nivel);

    }
    else
    {
        char mensaje[80];
        sprintf(mensaje, "Error al cargar el nivel: %03d", numero);
        fullscreen_message(mensaje, COLOR_PAIR(COLOR_PERDER));
        getch();
    }
}

void gameover(int ganador)
{

    if(ganador > 0)
    {
        fullscreen_message("Has ganado!!!", COLOR_PAIR(COLOR_GANAR) | A_BOLD | A_BLINK);
    }
    else
    {
        fullscreen_message("Has perdido", COLOR_PAIR(COLOR_PERDER) | A_BOLD);
    }

    getch();
}

int joc(Nivel *nivel, Player *jugador)
{

    int ch=0, ha_ganado=0, chafado=0;

    struct Tiempo time_nivel;
    struct Tiempo timer_piedras;
    struct Tiempo timer_diamantes;

    time_nivel.t_anterior = time_in_miliseconds();
    timer_diamantes.primeraVegada = 1;
    timer_piedras.primeraVegada = 1;

    timeout(JOC_CLOCK);//Li indico que apartir de aqui nomes esperi per llegir el teclat el temps especificat ala constant JOC_CLOCK

    while( ha_ganado==0 && jugador->vidas >= 0 && (ch != 'q' && ch != 'Q') )
    {
        ch = getch();

        ha_ganado = movePlayer(jugador, ch, nivel);

        chafado = moverPiedras(&nivel->piedras, &timer_piedras);

        moverDiamantes(&nivel->diamantes, &timer_diamantes);

        dibujaPanelLateral(nivel, jugador, &time_nivel);

        if(chafado)
        {

            jugador->vidas--; //Primero le quito la vida para hacer las comprobaciones

            if(jugador->vidas < 0)
            {
                ha_ganado = -1;
            }
            else
            {
                int continuar;

                continuar = mensajeBox("Deseas continuar (S/n)","Has sido chafado por una piedra");

                if(continuar < 0)
                {
                    jugador->vidas = -1;
                }

                jugador->puntos /= 2;
                reset_pos_InicioNivel(jugador, nivel);
            }

        }

        refresh();

    }

    timeout(-1);//Tornem a posar la entrada de teclat com estaba

    gameover(ha_ganado);

    return ha_ganado;

}

void iniciar_curses()
{

    initscr(); //Iniciamos la pantalla en modo ncurses
    //cbreak(); //Que no espere al enter para cojer el caracter
    raw();		//Pone la terminal en modo raw no hay buffer de entrada.
    noecho(); //No muestra por pantalla lo que escribimos por teclado
    //halfdelay();
    nonl(); //No ultilizar los \n para las nuevas lineas
    intrflush(stdscr, FALSE); //Indica que no limpie el buffer para antender las peticiones lo mas rapidamente posible. ya veremos si no me interesa mas ponerlo a TRUE.
    keypad(stdscr, TRUE); // Indica que podemos usar el teclado numerico.

    if(has_colors() == FALSE)
    {
        endwin();
        printf("La terminal no soporta colores.\n");
        exit(1);
    }
    else
    {
        start_color();

        init_pair(COLOR_TIERRA, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(COLOR_LIMITE, COLOR_WHITE, COLOR_WHITE);
        init_pair(COLOR_PIEDRA, COLOR_GREEN, COLOR_BLACK);
        init_pair(COLOR_PARED, COLOR_BLUE, COLOR_BLUE);
        init_pair(COLOR_DIAMANTE, COLOR_CYAN, COLOR_BLACK);
        init_pair(COLOR_PLAYER, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(COLOR_SALIDA, COLOR_WHITE, COLOR_RED);

        init_pair(COLOR_TITULO, COLOR_WHITE, COLOR_RED);

        init_pair(COLOR_GANAR, COLOR_YELLOW, COLOR_BLACK);
        init_pair(COLOR_PERDER, COLOR_RED, COLOR_BLACK);

    }

    clear();
    refresh();

}



