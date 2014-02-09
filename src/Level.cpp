/*
 * Level.cpp
 *
 *  Created on: 01/06/2013
 *      Author: Louise
 */

#include "../headers/Level.h"

Level::Level(int attackLevel, int intelligenceLevel, int defenceLevel){
	this->attackLevel= attackLevel;
	this->defenseLevel= defenceLevel;
	this->intelligenceLevel= intelligenceLevel;
}

void Level::setAttackLevel(int attackLevel){
	this->attackLevel= attackLevel;
}
void Level::setIntelligenceLevel(int intelligenceLevel){
	this->intelligenceLevel= intelligenceLevel;
}
	void Level::setDefenseLevel(int defenseLevel){
		this->defenseLevel= defenseLevel;
	}
int Level::getAttackLevel(){
	return attackLevel;
}
int Level::getIntelligenceLevel(){
	return intelligenceLevel;
}
int Level::getDefenseLevel(){
	return defenseLevel;
	}


int Level::getLevelMax(){
	if(attackLevel >= intelligenceLevel)
	{
		if(attackLevel >= defenseLevel)
			return 0;
		else
			return 2;
	}
	else if( intelligenceLevel >= defenseLevel){
		return 1;
	}
	else
		return 2;
}

int Level::getTotalLevel() {
	return attackLevel + intelligenceLevel + defenseLevel;
}
