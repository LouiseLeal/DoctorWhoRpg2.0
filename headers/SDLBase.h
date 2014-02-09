#ifndef SDLBASE_H_
#define SDLBASE_H_

//includes SDL
// #include "../FrameWorks/SDL.framework/Versions/A/Headers/SDL.h"
// #include "../FrameWorks/SDL_image.framework/Versions/A/Headers/SDL_image.h"
// #include "../FrameWorks/SDL_mixer.framework/Versions/A/Headers/SDL_mixer.h"
// #include "../FrameWorks/SDL_ttf.framework/Versions/A/Headers/SDL_ttf.h"
// #include "../FrameWorks/SDL_gfx.framework/Versions/A/Headers/SDL_rotozoom.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

//includes C / C++
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <math.h>

//include do tinyxml
#include "tinyxml2.h"

//includes do jogo
#include "Types.h"
#include "Constantes.h"
#include "Camera.h"


//definicoes
//#define FPS 1000/30
#define TILE_SIZE 64
#define IMAGE_COLUMNS 5
#define IMAGE_LINES 5
#define FRAME_TIME 100

using std::string;
using std::vector;
using namespace tinyxml2;

class SDLBase{

public:
	static int inicializaSDL();
	static void finalizaSDL();
	static SDL_Surface *getSurface();
	static SDL_Surface *loadImage(string);
	static void renderSurface(SDL_Surface* , SDL_Rect *, SDL_Rect *);
	static void updateScreen();
	static void drawLine(int x1, int y1, int x2, int y2, int rgb, int spacing);
	static SDL_Surface *clip(SDL_Surface *original, SDL_Rect *clip);
	static SDL_Surface *rotoZoom(SDL_Surface *surface, float angle, double scaleX, double scaleY);

	static SDL_Surface *screen;
	static int LEVEL_DIFICULDADE;
	static int FPS;
	static string strLanguage;
};


#endif /* SDLBASE_H_ */
