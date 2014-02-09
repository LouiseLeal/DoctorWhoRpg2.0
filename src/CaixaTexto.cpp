/*
 * CaixaTexto.cpp
 *
 *  Created on: Jun 26, 2013
 *      Author: Carol
 */

#include "../headers/CaixaTexto.h"

CaixaTexto::CaixaTexto(string texto){
	INTERVALO = 30;
	fontFile = "../fonts/CCRedAlert.ttf";
	ptSize = PTSIZE;

	fundoCaixaTexto = new Sprite("../images/tardis_box.png");
	tbPosX = (800/2) - (fundoCaixaTexto->getWidth() / 2);
	tbPosY = 600 - fundoCaixaTexto->getHeight() - 10;
	tbHeigh = 120;
	tbWidth = 682;

	posX = tbPosX + 25;
	posY = tbPosY + 58;

	int max_char = ((tbWidth - (25*2)) / CHAR_SIZE) - 5;
	int sizeOriginal = texto.size();
	int indexInicio = 0;
	int nroStr = sizeOriginal / max_char;
	for(int i = 0; i < nroStr; i++){
		string strAux;
		char espaco = ' ';
		//espaco esta no final da linha, pode continuar
		if(texto[max_char-1+ indexInicio] == espaco){
			strAux = texto.substr(indexInicio,max_char-1);
			vetStrings.push_back(strAux);
			indexInicio += max_char;
		}
		else {
			int posEspaco = texto.find(espaco,indexInicio + max_char);
			if(posEspaco == (max_char+ indexInicio-1)){
				strAux = texto.substr(indexInicio,max_char-1);
				vetStrings.push_back(strAux);
				indexInicio += max_char;
			}
			else {
				posEspaco = texto.find_last_of(espaco,indexInicio + max_char);
				strAux = texto.substr(indexInicio, posEspaco - indexInicio);
				vetStrings.push_back(strAux);
				indexInicio = posEspaco + 1;

			}
		}
		//printf("vetAux %s\n",strAux.c_str());
	}
	string strAux;
	strAux = texto.substr(indexInicio,texto.length() - indexInicio);
	vetStrings.push_back(strAux);
	//printf("vetAux %s\n",strAux.c_str());

	PRI_TEXTO = true;
	SEG_TEXTO = false;
	TER_TEXTO = false;

	timerWait = 0;
	timer.start();
	TXT_END = false;
	PAUSE = false;

	countLinhasEscritas = 3;

	setaContinua = new Sprite("../images/seta_branca_baixa.png");
	renderSeta = false;
	piscaSeta = 0;

	//printf("vet string size: %d\n",vetStrings.size());

}

