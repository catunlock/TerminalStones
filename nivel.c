#include "nivel.h"

#include "global.h"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int cargaNivel(int n_nivel, Nivel *nivel)
{

    int error = 1;

    char ruta_nivel[255];
    FILE *f_niveles;

    sprintf(ruta_nivel, "nivel%d.txt", n_nivel);
    printw("Cargando nivel: %s\n", ruta_nivel);

    f_niveles = fopen(ruta_nivel, "r");

    if(f_niveles != NULL)
    {

        int i = 0;

        void *mas_piedras;

        nivel->numero_nivel = n_nivel;

        nivel->piedras.lista = NULL;
        nivel->piedras.elementos = 0;



        nivel->diamantes.lista = NULL;
        nivel->diamantes.elementos = 0;
        void *mas_diamantes;

        fscanf(f_niveles,"posInicial_x = %4d", &nivel->posicioInicial.fila);
        fgetc(f_niveles); //Obtenemos el final de linea
        fscanf(f_niveles,"posInicial_y = %4d", &nivel->posicioInicial.columna);
        fgetc(f_niveles); //Obtenemos el final de linea
        fscanf(f_niveles,"diamantes_necesarios = %4d", &nivel->diamantes.elementos_necesarios);
        fgetc(f_niveles); //Obtenemos el final de linea
        fscanf(f_niveles,"posSalida_x = %4d", &nivel->posicioSortida.fila);
        fgetc(f_niveles); //Obtenemos el final de linea
        fscanf(f_niveles,"posSalida_y = %4d", &nivel->posicioSortida.columna);
        fgetc(f_niveles); //Obtenemos el final de linea
        fscanf(f_niveles,"puntosPorGanar = %4d", &nivel->puntosPorGanar);
        fgetc(f_niveles); //Obtenemos el final de linea


        printw("Posicion Inicial: X:%d Y:%d\n", nivel->posicioInicial.fila, nivel->posicioInicial.columna);

        while( !feof(f_niveles) )
        {
            fgets(nivel->caracteres[i], NIVEL_COLUMNAS + 1, f_niveles);
            fgetc(f_niveles); //Obtenemos el final de linea

            printw("Leido %d: %s\n", i, nivel->caracteres[i]);

            int j = 0;
            while(j<=NIVEL_COLUMNAS+1)
            {

                if(nivel->caracteres[i][j] == 'O')  //Es una pedra.
                {
                    printw("Piedra leida en la posicion: X:%d, Y:%d\n", i, j);
                    nivel->piedras.elementos++;

                    mas_piedras = realloc(nivel->piedras.lista, sizeof(Lista_Piedras) * (nivel->piedras.elementos) );

                    if(mas_piedras != NULL)
                    {
                        nivel->piedras.lista = mas_piedras;
                        nivel->piedras.lista[nivel->piedras.elementos-1].posicion.fila = i;
                        nivel->piedras.lista[nivel->piedras.elementos-1].posicion.columna = j;
                        nivel->piedras.lista[nivel->piedras.elementos-1].segunda_oportunidad = 1;
                        nivel->piedras.lista[nivel->piedras.elementos-1].direccion = 0;
                    }
                    else
                    {
                        free(nivel->piedras.lista);
                        printw("Error rehahuecando memoria para las piedras.\n");
                        exit(1);
                    }
                }

                if(nivel->caracteres[i][j] == 'V')  //Es un diamant.
                {
                    printw("Diamante leido en la posicion: X:%d, Y:%d\n", i, j);
                    nivel->diamantes.elementos++; // A1 - Al detectar el diamante se incrementa la cantidad ahora para que el realloc funcione correctamente.

                    mas_diamantes = realloc(nivel->diamantes.lista, sizeof(Lista_Diamantes) * nivel->diamantes.elementos);

                    if(mas_diamantes != NULL)
                    {
                        nivel->diamantes.lista = mas_diamantes;
                        nivel->diamantes.lista[nivel->diamantes.elementos-1].posicion.fila = i; //Ver A1 + y aqui le restamos 1 para que empieze en la posicion 0 del array.
                        nivel->diamantes.lista[nivel->diamantes.elementos-1].posicion.columna = j;
                        nivel->diamantes.lista[nivel->diamantes.elementos-1].eliminado = 0;
                    }
                    else
                    {
                        free(nivel->piedras.lista);
                        printw("Error rehahuecando memoria para los diamantes.\n");
                        exit(1);
                    }
                }

                j++;
            }

            i++;
        }

        fclose(f_niveles);
        error = 0;
    }

    mostrarDiamantesAlmacenados(nivel);
    mostrarPiedrasAlmacenadas(nivel);


    return error;
}

void liberaNivel(Nivel *nivel)
{

    free(nivel->piedras.lista);
    free(nivel->diamantes.lista);
}

void copiarNivel(Nivel *nivel_origen)
{
    int i, j;
    int ch_nivel, ch;

    clear();

    for(i=0; i<NIVEL_FILAS; i++)
    {
        for(j=0; j<NIVEL_COLUMNAS; j++)
        {
            ch_nivel = nivel_origen->caracteres[i][j];

            switch(ch_nivel)
            {
            case '.':
                ch = TERRA;
                break;
            case 'X':
                ch = LIMITE;
                break;
            case 'O':
                ch = PEDRA;
                break;
            case '#':
                ch = PARED;
                break;
            case 'V':
                ch = DIAMANT;
                break;
            case '@':
                ch = PLAYER;
                break;
            case 'D':
                ch = SALIDA;
                break;
            default:
                break;
            }

            mvaddch(i, j, ch);

        }
    }
}
