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

	pair<int,Move> max(const vector<Move> & adversary, const GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad,const int MAXP);
	pair<int,Move> min(const vector<Move> & adversary, const GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad,const int MAXP);
	int eval(const GameState & state,const Player & jugador);

	int semillasJugador(const GameState & state, const Player & jugador);

};

#endif /* MANUPCBOT_H_ */
