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
	int maxp = 11;
	
	pair<double,Move> devolver = max(adversary,state, turno, alfa, beta,0,maxp);
	return  devolver.second;

}



pair<double,Move> AlphaMancala::max(const vector<Move> & adversary,const  GameState & state, const Player & jugador, double  alfa, double  beta, int profundidad ,const int MAXP){
	//if(state.getScore(jugador)>25){

	if(profundidad == MAXP || state.isFinalState()){

		double evaluacion = eval(state,jugador);
		pair<double,Move> devolver (evaluacion,M_NONE);

		return devolver;
	}

 	double mayor_valor = INT_MIN;
	Move mejor_movimiento;
	for(int i=1; i<=6;i++){

		//Para ver si es un movimiento valido
		//if (state.getSeedsAt(jugador, (Position) i) >0) {

			//Calculamos el estado de realizar este movimiento
			GameState resultado= state.simulateMove( (Move) i);
			pair<double,Move> utilidad;
			
			if(resultado.getCurrentPlayer() == state.getCurrentPlayer()){
				utilidad = max(adversary,resultado,jugador,alfa,beta,profundidad+1,MAXP);
			}else{
				utilidad = min(adversary,resultado,jugador,alfa,beta,profundidad+1,MAXP);
			}
			
			if(utilidad.first>mayor_valor){
				mayor_valor = utilidad.first;
				mejor_movimiento = (Move) i;
			}

			alfa = std::max(mayor_valor,alfa);		

			if(beta<=alfa){
				pair<double,Move> devolver (mayor_valor,mejor_movimiento);
				return devolver;
			}

			
		//}
	}


	pair<double,Move> devolver (mayor_valor,mejor_movimiento);
	return devolver;
}
pair<double,Move> AlphaMancala::min(const vector<Move> & adversary,const  GameState & state, const Player & jugador, double  alfa, double  beta, int profundidad ,const int MAXP){

	
	if( profundidad == MAXP ||state.isFinalState()){
		//cerr << "nodo min" << endl;
		double evaluacion = eval(state,jugador);
		pair<double,Move> devolver (evaluacion,M_NONE);
		return devolver;
	}
	double menor_valor = INT_MAX;
	Move mejor_movimiento;

	for(int i=1; i<=6;i++){
			

			//Calculamos el estado de realizar este movimiento
			GameState resultado = state.simulateMove( (Move) i);
			pair<double,Move>  utilidad;
			if(resultado.getCurrentPlayer() == state.getCurrentPlayer()){
				utilidad = min(adversary,resultado,jugador,alfa,beta,profundidad+1,MAXP);
			}else{
				utilidad = max(adversary,resultado,jugador,alfa,beta,profundidad+1,MAXP);
			}
		
			if(utilidad.first<menor_valor){
				menor_valor = utilidad.first;
				mejor_movimiento = (Move) i;
			}

			beta = std::min(menor_valor,beta);

			if(beta<=alfa){
				pair<double,Move> devolver (menor_valor,mejor_movimiento);
				return devolver;
			}
			
		
	}
	
	pair<double,Move> devolver (menor_valor,mejor_movimiento);
	return devolver;

}
double AlphaMancala::eval(const GameState & state, const Player & jugador){
	Player adversario;
	if(jugador == Player::J1)
		adversario = Player::J2;
	else	
		adversario = Player::J1;
	//Heuristica Antiguas	
	/*
	double devolver =0;
	double evaluacion =  state.getScore(jugador)-state.getScore(adversario);

	double semillasJug = semillasJugador(state,jugador);
	double semillasAdv = semillasJugador(state,adversario);

	double cuanto_le_falta = 24 - state.getScore(jugador);

	devolver = evaluacion+evaluacion+(cuanto_le_falta)+(semillasJug*0.5)-(semillasAdv*0.5);
	*/
	
	//Nueva heuristica sacada de http://eldar.mathstat.uoguelph.ca/dashlock/CIG2013/papers/paper_45.pdf
	int h1 = state.getSeedsAt(jugador,(Position)6);
	int h2 = semillasJugador(state,jugador);
	int h3 = cantDeContadoresDisponibles(state,jugador);
	int h4 = state.getScore(jugador);
	int h5 = state.getSeedsAt(jugador,(Position)0);
	int h6 = cantDeContadoresDisponibles(state,adversario);
	double devolver = (h1*0.126 )+(h2*0.104)+(h3*0.564)+h4+(h5*0.51 )-(h6*0.605);
	
	return devolver;
}


int AlphaMancala::semillasJugador(const GameState & state, const Player & jugador){
	int semillas = 0;
	for(int i = 0; i <=6; i++)
		semillas += state.getSeedsAt(jugador,(Position)i);
	return semillas;
}

int AlphaMancala::cantDeContadoresDisponibles(const GameState & state, const Player & jugador){
	int disponible = 0;
	for(int i = 0; i <=6; i++)
		if(state.getSeedsAt(jugador,(Position)i) > 0)
		disponible++;
	return disponible;
}