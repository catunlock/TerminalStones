/*
 * File:   nivel.h
 * Author: xaloc
 *
 * Created on 6 de abril de 2012, 11:27
 */

#ifndef NIVEL_H
#define	NIVEL_H

#include "global.h"
#include "timer.h"
#include "diamante.h"
#include "piedra.h"

#define NIVEL_FILAS 25
#define NIVEL_COLUMNAS 60

typedef struct
{
    char caracteres[NIVEL_FILAS][NIVEL_COLUMNAS+1];
    Punt posicioInicial; // On comença el player
    Punt posicioSortida; // On esta la surtida
    int puntosPorGanar;  // Quants punts li donan per superar el nivell
    Diamantes diamantes; // Diamants del nivell
    Piedras piedras;     // Pedres del nivell
    int numero_nivel;    // En quin nivell esta.
} Nivel;

int cargaNivel(int n_nivel, Nivel *nivel);
void copiarNivel(Nivel *nivel_origen);
int moverPiedras(Piedras *piedras, struct Tiempo *timer);
void liberaNivel(Nivel *nivel);
#endif	/* NIVEL_H */

