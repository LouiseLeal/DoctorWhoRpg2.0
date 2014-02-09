/*
 * InputManager.cpp
 *
 *  Created on: May 14, 2013
 *      Author: Carol
 */
#include "../headers/InputManager.h"

InputManager *InputManager::instance = NULL;

InputManager *InputManager::getInputManager(){
	if(instance == NULL)
		instance = new InputManager();

	 return instance;
}

void InputManager::update() {
	SDL_Event event;
	cleanArrays();

	//atualiza mouse e teclado
	mouse = SDL_GetMouseState(&mouseX,&mouseY);
	teclado = SDL_GetKeyState(NULL);

	while( SDL_PollEvent(&event) ) {
		switch (event.type) {
			case SDL_KEYDOWN:
				keyDown[event.key.keysym.sym] = true;
				keyUp[event.key.keysym.sym] = false;
				break;
			case SDL_KEYUP:
				keyUp[event.key.keysym.sym] = true;
				keyDown[event.key.keysym.sym] = false;
				break;
			case SDL_MOUSEMOTION:
				mouseX = event.button.x;
				mouseY = event.button.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseDown[event.button.button] = true;
				mouseUp[event.button.button] = false;
				break;
			case SDL_MOUSEBUTTONUP:
				mouseUp[event.button.button] = true;
				mouseDown[event.button.button] = false;
				break;
			case SDL_QUIT:
				quitGame = true;
				break;
		}
	}
}

bool InputManager::isKeyPressed(int key){
	if(teclado[key])
		return true;
	else
		return false;
}

bool InputManager::isMousePressed(unsigned char button){

	if(mouse == SDL_BUTTON(button))
		return true;
	else
		return false;
}

bool InputManager::isMouseInside(SDL_Rect *rect) {
	if((mouseX >= rect->x) && (mouseX <= (rect->x + rect->w))) {
		if((mouseY >= rect->y) && (mouseY <= (rect->y + rect->y)))
			return true;
		else
			return false;
	}
	else
		return false;
}

void InputManager::cleanArrays(){
	int i;
	for(i= 0; i < 320; i++){
		keyDown[i] = 0;
		keyUp[i] = 0;
	}

	for(i= 0; i < 7; i++){
		mouseDown[i] = 0;
		mouseUp[i] = 0;
	}
}

bool InputManager::isKeyDown(int key)
{
	return keyDown[key];
}

bool InputManager::isKeyUp(int key)
{
	return keyUp[key];
}

bool InputManager::isMouseDown(int button)
{
	return mouseDown[button];
}

bool InputManager::isMouseUp(int button)
{
	return mouseUp[button];
}
