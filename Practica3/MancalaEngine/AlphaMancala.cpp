/*
 * AlphaMancala.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: Antonio Heredia Castillo
 */

#include "AlphaMancala.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <limist.h>
using namespace std;

AlphaMancala::AlphaMancala() {
	// Inicializar las variables necesarias para ejecutar la partida

}

AlphaMancala::~AlphaMancala() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void AlphaMancala::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string AlphaMancala::getName() {
	return "AlphaMancala"; // Sustituir por el nombre del bot
}

Move AlphaMancala::nextMove(const vector<Move> &adversary, const GameState &state) {

	

	Player turno= this->getPlayer();
	Player contrincante;
	

	long timeout= this->getTimeOut();

	Move movimiento= M_NONE;


	int puntos= -10000;

	
	// Recorremos los 6 movimientos posibles
	/*
		for (int i= 1; i<=6; i++) {

			// Comprobamos si hay semillas en la casilla i
			if (state.getSeedsAt(turno, (Position) i) >0) {

				// Si las hay, intentamos ver cómo queda el tablero si
				// hacemos el movimiento de la casilla i
				GameState hijo= state.simulateMove( (Move) i);

				// Si nos da más puntos de los que tenemos
				// con respecto al contrario, lo hacemos
				if (hijo.getScore(turno) > puntos) {
					puntos= hijo.getScore(turno);
					movimiento= (Move) i;

				// O si nos da los mismos puntos pero tiramos de nuevo,
				// cogemos el movimiento i
				} else if (hijo.getScore(turno) == puntos) {
					if (hijo.getCurrentPlayer() == turno)
						movimiento= (Move)i;
				}
			}

		}
	*/
	int alfa = -50;
	int beta = 50;
	return max(adversary,state, alfa, beta,0).first;

}



pair<Move,int> AlphaMancala::max(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int & alfa, int & beta, int profundidad){
	//if(state.getScore(jugador)>25){
	if(profundidad == 7){
		pair<Move,int> devolver;
		devolver.first = mejor_accion;
		devolver.second = mayor_valor;
		return devolver;
	}else{
		int mayor_valor = INT_MIN;
		Move mejor_accion;
		for(int i=0; i<7;i++){
			//Para ver si es un movimiento valido
			if (state.getSeedsAt(jugador, (Position) i) >0) {

			//Calculamos el estado de realizar este movimiento
			GameState hijo= state.simulateMove( (Move) i);
			pair<Move,int> resultado = min(adversary,hijo,jugador,alfa,beta)
			if(mayor_valor<resultado.second){
				mayor_valor = resultado.second;
				mejor_accion = resultado.first;
			}
			if(mayor_valor >= beta){
				pair<Move,int> devolver;
				devolver.first = mejor_accion;
				devolver.second = mayor_valor;
				return devolver;
			}
			if(mayor_valor > alfa){
				alfa = mayor_valor;
			}
			/*
			// Si nos da más puntos de los que tenemos
			// con respecto al contrario, lo hacemos
			if (hijo.getScore(jugador) > puntos) {
				puntos= hijo.getScore(jugador);
				movimiento= (Move) i;

			// O si nos da los mismos puntos pero tiramos de nuevo,
			// cogemos el movimiento i
			} else if (hijo.getScore(jugador) == puntos) {
				if (hijo.getCurrentPlayer() == jugador)
					movimiento= (Move)i;
			}
			*/
			
			}
		}
	}
	pair<Move,int> devolver;
	devolver.first = mejor_accion;
	devolver.second = mayor_valor;
	return devolver; 
}

pair<Move,int> AlphaMancala::min(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int & alfa, int & beta, int profundidad){
	if(profundidad == 7){

	}
}