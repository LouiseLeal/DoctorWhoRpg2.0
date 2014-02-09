/*
 * EstruturaStatus.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Carol
 */

#include "../headers/EstruturaStatus.h"

EstruturaStatus::EstruturaStatus(PersonagemAtivo *personagem, int posX, int posY){
	this->posX = posX;
	this->posY = posY;
	int ptSize = 20;

	//550x 20y
	string fontFile = "../fonts/CCRedAlert.ttf";
	SDL_Color corBranco = { 255, 255, 255 };

	//620x 50y
	nome = new Text(fontFile, personagem->nome.c_str(),ptSize,TTF_STYLE_NORMAL,corBranco,posX + 70, posY + 30);

	//620x 250y
	string strTipo = "Type: ";
	if(personagem->tipo == ATAQUE)
		strTipo += "Attack";
	else if(personagem->tipo == INTELIGENCIA)
		strTipo += "Intelligence";
	else if(personagem->tipo == DEFESA)
		strTipo += "Defence";

	tipo = new Text(fontFile, strTipo,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 70, posY + 230);

	char strAtaque[50];
	sprintf(strAtaque,"Attack: %d",personagem->habilidade.ataque);
	char strInteligencia[50];
	sprintf(strInteligencia,"Intelligence: %d",personagem->habilidade.inteligencia);
	char strDefensa[50];
	sprintf(strDefensa,"Defence: %d",personagem->habilidade.defesa);


	//570x 280y
	ataque = new Text(fontFile,strAtaque,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20, posY + 260);
	inteligencia = new Text(fontFile,strInteligencia,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20, posY + 280);
	defesa = new Text(fontFile,strDefensa,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20, posY + 300);

	string strSprite = "../images/";
	strSprite += personagem->nome;
	strSprite += "_Normal.png";
	sprite = new Sprite(strSprite);
}

void EstruturaStatus::render() {
	//render da imagem 620x 100y
	sprite->render(posX + 70, posY + 80);
	nome->render();
	tipo->render();
	ataque->render();
	inteligencia->render();
	defesa->render();

}



