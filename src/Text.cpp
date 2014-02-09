/*
 * Text.cpp
 *
 *  Created on: 07/06/2013
 *      Author: Louise
 */

#include "../headers/Text.h"

Text::Text(string fontFile, string text, int ptsize, int style, SDL_Color color,
		int x, int y) {
	this->pathFont = fontFile;
	this->text = text;
	this->ptsize = ptsize;
	this->style = style;
	this->box.x = x;
	this->box.y = y;
	this->box.w = 0;
	this->box.h = 0;
	this->color = color;
	this->font = TTF_OpenFont(fontFile.c_str(), ptsize);
	if (font == NULL) {
		cout << "Text : font==NULL" << endl;
	}

	//printf("texto no text %s\n",text.c_str());
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	this->textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	this->box.w = textSurface->w;
	this->box.h = textSurface->h;

}

Text::~Text() {
	TTF_CloseFont(font);
	SDL_FreeSurface(textSurface);
}
void Text::render() {
	SDL_Rect dst;
	dst.x = box.x;
	dst.y = box.y;
	dst.w = 0;
	dst.h = 0;
	SDLBase::renderSurface(textSurface, NULL, &dst);
	box.w = textSurface->clip_rect.w;
	box.h = textSurface->clip_rect.h;
}
void Text::setPos(int x, int y) {
	box.x = x;
	box.y = y;
}
void Text::setText(string text) {
	SDL_Rect dst;
	dst.x = box.x;
	dst.y = box.x;
	dst.w = 0;
	dst.h = 0;
	SDL_FreeSurface(textSurface);
	if (textSurface == NULL) {
		cout << "(Text::setText) Fala ao liberar o surface " << endl;
	}
	this->text = text;
	textSurface = TTF_RenderText_Blended(font, this->text.c_str(), color);
	SDLBase::renderSurface(textSurface, NULL, &dst);
	box.w = textSurface->clip_rect.w;
	box.h = textSurface->clip_rect.h;
}
void Text::setColor(SDL_Color color) {
	SDL_FreeSurface(textSurface);
	if (textSurface == NULL) {
		cout << "(Text -  setColor) Erro ao liberar surface" << endl;
	}
	textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (textSurface == NULL) {
		cout << "(Text -  setColor) surface NULA" << endl;
	}
}
void Text::setStyle(int style) {
	SDL_Rect dst;
	dst.x = box.x;
	dst.y = box.x;
	dst.w = 0;
	dst.h = 0;
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

	if (textSurface != NULL) {
		cout << "(Text::setText) Fala ao liberar o surface " << endl;
	}
	this->style = style;
	TTF_SetFontStyle(font, this->style);
	textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDLBase::renderSurface(textSurface, &box, &dst);
	box.w = textSurface->clip_rect.w;
	box.h = textSurface->clip_rect.h;

}
void Text::setSize(int ptsize) {
	this->ptsize = ptsize;
	SDL_Rect dst;
	dst.x = box.x;
	dst.y = box.x;
	dst.w = 0;
	dst.h = 0;
	SDL_FreeSurface(textSurface);

	if (textSurface != NULL) {
		cout << "(Text::setText) Fala ao liberar o surface " << endl;
	}
	// this->style = style;
	TTF_SetFontStyle(font, this->style);
	textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDLBase::renderSurface(textSurface, &box, &dst);
	box.w = textSurface->clip_rect.w;
	box.h = textSurface->clip_rect.h;

}

bool Text::isTextSelecionavel(){
	if(color.b == 150 && color.g == 150 && color.r == 150){
		//printf("nao selecionalvel!!\n");
		return false;
	}
	else
		return true;
}
