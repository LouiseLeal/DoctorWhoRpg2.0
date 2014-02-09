/*
 * Level.h
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "SDLBase.h"

class Level {
private:
	int attackLevel;
	int intelligenceLevel;
	int defenseLevel;

public:
	Level(int attackLevel, int intelligenceLevel, int defenceLevel);

	void setAttackLevel(int attackLevel);
	void setIntelligenceLevel(int intelligenceLevel);
	void setDefenseLevel(int defenseLevel);

	int getAttackLevel();
	int getIntelligenceLevel();
	int getDefenseLevel();

	int getLevelMax();
	int getTotalLevel();

};


#endif /* LEVEL_H_ */
