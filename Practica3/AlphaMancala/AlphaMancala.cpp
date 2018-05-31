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
	int maxp = 3;
	if(turno == Player::J2)
		maxp = 15;
	max(adversary,state, turno, alfa, beta,0, movimiento,maxp);
	return  movimiento;

}



int AlphaMancala::max(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad, Move & movimiento,const int MAXP){
	//if(state.getScore(jugador)>25){

	if(profundidad == MAXP || state.isFinalState()){

		int evaluacion = eval(state,jugador);
		return evaluacion;
	}

 	int mayor_valor = INT_MIN;
	Move mejor_movimiento;
	for(int i=1; i<=6;i++){

		//Para ver si es un movimiento valido
		if (state.getSeedsAt(jugador, (Position) i) >0) {

			//Calculamos el estado de realizar este movimiento
			GameState resultado= state.simulateMove( (Move) i);
			int utilidad;
			
			if(resultado.getCurrentPlayer() == jugador){
				utilidad = max(adversary,resultado,jugador,alfa,beta,profundidad+1, movimiento,MAXP);
			}else{
				utilidad = min(adversary,resultado,jugador,alfa,beta,profundidad+1, movimiento,MAXP);
			}
			
			if(utilidad>mayor_valor){
				mayor_valor = utilidad;
				mejor_movimiento = (Move) i;
			}
			if(mayor_valor>=beta){
				movimiento = mejor_movimiento;
				return mayor_valor;
			}
			if(mayor_valor>alfa)
				alfa = mayor_valor;
		}
	}


	movimiento = mejor_movimiento;
	return mayor_valor; 
}
int AlphaMancala::min(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad, Move & movimiento,const int MAXP){

	if(profundidad == MAXP || state.isFinalState()){
		
		int evaluacion = eval(state,jugador);
		return evaluacion;
	}
	int menor_valor = INT_MAX;
	Move mejor_movimiento;

	for(int i=1; i<=6;i++){
			
		if (state.getSeedsAt(jugador, (Position) i) >0) {

			//Calculamos el estado de realizar este movimiento
			GameState resultado = state.simulateMove( (Move) i);
			int utilidad;
			if(resultado.getCurrentPlayer() == jugador){
				utilidad = min(adversary,resultado,jugador,alfa,beta,profundidad+1, movimiento,MAXP);
			}else
				utilidad = max(adversary,resultado,jugador,alfa,beta,profundidad+1, movimiento,MAXP);

		
			if(utilidad<menor_valor){
				menor_valor = utilidad;
				mejor_movimiento = (Move) i;
			}
			if(menor_valor<=alfa){
				movimiento = mejor_movimiento;
				return menor_valor;
			}
			if(menor_valor>beta)
				beta = menor_valor;
		}
	}
	
	movimiento = mejor_movimiento;
	return menor_valor; 

}
int AlphaMancala::eval(const GameState & state, const Player & jugador){
	Player adversario;
	if(jugador == Player::J1)
		adversario = Player::J2;
	else	
		adversario = Player::J1;

	int evaluacion =  state.getScore(jugador)-state.getScore(adversario);
	if(state.isFinalState() && state.getScore(adversario)>24)
		evaluacion = 0;
	else if(state.isFinalState() && state.getScore(jugador)>24)
		evaluacion = INT_MAX;
		
	return evaluacion;
}
