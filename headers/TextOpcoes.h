/*
 * TextoOpcoes.h
 *
 *  Created on: Jun 19, 2013
 *      Author: Carol
 */

#ifndef TEXTOPCOES_H_
#define TEXTOPCOES_H_

#include "Text.h"
// #include "SDLBase.h"
#include "Sprite.h"

class TextOpcoes {
public:
	int setaX;
	int setaY;
	TextOpcoes(vector<string> strOpcoes, int posX, int posY, int espaco, Sprite *sprite);
	vector<Text*> opcoes;
	Sprite * seta;
	~TextOpcoes();
	void render(bool bSeta);
	int getOpcao();
	// bool = 0 foi selecionado pra cima, bool = 1 foi selecionado pra baixo
	void update(bool direcao);
	int getWidthMax();
	int ptSize;
	int INTERVALO;
};


#endif /* TEXTOPCOES_H_ */
