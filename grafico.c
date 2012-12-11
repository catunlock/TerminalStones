#include "grafico.h"
#include "global.h"

#include <ncurses.h>
#include <string.h>

void fullscreen_message(const char *mensaje, int formato)
{

    int pos_x = getmaxy(stdscr)/2 -1;
    int pos_y = (getmaxx(stdscr)- strlen(mensaje) ) / 2;

    clear();

    attron( formato );
    mvprintw( pos_x, pos_y, mensaje);
    attroff( formato );

    refresh();
}

void printCentrado(int linea, char cadena[], int formato)
{
    int pos_x = (80- strlen(cadena) ) / 2;

    attron( formato );
    mvprintw( linea, pos_x, "%s", cadena);
    attroff( formato );
}

void printLateral(int linea, char cadena[], int formato)
{

    int longi = (20- strlen(cadena) ) / 2;

    attron( formato );
    mvprintw( linea, 60 + longi, "%s", cadena);
    attroff( formato );
}

void mostrar_instrucciones()
{

    int formato = A_BOLD | COLOR_PAIR(COLOR_GANAR);

    printCentrado(3, "Term Stones es un juego inspirado en gnome-stones.", formato);

    printCentrado(5, "El jugador esta representado en el mapa por una @.", formato);
    printCentrado(6, "lo encontraras abajo a la izquiera, el fondo de la mina", formato);
    printCentrado(7, "Para abrite paso por el mapa usa las teclas de direccion ^ < > v", formato);

    printCentrado(9, "Si te cae una piedra encima tuyo moriras, pero no te preocupes tienes 3 vidas.", formato);
    printCentrado(10, "Puedes bloquear las piedras, pero en cuanto te apartes caera.", formato);
    printCentrado(11, "Tambien puedes provocar desprendimientos si apartas tierra o cojes un diamante.", formato);

    printCentrado(13, "La salida se representa por una D si esta cerrada i por una C si esta abierta", formato);
    printCentrado(14, "Para conseguir abrirla debes recojer los diamantes necesarios del mapa.", formato);
    printCentrado(15, "Los diamantes en el mapa estan representados con una V.", formato);

    printCentrado(17, "Tambien tienes un Crono con el que medir tu tiempo en los mapas.", formato);

    formato =  COLOR_PAIR(COLOR_DIAMANTE) | A_BOLD;
    printCentrado(19, "Volver", formato);

    refresh();
    getch();
}

void dibujaPanelLateral(Nivel *nivel, Player *jugador, struct Tiempo *t_nivel)
{
    char cadena[20];
    int formato;
// -------------------PLAYER -----------------------------------
    formato = A_BOLD | COLOR_PAIR(COLOR_GANAR);

    printLateral(1, VERSION, formato);

    printLateral(2, "____________________", formato);
    printLateral(3, "PLAYER", formato);
    printLateral(4, "====================", formato);

    sprintf(cadena, "Vidas: %d", jugador->vidas);
    printLateral(5, cadena, formato);

    sprintf(cadena, "F:%2d C:%2d", jugador->posicio.fila, jugador->posicio.columna);
    printLateral(6, cadena, formato);

    sprintf(cadena, "Puntos:    %07d", jugador->puntos);
    printLateral(7, cadena, formato);

    sprintf(cadena, "Diamantes: %07d", jugador->diamantes_totales);
    printLateral(8, cadena, formato);

    printLateral(9, "____________________", formato);

// -------------------NIVEL -----------------------------------

    formato = A_BOLD | COLOR_PAIR(COLOR_DIAMANTE);

    printLateral(10, "____________________", formato);

    sprintf(cadena, "NIVEL: %02d", nivel->numero_nivel);
    printLateral(12, cadena, formato);

    printLateral(13, "====================", formato);

    sprintf(cadena, "Diamantes:     %03d", nivel->diamantes.elementos);
    printLateral(14, cadena, formato);

    sprintf(cadena, "Necesarios:    %03d", nivel->diamantes.elementos_necesarios);
    printLateral(15, cadena, formato);

    sprintf(cadena, "Cogidos:       %03d", jugador->diamantes_nivel);
    printLateral(16, cadena, formato);
// ------------------TIME-------------------------------------------

    formato = A_BOLD;

    printLateral(17, "____________________", formato);
    printLateral(18, "RELOG", formato);
    printLateral(19, "====================", formato);

    struct Formato_tiempo f_tiempo;

    formatear_tiempo(time_elapsed(t_nivel), &f_tiempo);

    sprintf(cadena, "%02d:%02d:%02d elapsed", f_tiempo.minutos, f_tiempo.segundos, f_tiempo.decisegundos);
    printLateral(20, cadena, formato);

}


void setTitulo(const char *mensaje)
{

    int l_mensaje = strlen(mensaje);

    int pos_ini_f = 0; //Fila inicial
    int pos_ini_c = (NIVEL_COLUMNAS - l_mensaje ) / 2; //Columna inicial

    attron( COLOR_PAIR(COLOR_TITULO) );
    mvprintw( pos_ini_f, pos_ini_c , "%s", mensaje);
    attroff( COLOR_PAIR(COLOR_TITULO) );
}

void limpiarTitulo()
{

    int i;

    for(i=0; i<NIVEL_COLUMNAS; i++)
    {
        mvaddch(0, i, LIMITE);
    }
}

/**
 * Pausa el juego i muestra un mensaje en pantalla con el titulo en la parte superior
 * @return Retorna , si la respuesta es afirmativa, -1 si es negativa.
 */
int mensajeBox(const char *titulo, const char *mensaje)
{


    int resultat=1, ch;
    int i,j;

    chtype screen_dump[100][100];

    int l_mensaje = strlen(mensaje);

    int pos_msg_f = getmaxy(stdscr)/2 -1;
    int pos_msg_c = (NIVEL_COLUMNAS - l_mensaje ) / 2;

    int pos_ini_f = pos_msg_f - 1; //Fila inicial
    int pos_ini_c = pos_msg_c - 1; //Columna inicial

    int pos_final_f = pos_ini_f + 2;
    int pos_final_c = pos_ini_c + l_mensaje + 1;


    //Copia al buffer de backup el trozo de ventara que trabajaremos.
    for(i = pos_ini_f; i <= pos_final_f; i++)
    {
        for(j = pos_ini_c; j <= pos_final_c; j++)
        {
            screen_dump[i][j] = mvinch(i,j);
        }
    }

    //Pinta de negro el trozo donde imprimira el mensaje
    for(i = pos_ini_f; i <= pos_final_f; i++)
    {
        for(j = pos_ini_c; j <= pos_final_c; j++)
        {
            mvaddch(i,j, ' ' );
        }
    }

    setTitulo(titulo);
    mvprintw(pos_msg_f , pos_msg_c, mensaje);

    timeout(-1);

    do
    {
        ch = getch();
    }
    while(ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT);

    timeout(JOC_CLOCK);

    if(ch == 'N' || ch == 'n')
    {
        resultat = -1;
    }

    //Restaura del backup del trozo de ventana que hemos chafado
    for(i = pos_ini_f; i <= pos_final_f; i++)
    {
        for(j = pos_ini_c; j <= pos_final_c; j++)
        {
            mvaddch(i,j, screen_dump[i][j]);
        }
    }

    limpiarTitulo();

    refresh();

    return resultat;
}
