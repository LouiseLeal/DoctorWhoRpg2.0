/*
 * Sprite.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: LOUISE
 */
#include "../headers/Sprite.h"
#include "../headers/SDLBase.h"


using namespace std;

Sprite::Sprite(string arquivo)
{
   surface=NULL;
   surfaceRotoZoom = NULL;
   angle=0;
   scaleX=1.0;
   scaleY=1.0;
   load(arquivo);
}
Sprite::~Sprite(){

    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
}
/*
 * load(string): verifica se a surface esta descarregada,
 * em seguida carrega surface
 */
void Sprite::load(std::string arquivo){
    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
    surface=SDLBase::loadImage(arquivo);
    clipRectSprite.x=0;
    clipRectSprite.y=0;
    clipRectSprite.w=surface->w;
    clipRectSprite.h=surface->h;
}
/*
 * clip(int,int,int,int):define os parametros do retangulo clipRect
 */
void Sprite::clip(int x, int y, int w, int h){
		clipRectSprite.x=x;
		clipRectSprite.y=y;
		clipRectSprite.w=w;
		clipRectSprite.h=h;
		// if(surfaceRotoZoom!=NULL){
		//    	rotoZoom(angle,scaleX,scaleY,true);
		// }

}
/*
 * getClip(): retorna o retangulo clipRect;
 */
SDL_Rect Sprite::getClip(){
    return clipRectSprite;
}
/*
 *render(x,y): renderiza a surface na posiçãpo
 *parametros x e y.
 */
void Sprite::render(int x, int y){
    SDL_Rect dst;
    dst.x=x;
    dst.y=y;
    dst.w=0;
    dst.h=0;
    // if(surfaceRotoZoom == NULL){
    	SDLBase::renderSurface(surface,&clipRectSprite,&dst);
    // }else{
    // 	dst.x=x+(clipRectSprite.w/2 - surfaceRotoZoom->w/2);
    // 	dst.y=y+(clipRectSprite.h/2 - surfaceRotoZoom->h/2);

    // 	SDLBase::renderSurface(surfaceRotoZoom,NULL,&dst);
    // }

}
/*
 * getWidth():retorna parametro SDL_Rect->w,
 * do surface
 */
int Sprite::getWidth(){
	// if(surfaceRotoZoom==NULL)
		return surface->w;
	// else
	// 	return surfaceRotoZoom->w;
}
/*
* getHeight():retorna parametro SDL_Rect->h,
* do surface.
*/
int Sprite::getHeight(){
    // if(surfaceRotoZoom==NULL)
    	return surface->h;
	// else
	// 	return surfaceRotoZoom->h;
}
// void Sprite::rotoZoom(float angle, float scaleX, float scaleY, bool force){
// 	SDL_Rect auxRect;
// 	if((this->angle!=angle || this->scaleX!= scaleX || this->scaleY!=scaleY) || force == true){
// 			if(surfaceRotoZoom !=NULL){
// 				SDL_FreeSurface(surfaceRotoZoom);
// 				surfaceRotoZoom=NULL;
// 			}
// 			this->angle = angle;
// 			this->scaleX = scaleX;
// 			this->scaleY = scaleY;
// 			if(scaleX!= 1|| scaleY !=1 ||force){
// 				auxRect.x=clipRectSprite.x;
// 				auxRect.y=clipRectSprite.y;
// 				auxRect.w=clipRectSprite.w;
// 				auxRect.h=clipRectSprite.h;

// 				surfaceRotoZoom = SDLBase::clip(surface, &auxRect);
// 				surfaceRotoZoom = SDLBase::rotoZoom(surfaceRotoZoom,angle,scaleX,scaleY);
// 			}else{
// 				surfaceRotoZoom = SDLBase::rotoZoom(surface,angle,scaleX,scaleY);
// 			}
// 			clipRectSprite.w = clipRectSprite.w*scaleX;
// 			clipRectSprite.h = clipRectSprite.h*scaleY;

// 			//clipRectSprite = surfaceRotoZoom->clip_rect;

// 		}


// }
void Sprite::restore(){
	// if(surfaceRotoZoom !=NULL){
	// 	delete(surfaceRotoZoom);
	// 	surfaceRotoZoom = NULL;
	// }
}

