/*
 * Text.h
 *
 *  Created on: 07/06/2013
 *      Author: Louise
 */

#include "SDLBase.h"
// #include "iostream"

#ifndef TEXT_H_
#define TEXT_H_

using namespace std;

class Text{
private:
	TTF_Font * font;
	SDL_Surface * textSurface;
	string text;
	string pathFont;
	int style;
	int ptsize;
	SDL_Color color;


public:
	SDL_Rect box;
	Text(string fontFile, string text, int ptsize,int style, SDL_Color color, int x , int y);
	virtual ~Text();
	void render();
	void setPos(int x, int y);
	void setText(string text);
	void setColor(SDL_Color color);
	bool isTextSelecionavel();
	void setStyle(int style);
	void setSize(int ptsize);
	string getString() {return text;};
};

#endif /* TEXT_H_ */
