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
	int maxp = 9;

	if(turno == Player::J2)
		maxp = 6;
	pair<int,Move> devolver = max(adversary,state, turno, alfa, beta,0,maxp);
	return  devolver.second;

}



pair<int,Move> AlphaMancala::max(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad ,const int MAXP){
	//if(state.getScore(jugador)>25){

	if(profundidad > MAXP || state.isFinalState()){

		int evaluacion = eval(state,jugador);
		pair<int,Move> devolver (evaluacion,M_NONE);

		return devolver;
	}

 	int mayor_valor = INT_MIN;
	Move mejor_movimiento;
	for(int i=1; i<=6;i++){

		//Para ver si es un movimiento valido
		if (state.getSeedsAt(jugador, (Position) i) >0) {

			//Calculamos el estado de realizar este movimiento
			GameState resultado= state.simulateMove( (Move) i);
			pair<int,Move> utilidad;
			
			if(resultado.getCurrentPlayer() == jugador){
				utilidad = max(adversary,resultado,jugador,alfa,beta,profundidad+1,MAXP);
			}else{
				utilidad = min(adversary,resultado,jugador,alfa,beta,profundidad+1,MAXP);
			}
			
			if(utilidad.first>mayor_valor){
				mayor_valor = utilidad.first;
				mejor_movimiento = (Move) i;
			}
			if(beta<=alfa){
				pair<int,Move> devolver (mayor_valor,mejor_movimiento);
				return devolver;
			}
			if(mayor_valor>alfa)
				alfa = mayor_valor;
		}
	}


	pair<int,Move> devolver (mayor_valor,mejor_movimiento);
	return devolver;
}
pair<int,Move> AlphaMancala::min(const vector<Move> & adversary,const  GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad ,const int MAXP){

	
	if( state.isFinalState()){
		
		int evaluacion = eval(state,jugador);
		pair<int,Move> devolver (evaluacion,M_NONE);
		return devolver;
	}
	int menor_valor = INT_MAX;
	Move mejor_movimiento;

	for(int i=1; i<=6;i++){
			
		if (state.getSeedsAt(jugador, (Position) i) >0) {

			//Calculamos el estado de realizar este movimiento
			GameState resultado = state.simulateMove( (Move) i);
			pair<int,Move>  utilidad;
			if(resultado.getCurrentPlayer() == jugador){
				utilidad = max(adversary,resultado,jugador,alfa,beta,profundidad+1,MAXP);
			}else{
				utilidad = min(adversary,resultado,jugador,alfa,beta,profundidad+1,MAXP);
			}
		
			if(utilidad.first<menor_valor){
				menor_valor = utilidad.first;
				mejor_movimiento = (Move) i;
			}
			if(beta<=alfa){
				pair<int,Move> devolver (menor_valor,mejor_movimiento);
				return devolver;
			}
			if(menor_valor<beta)
				beta = menor_valor;
		}
	}
	
	pair<int,Move> devolver (menor_valor,mejor_movimiento);
	return devolver;

}
int AlphaMancala::eval(const GameState & state, const Player & jugador){
	Player adversario;
	if(jugador == Player::J1)
		adversario = Player::J2;
	else	
		adversario = Player::J1;
	
	int devolver =0;
	int evaluacion =  state.getScore(jugador)-state.getScore(adversario);

	int semillasJug = semillasJugador(state,jugador);
	int semillasAdv = semillasJugador(state,adversario);

	devolver = evaluacion;

	
	
	
	return devolver;
}

int AlphaMancala::semillasJugador(const GameState & state, const Player & jugador){
	int semillas = 0;
	for(int i = 0; i <=6; i++)
		semillas += state.getSeedsAt(jugador,(Position)i);
	return semillas;
}