/*
 * GameObject.h
 *
 *  Created on: May 19, 2013
 *      Author: LOUISE
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Sprite.h"
// #include "SDLBase.h"
// #include "GameObject.h"
#include "BoundingBox.h"

using namespace std;

class GameObject {

public:
	BoundingBox box;


	GameObject(float x, float y, float w, float h);
	virtual ~GameObject();
	virtual bool collidesWith(SDL_Rect *rect) = 0;
	virtual int update(int dt)=0;
	virtual void render()=0;

};

#endif /* GAMEOBJECT_H_ */
//
