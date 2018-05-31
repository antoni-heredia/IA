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

	int max(const vector<Move> & adversary, const GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad, Move & movimiento);
	int min(const vector<Move> & adversary, const GameState & state, const Player & jugador, int  alfa, int  beta, int profundidad, Move & movimiento);
};

#endif /* MANUPCBOT_H_ */
