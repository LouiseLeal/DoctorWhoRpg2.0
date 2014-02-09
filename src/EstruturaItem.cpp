/*
 * EstruturaItem.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Carol
 */

#include "../headers/EstruturaItem.h"

EstruturaItem::EstruturaItem(Item *item, int posX, int posY){
	this->posX = posX;
	this->posY = posY;
	int ptSize = 20;

	//550x 20y
	string fontFile = "../fonts/CCRedAlert.ttf";
	SDL_Color corBranco = { 255, 255, 255 };

	//620x 50y
	nome = new Text(fontFile, item->nome.c_str(),ptSize,TTF_STYLE_NORMAL,corBranco,posX + 70, posY + 30);

	//620x 250y
	int boxWidth = 225; // 12 = ptsize 3 = espacos
	int max_char = (boxWidth / 10) - 3;
	int sizeOriginal = item->descricao.size(); //tamnho original da string
	int indexInicio = 0; //index do inicio para corte
	int nroStr = sizeOriginal / max_char; //nro d strings depois de dividir
	printf("nroStr: %d max_car %d sizeOriginial %d\n",nroStr, max_char, sizeOriginal);
	for(int i = 0; i <= nroStr; i++){
		string strAux;
		char espaco = ' ';
		string texto = item->descricao;
		//espaco esta no final da linha, pode continuar
		if(texto[max_char-1+ indexInicio] == espaco){
			strAux = texto.substr(indexInicio,max_char-1);
			printf("1Substring: %s\n",strAux.c_str());
			vetStrings.push_back(strAux);
			indexInicio += max_char;
		}
		else {

			if(max_char + indexInicio - 1  >= sizeOriginal){
				strAux = texto.substr(indexInicio,sizeOriginal - indexInicio);
				printf("4Substring: %s\n",strAux.c_str());
				vetStrings.push_back(strAux);
				indexInicio += sizeOriginal - indexInicio;
			}
			else {
				int posEspaco = texto.find(espaco,indexInicio + max_char);
				if(posEspaco == (max_char+ indexInicio-1)){
					strAux = texto.substr(indexInicio,max_char-1);
					printf("2Substring: %s\n",strAux.c_str());
					vetStrings.push_back(strAux);
					indexInicio += max_char;
				}
				else {
					posEspaco = texto.find_last_of(espaco,indexInicio + max_char);
					strAux = texto.substr(indexInicio, posEspaco - indexInicio);
					printf("3Substring: %s\n",strAux.c_str());
					vetStrings.push_back(strAux);
					indexInicio = posEspaco + 1;

				}
			}
		}
		//printf("vetAux %s\n",strAux.c_str());
	}

	int posYAux;
	for(int i = 0; i < vetStrings.size(); i++){
		posYAux = 230 + i*20;
		printf("Posy + posYAux %d\n",posYAux + posY);
		Text *txtAux = new Text(fontFile,vetStrings[i],ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20, posY + posYAux);
		vetText.push_back(txtAux);
	}
	//descricao = new Text(fontFile,item->descricao,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20, posY + 230);

	//570x 280y
	//int posYAux = posY;
	posYAux += 50;
	if(item->xpEffect != 0){
		char strEffect[50];
		sprintf(strEffect,"XP Effect: %d\%",item->xpEffect);
		Text *efeito = new Text(fontFile, strEffect,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20, posYAux + posY);// + 260);
		posYAux += 20;
		vetEfeito.push_back(efeito);
	}
	if(item->hpEffect != 0){
		char strEffect[50];
		sprintf(strEffect,"HP Effect: %d",item->hpEffect);
		Text *efeito = new Text(fontFile, strEffect,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20, posYAux + posY);
		posYAux += 20;
		vetEfeito.push_back(efeito);
	}
	if(item->attackEffect != 0){
		char strEffect[50];
		sprintf(strEffect,"Attack Effect: %d%",item->attackEffect);
		Text *efeito = new Text(fontFile, strEffect,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20,posYAux + posY);
		posYAux += 20;
		vetEfeito.push_back(efeito);
	}
	if(item->inteligenceEffect != 0){
		char strEffect[50];
		sprintf(strEffect,"Intelligence Effect: %d%",item->inteligenceEffect);
		Text *efeito = new Text(fontFile, strEffect,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20, posYAux + posY);

		vetEfeito.push_back(efeito);
	}
	if(item->defenseEffect != 0){
		char strEffect[50];
		sprintf(strEffect,"Defence Effect: %d%",item->defenseEffect);
		Text *efeito = new Text(fontFile, strEffect,ptSize,TTF_STYLE_NORMAL,corBranco,posX + 20,posYAux + posY);
		posYAux += 20;
		vetEfeito.push_back(efeito);
	}

	string strSprite = "../images/";
	strSprite += item->nome;
	strSprite += ".png";
	sprite = new Sprite(strSprite);
}

void EstruturaItem::render() {
	//render da imagem 620x 100y
	sprite->render(posX + 70, posY + 80);
	nome->render();
//	descricao->render();
	for(int i = 0; i < vetText.size(); i++)
		vetText[i]->render();
	for(vector<Text*>::iterator it = vetEfeito.begin(); it < vetEfeito.end(); it++)
		(*it)->render();
}



