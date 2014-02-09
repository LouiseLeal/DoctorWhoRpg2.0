/*
 * TextOpcoes.cpp
 *
 *  Created on: Jun 19, 2013
 *      Author: Carol
 */

#include "../headers/Text.h"
#include "../headers/TextOpcoes.h"

#define SETA_PATH "../images/seta.gif"

TextOpcoes::TextOpcoes(vector<string> strOpcoes, int posX, int posY, int espaco, Sprite *sprite) {
	string strAux;
	string fontFile = "../fonts/CCRedAlert.ttf";
	SDL_Color corBranco = { 255, 255, 255 };
	SDL_Color corCinza = { 150, 150, 150 };

	vector<string>::iterator itString;
	seta = sprite;
	//seta->rotoZoom(0, 0.3, 0.3, true);
	setaX = posX - 20;
	setaY = posY;
	ptSize = 20;

	INTERVALO = espaco;


	//printf("size of vector :%d\n",strOpcoes.size());
	for (itString = strOpcoes.begin(); itString < strOpcoes.end(); itString++) {
		Text *newText;
		if ((*itString).find("*") != string::npos){
			(*itString).erase((*itString).begin());
			newText = new Text(fontFile, (*itString), ptSize, 1, corCinza, posX,posY);
		}
		else
			newText = new Text(fontFile, (*itString), ptSize, 1, corBranco, posX,
					posY);
		opcoes.push_back(newText);
		posY += INTERVALO;
		//printf("size box: %d\n",newText->box.w);
	}
	setaX = posX - 50;
	setaY = opcoes.front()->box.y - ((seta->getHeight() / 2) - (opcoes.front()->box.h / 2));

}
TextOpcoes::~TextOpcoes() {
	vector<Text*>::iterator itOpcoes;
	for (itOpcoes = opcoes.begin(); itOpcoes < opcoes.end(); itOpcoes++) {
		delete ((*itOpcoes));
	}
}
void TextOpcoes::render(bool bSeta) {
	vector<Text*>::iterator itOpcoes;
	for (itOpcoes = opcoes.begin(); itOpcoes < opcoes.end(); itOpcoes++) {
		(*itOpcoes)->render();
	}
	if(bSeta)
		seta->render(setaX,setaY);
}
int TextOpcoes::getOpcao() {
	int contador = 0;
	vector<Text*>::iterator itOpcoes;
	for (itOpcoes = opcoes.begin(); itOpcoes < opcoes.end(); itOpcoes++) {
		int comparacao = (*itOpcoes)->box.y - ((seta->getHeight() / 2) - ((*itOpcoes)->box.h / 2));
		if (setaY == comparacao) {
			return contador;
		}
		contador++;
	}
	return -1;
}
void TextOpcoes::update(bool direcao) {
	if (!direcao) {
		setaY -= INTERVALO;
		//compara se ja eh o primeiro item e volta para o ultimo
		int comparacaoInicio = opcoes.front()->box.y - ((seta->getHeight() / 2) - (opcoes.front()->box.h / 2));
		int posFinalSeta = opcoes.back()->box.y - ((seta->getHeight() / 2) - (opcoes.back()->box.h / 2));

		vector<Text*>::iterator it = opcoes.end() - 1;
		while(true){//!txtFound){
			if (setaY < comparacaoInicio)
				setaY = posFinalSeta;
			int comparacaoItem = (*it)->box.y - ((seta->getHeight() / 2) - ((*it)->box.h / 2));
			//printf("comparacao item: %d\n",comparacaoItem);
			//printf("setaY: %d\n",setaY);
			if(setaY == comparacaoItem){
				if(!(*it)->isTextSelecionavel())
					setaY -= INTERVALO;
				else {
					break;
				}
			}

			it--;

			if(it < opcoes.begin())
				it = opcoes.end() - 1;
		}

	} else {
		setaY += INTERVALO;
		//verifica se e o ultimo item e volta para o primeiro
		int comparacaoFinal = opcoes.back()->box.y - ((seta->getHeight() / 2) - (opcoes.back()->box.h / 2));
		int posInicioSeta = opcoes.front()->box.y - ((seta->getHeight() / 2) - (opcoes.front()->box.h / 2));

		vector<Text*>::iterator it = opcoes.begin();
		while(true){//!txtFound){
			if (setaY > comparacaoFinal)
				setaY = posInicioSeta;
			int comparacaoItem = (*it)->box.y - ((seta->getHeight() / 2) - ((*it)->box.h / 2));
			//printf("comparacao item: %d\n",comparacaoItem);
			//printf("setaY: %d\n",setaY);
			if(setaY == comparacaoItem){
				if(!(*it)->isTextSelecionavel())
					setaY += INTERVALO;
				else {
					break;
				}
			}

			it++;

			if(it >= opcoes.end()){
				//printf("cheguei no fim do vetor");
				it = opcoes.begin();
			}
		}

	}

}
int TextOpcoes::getWidthMax() {
	int max = 0;
	vector<Text*>::iterator itOpcoes;
	for (itOpcoes = opcoes.begin(); itOpcoes < opcoes.end(); itOpcoes++) {
		if ((*itOpcoes)->box.w > max)
			max = (*itOpcoes)->box.w;
	}
 return max;
}

