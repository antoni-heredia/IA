/*
 * AlphaMancala.h
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
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

	pair<Move,int> max(const vector<Move> & adversary, const GameState & state, const Player & jugador, int & alfa, int & beta, int profundidad);
	pair<Move,int> min(const vector<Move> & adversary, const GameState & state, const Player & jugador, int & alfa, int & beta, int profundidad);
};

#endif /* MANUPCBOT_H_ */
