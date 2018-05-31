/*
 * AlphaMancala.cpp
 *
 *      Author: Antonio Heredia Castillo
 */

#include "AlphaMancala.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <limits.h>


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


	int alfa = INT_MIN;
	int beta = INT_MAX;

	max(adversary,state, turno, alfa, beta,0, movimiento);
	return  movimiento;

}



int AlphaMancala::max(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad, Move & movimiento){
	//if(state.getScore(jugador)>25){
 	int v = INT_MIN;

	if(profundidad > 8){

		return state.getScore(jugador);
	}else{

		for(int i=1; i<=6;i++){
				//cerr<< i << endl;

			//Para ver si es un movimiento valido
			if (state.getSeedsAt(jugador, (Position) i) >0) {

				//Calculamos el estado de realizar este movimiento
				GameState hijo= state.simulateMove( (Move) i);
				int resultado = 0;
				if(hijo.getCurrentPlayer() == jugador){
					resultado = max(adversary,hijo,jugador,alfa,beta,profundidad+1, movimiento);
				}else{
					resultado = min(adversary,hijo,jugador,alfa,beta,profundidad+1, movimiento);
				}
				
				
				if(resultado>v){
					v = resultado;
					movimiento = (Move) i;
				}
				if(v>=beta){
					movimiento = (Move) i;
					return v;
				}
				alfa = (v>alfa) ? v : alfa;
			}
		}
	}

	
	return v; 
}

int AlphaMancala::min(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad, Move & movimiento){
	int v = INT_MAX;

	if(profundidad >8){
		return state.getScore(jugador);
	}else{

		for(int i=1; i<=6;i++){
				
			if (state.getSeedsAt(jugador, (Position) i) >0) {

				//Calculamos el estado de realizar este movimiento
				GameState hijo = state.simulateMove( (Move) i);
				int resultado;
				if(hijo.getCurrentPlayer() == jugador){
					resultado = min(adversary,hijo,jugador,alfa,beta,profundidad+1, movimiento);
				}else
					resultado = max(adversary,hijo,jugador,alfa,beta,profundidad+1, movimiento);

			
				v = (v > resultado) ? resultado : v;
				if(resultado<v){
					v = resultado;
					movimiento = (Move) i;
				}
				if(v<=alfa){
					movimiento = (Move) i;
					return v;
				}
				beta = (v>beta) ? v : beta;
			}
		}
	}

	return v; 

}