#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>

// Cabecera de la heurística que se tiene que usar en el nivel 2.
// Tiene 3 entradas que son la ubicación del jugador, del colaborador y la de la casilla destino.
double HeuristicaParaElNivel2(const ubicacion &jugador, const ubicacion &colaborador, const ubicacion &final){
	double d1 = abs(colaborador.f - final.f) + abs(colaborador.c - final.c);
	double d2 = abs(jugador.f - colaborador.f) + abs(jugador.c - colaborador.c);
	double d3 = 8 - (int) colaborador.brujula;

	if (d1 == 0) 
		return d1;
	else
		return (d1*d1*8) + d3 + d2;
}

// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;

	// Incluir aquí el comportamiento del agente jugador

	return accion;
}


int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
