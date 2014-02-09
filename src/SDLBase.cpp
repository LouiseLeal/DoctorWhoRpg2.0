/*
 * SDLBase.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: Carol
 */
#include "../headers/SDLBase.h"

SDL_Surface *SDLBase::screen;
int SDLBase::LEVEL_DIFICULDADE;
int SDLBase::FPS = 1000/30;
string SDLBase::strLanguage;

int SDLBase::inicializaSDL() {
	//inicia o sdl
	int retorno = SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE);
	if(retorno < 0)
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	//muda o nome da tela
	SDL_WM_SetCaption("Doctor Who - An Army of Ghosts", "Doctor Who - An Army of Ghosts");

	//seta o tipo de video
	screen = SDL_SetVideoMode(800, 600, 0, SDL_SWSURFACE);
	if(screen == NULL)
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	TTF_Init();

	return 1;
}

void SDLBase::finalizaSDL(){
	TTF_Quit();
}

SDL_Surface *SDLBase::getSurface(){
	return screen;
}

SDL_Surface *SDLBase::loadImage(string fileName){

	//adicionar uma imagem a surface
	SDL_Surface *surface = 0;
	surface = IMG_Load(fileName.c_str());
	if(!surface)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(1);
	}

	SDL_Surface *surfaceAux = 0;
	if(surface->format->Amask == 0) //nao tem canal alpha
		surfaceAux = SDL_DisplayFormat(surface);
	else //tem canal alpha
		surfaceAux = SDL_DisplayFormatAlpha(surface);

	if(surfaceAux == NULL)
	{
		printf("SDL_BlitSurface: %s\n", IMG_GetError());
		exit(1);
	}

	SDL_FreeSurface(surface);

	return surfaceAux;
}

void SDLBase::renderSurface(SDL_Surface* surface, SDL_Rect *clip, SDL_Rect *destino){
	//colar a imagem na surface
	//SDL_BlitSurface(fontSurface, NULL, caixaTexto, fontRect);
	if(SDL_BlitSurface(surface, clip, screen, destino) != 0)
	{
		printf("SDL_BlitSurface: %s\n", IMG_GetError());
		exit(1);
	}
}

void SDLBase::SDLBase::updateScreen(){
	//atualizar a modificacao na tela
	if(SDL_Flip(screen) != 0)
	{
		printf("SDL_Flip: %s\n", IMG_GetError());
		exit(1);
	}
}

void SDLBase::drawLine(int x1, int y1, int x2, int y2, int rgb, int spacing)
{
	int deltax = abs(x2 - x1); // The difference between the x's
	int deltay = abs(y2 - y1); // The difference between the y's
	int x = x1;                // Start x off at the first pixel
	int y = y1;                // Start y off at the first pixel
	int xinc1 = 0;
	int yinc1 = 0;
	int xinc2 = 0;
	int yinc2 = 0;
	int den = 0;
	int num = 0;
	int numadd = 0;
	int numpixels = 0;

	if (x2 >= x1)              // The x-values are increasing
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else                       // The x-values are decreasing
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)              // The y-values are increasing
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else                       // The y-values are decreasing
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)		// There is at least one x-value for every y-value
	{
		xinc1 = 0;				// Don't change the x when numerator >= denominator
		yinc2 = 0;				// Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;		// There are more x-values than y-values
	}
	else						// There is at least one y-value for every x-value
	{
		xinc2 = 0;				// Don't change the x for every iteration
		yinc1 = 0;				// Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;		// There are more y-values than x-values
	}

	for (int curpixel = 1; curpixel <= numpixels; curpixel++)
	{
		if (spacing == 0)
		{
			SDL_Rect pixel = {x,y,1,1};
			SDL_FillRect(screen,&pixel,rgb);
		}
		else if (curpixel % spacing >= spacing/2)
		{
			SDL_Rect pixel = {x,y,1,1};
			SDL_FillRect(screen,&pixel,rgb);
		}

		num += numadd;         // Increase the numerator by the top of the fraction
		if (num >= den)        // Check if numerator >= denominator
		{
			num -= den;         // Calculate the new numerator value
			x += xinc1;         // Change the x as appropriate
			y += yinc1;         // Change the y as appropriate
		}
		x += xinc2;             // Change the x as appropriate
		y += yinc2;             // Change the y as appropriate
	}
}


// SDL_Surface *SDLBase::rotoZoom(SDL_Surface *surface, float angle, double scaleX, double scaleY){
// 	if(surface == NULL)
// 		return NULL;

// 	if(scaleX < 0 || scaleY < 0){
// 		printf("Erro: valor inválido de escala. Rotação não realizada.\n");
// 		return surface;
// 	}

// 	SDL_Surface *surfaceAux = zoomSurface(surface, angle, scaleX, 1);
// 	return surfaceAux;
// }

SDL_Surface *SDLBase::clip(SDL_Surface *original, SDL_Rect *clip){
	if(original == NULL)
		return NULL;

	SDL_Surface *surfaceAux = SDL_CreateRGBSurface(original->flags, clip->w, clip->h, 32, original->format->Rmask, original->format->Gmask, original->format->Bmask, 0);

	if(surfaceAux == NULL){
		printf("SDL_CreateRGBSurface: %s\n", IMG_GetError());
		exit(1);
	}

	if(SDL_BlitSurface(original,clip, surfaceAux, NULL) != 0)
	{
		printf("SDL_BlitSurface: %s\n", IMG_GetError());
		exit(1);
	}

	return surfaceAux;
}

