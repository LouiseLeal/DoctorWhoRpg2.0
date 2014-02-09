/*
 * CaixaTexto.h
 *
 *  Created on: Jun 26, 2013
 *      Author: Carol
 */

#ifndef CAIXATEXTO_H_
#define CAIXATEXTO_H_

#include "Text.h"
// #include "SDLBase.h" -- ja tem no sprite
#include "Sprite.h"
#include "Tempo.h"

//#define INTERVALO 20
#define PTSIZE 25
#define CHAR_SIZE 12

class CaixaTexto {
public:
	CaixaTexto(string texto);
	void update(int deltaFrame);
	void render();
	void setText(string texto);


	vector<Text*> vetText;
	vector<string> vetStrings;
	string fontFile;
	int ptSize;
	int posX;
	int posY;

	//variaveis do tamanho da caixa de texto
	Sprite *fundoCaixaTexto;
	int tbPosX;
	int tbPosY;
	int tbWidth;
	int tbHeigh;

	//controle de qual linha deve ser impressa
	bool PRI_TEXTO;
	bool SEG_TEXTO;
	bool TER_TEXTO;

	//temporizador para controlar impressao do texto
	Tempo timer;
	Tempo timerSeta;
	int timerWait;

	bool TXT_END;
	bool PAUSE;
	bool renderSeta;

	int INTERVALO;
	int countLinhasEscritas;

	Sprite *setaContinua;
	int piscaSeta;
};



#endif /* CAIXATEXTO_H_ */
