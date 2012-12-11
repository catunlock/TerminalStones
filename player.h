/*
 * File:   player.h
 * Author: xaloc
 *
 * Created on 6 de abril de 2012, 18:02
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "nivel.h"
#include "global.h"

#define VIDAS 2

typedef struct
{
    int caracter;
    Punt posicio;
    int caracter_recogido; //Sirve para almecenar el caracter que havia antes en el mapa de que el player se pusiera encima
    unsigned int diamantes_totales;
    unsigned int diamantes_nivel;
    unsigned int puntos;
    int vidas;
} Player;

void reset_pos_InicioNivel(Player *player, Nivel *nivel);

int movePlayer(Player *player, int direccion, Nivel *nivel);

int comprobarObjetoRecogido(Player *player, Nivel *nivel);

void inicializaPlayer(Player *player, Nivel *nivel);


#endif	/* PLAYER_H */

