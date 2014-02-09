/*
 * Item.cpp
 *
 *  Created on: 20/06/2013
 *      Author: Louise
 */

#include "../headers/Item.h"

Item::Item(string nome, string descricao, int hpEffect, int xpEffect, int attackEffect, int inteligenceEffect, int defenseEffect){
	this->nome = nome;
	this->descricao = descricao;
	this->hpEffect = hpEffect;
	this->xpEffect = xpEffect;
	this->attackEffect = attackEffect;
	this->inteligenceEffect = inteligenceEffect;
	this->defenseEffect = defenseEffect;

	string strSprite = IMAGE_PATH;
	strSprite += nome;
	strSprite +=".png";
	this->sprite = new Sprite(strSprite);
}

