#ifndef GRAFICO_H_INCLUDED
#define GRAFICO_H_INCLUDED

#include "nivel.h"
#include "player.h"

void dibujaPanelLateral(Nivel *nivel, Player *jugador, struct Tiempo *t_nivel);
void mostrar_instrucciones();

void printCentrado(int linea, char cadena[], int formato);
int mensajeBox(const char *titulo, const char *mensaje);
void fullscreen_message(const char *mensaje, int formato);

#endif // GRAFICO_H_INCLUDED