void CaixaTexto::update(int deltaFrame) {
	if(!PAUSE) {
		SDL_Color corBranco = { 255, 255, 255 };
		unsigned int indice = 0;
		if(PRI_TEXTO)
			indice = 0;
		else if (SEG_TEXTO)
			indice = 1;
		else if(TER_TEXTO)
			indice = 2;

		if(vetStrings.size() > 0) {
			if(vetStrings[indice].size() == 0){
				if(PRI_TEXTO)
				{
					PRI_TEXTO = false;
					indice = 1;
					if(vetStrings.size() > 1)
						SEG_TEXTO = true;
					else{
						TXT_END = true;
						timerSeta.start();
					}
				}
				else if (SEG_TEXTO)
				{
					SEG_TEXTO = false;
					indice = 2;
					if(vetStrings.size() > 2)
						TER_TEXTO = true;
					else{
						printf("else texto dois!\n");
						TXT_END = true;
						timerSeta.start();
					}
				}
				else if(TER_TEXTO)
				{
					indice = 2;
					countLinhasEscritas++;
					if(countLinhasEscritas > 3)
					{
						PAUSE = true;
						timerSeta.start();
					}

					if(vetStrings.size() > 3){
						if(!PAUSE) {
							TER_TEXTO = true;
							//posicoes antigas
							int posX = vetText[0]->box.x;
							int posY = vetText[0]->box.y;
							int posX1 = vetText[1]->box.x;
							int posY1 = vetText[1]->box.y;
							vetText.erase(vetText.begin());
							//troca os text de lugar e atualiza posicao
							vetText[0]->setPos(posX,posY);
							//troca os text de lugar e atualiza posicao
							vetText[1]->setPos(posX1,posY1);
							vetStrings.erase(vetStrings.begin());
						}
					}
					else {
						TER_TEXTO = false;
						TXT_END = true;
						timerSeta.start();
						PAUSE = true;
					}
				}
			}

			if(PRI_TEXTO || SEG_TEXTO || TER_TEXTO) {
				if(timer.getTime() > timerWait) {
					//codigo de impressao e contatenacao do texto
					if(vetText.size() == indice){
						string strAux;
						if(vetStrings[indice].size() > 0) {
							strAux.push_back(vetStrings[indice][0]);
							if(vetStrings[indice][0] == '.'){
								timer.start();
								timerWait = 700;
							}
							else if(vetStrings[indice][0] == ','){
								timer.start();
								timerWait = 200;
							}
							vetStrings[indice].erase(0,1);
							Text *text = new Text(fontFile,strAux,ptSize,1,corBranco,posX,posY+(indice*INTERVALO));
							vetText.push_back(text);
						}
						else
							TXT_END = true;
					}
					else {
						string strAux;
						strAux = vetText[indice]->getString();
						strAux.push_back(vetStrings[indice][0]);
						if(vetStrings[indice][0] == '.'){
							timer.start();
							timerWait = 500;
						}
						else if(vetStrings[indice][0] == ','){
							timer.start();
							timerWait = 250;
						}
						vetStrings[indice].erase(0,1);
						vetText[indice]->setText(strAux);
						//printf("strAux %s\n",strAux.c_str());
					}
				}
			}

		}
	}
}

void CaixaTexto::render() {
	fundoCaixaTexto->render(tbPosX,tbPosY);
	if(vetText.size() > 0)
		vetText[0]->render();
	if(vetText.size() > 1)
		vetText[1]->render();
	if(vetText.size() > 2)
		vetText[2]->render();

	//655x145
	if(PAUSE || TXT_END){
		if(timerSeta.getTime() < 500)
			setaContinua->render(tbPosX + 630, tbPosY + 125);
		if(timerSeta.getTime() > 1000)
			timerSeta.start();

	}
}

void CaixaTexto::setText(string texto){

	//limpa os vetores
	vetStrings.clear();
	vetText.clear();

	int max_char = ((tbWidth - (25*2)) / CHAR_SIZE) - 5;
	int sizeOriginal = texto.size();
	int indexInicio = 0;
	int nroStr = sizeOriginal / max_char;
	for(int i = 0; i < nroStr; i++){
		string strAux;
		char espaco = ' ';
		//espaco esta no final da linha, pode continuar
		if(texto[max_char-1+ indexInicio] == espaco){
			strAux = texto.substr(indexInicio,max_char-1);
			vetStrings.push_back(strAux);
			indexInicio += max_char;
		}
		else {
			int posEspaco = texto.find(espaco,indexInicio + max_char);
			if(posEspaco == (max_char+ indexInicio-1)){
				strAux = texto.substr(indexInicio,max_char-1);
				vetStrings.push_back(strAux);
				indexInicio += max_char;
			}
			else {
				posEspaco = texto.find_last_of(espaco,indexInicio + max_char);
				strAux = texto.substr(indexInicio, posEspaco - indexInicio);
				vetStrings.push_back(strAux);
				indexInicio = posEspaco + 1;

			}
		}
		//printf("vetAux %s\n",strAux.c_str());
	}
	string strAux;
	strAux = texto.substr(indexInicio,texto.length() - indexInicio);
	vetStrings.push_back(strAux);
	//printf("vetAux %s\n",strAux.c_str());

	PRI_TEXTO = true;
	SEG_TEXTO = false;
	TER_TEXTO = false;

	timerWait = 0;
	timer.start();
	TXT_END = false;
	PAUSE = false;

	countLinhasEscritas = 3;
}


