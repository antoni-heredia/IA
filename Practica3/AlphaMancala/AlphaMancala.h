/*
 * AlphaMancala.h
 *
 *  Author: Antonio Heredia Castillo
 */

#include "Bot.h"

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

class AlphaMancala:Bot {
public:
	AlphaMancala();
	~AlphaMancala();


	void initialize();
	string getName();

	Move nextMove(const vector<Move> & adversary, const GameState &state);

	Move miniMax(const vector<Move>  & adversary,const GameState & state);

	pair<double,Move> max(const vector<Move> & adversary, const GameState & state, const Player & jugador, double  alfa, double  beta, int profundidad,const int MAXP);
	pair<double,Move> min(const vector<Move> & adversary, const GameState & state, const Player & jugador, double  alfa, double  beta, int profundidad,const int MAXP);
	double eval(const GameState & state,const Player & jugador);

	int semillasJugador(const GameState & state, const Player & jugador);

};

#endif /* MANUPCBOT_H_ */
