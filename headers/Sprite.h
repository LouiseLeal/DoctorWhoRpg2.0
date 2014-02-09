#ifndef SPRITE_H
#define SPRITE_H

#include "SDLBase.h"

class Sprite {
public:
	/// Atributos

	SDL_Surface* surface;
	SDL_Rect clipRectSprite;
	// trab 3
	SDL_Surface* surfaceRotoZoom;
	float angle;
	float scaleX, scaleY;


	/// Métodos
	Sprite(std::string arquivo);
	virtual ~Sprite();
	void load(std::string arquivo);
	void clip(int x, int y, int w, int h);
	SDL_Rect getClip();
	int getWidth();
	int getHeight();
	void render(int x, int y);
	// trab3

	void rotoZoom(float angle, float scaleX = 1.0f, float scaleY = 1.0f,
			bool forca = true);
	void restore();
	virtual void update(int dt){};

};

#endif // SPRITE_H
