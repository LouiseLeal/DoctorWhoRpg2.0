/*
 * GameObject.cpp
 *
 *  Created on: May 19, 2013
 *      Author: LOUISE
 */

#include "../headers/GameObject.h"

using namespace std;

GameObject::GameObject(float x, float y, float w, float h) {
	box.posX=x;
	box.posY=y;
	box.w=w;
	box.h=h;
}

GameObject::~GameObject() {

}

