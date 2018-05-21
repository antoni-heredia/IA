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
	
	menor_valor = INT_MAX;
	mayor_valor = INT_MIN;
	long timeout= this->getTimeOut();

	Move movimiento= M_NONE;


	int puntos= -10000;


	int alfa = -50;
	int beta = 50;

	return max(adversary,state, turno, alfa, beta,0).first;

}



pair<Move,int> AlphaMancala::max(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int & alfa, int & beta, int profundidad){
	//if(state.getScore(jugador)>25){

	if(profundidad == 7){
		pair<Move,int> devolver;
		devolver.first = mejor_accion;
		devolver.second = mayor_valor;
		//cerr << "if max" <<endl;
		return devolver;
	}else{

		for(int i=1; i<=6;i++){
				//cerr<< i << endl;

			//Para ver si es un movimiento valido
			if (state.getSeedsAt(jugador, (Position) i) >0) {

				//Calculamos el estado de realizar este movimiento
				GameState hijo= state.simulateMove( (Move) i);
				pair<Move,int> resultado = min(adversary,hijo,jugador,alfa,beta,profundidad+1);
				if(mayor_valor<resultado.second){
					mayor_valor = resultado.second;
					mejor_accion = (Move)i;
					cerr << "mejora:" << i << endl;
				}
				if(mayor_valor >= beta){
					pair<Move,int> devolver;
					devolver.first = mejor_accion;
					devolver.second = mayor_valor;
							//cerr << "for max" <<endl;

					return devolver;
				}
				if(mayor_valor > alfa){
					alfa = mayor_valor;
				}

			
			}
		}
	}

	pair<Move,int> devolver;
	devolver.first = mejor_accion;
	devolver.second = mayor_valor;
				//cerr << "fuera max" <<endl;

	return devolver; 
}

pair<Move,int> AlphaMancala::min(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int & alfa, int & beta, int profundidad){
		if(profundidad == 7){
		pair<Move,int> devolver;
		devolver.first = mejor_accion;
		devolver.second = mayor_valor;
		//cerr << "if min" <<endl;

		return devolver;
	}else{
		
		for(int i=1; i<=6;i++){
			//Para ver si es un movimiento valido
			if (state.getSeedsAt(jugador, (Position) i) >0) {

				//Calculamos el estado de realizar este movimiento
				GameState hijo= state.simulateMove( (Move) i);
				pair<Move,int> resultado = max(adversary,hijo,jugador,alfa,beta,profundidad+1);
				if(menor_valor>resultado.second){
					menor_valor = resultado.second;
					mejor_accion = (Move)i;
					cerr << "mejora:" << i << endl;

				}
				if(menor_valor <= alfa){
					pair<Move,int> devolver;
					devolver.first = mejor_accion;
					devolver.second = menor_valor;

					return devolver;
				}
				if(menor_valor > beta)
					beta = menor_valor;
				
				
			}
		}
	}
	pair<Move,int> devolver;
	devolver.first = mejor_accion;
	devolver.second = menor_valor;
										//cerr << "fuera min" <<endl;

	return devolver; 
}