/*
 * StateCredito.cpp
 *
 *  Created on: Jul 26, 2013
 *      Author: Carol
 */

#include "../headers/StateCreditos.h"

void StateCreditos::load(int pilha) {

	background = new Sprite("../images/CREDITOS.png");
	sfxBackground = new Audio("../sfx/temaPrincipal.wav",1);

	returnUpdate = ESTADO_CREDITOS;
}

void StateCreditos::begin() {
	sfxBackground->play(5);
	Camera::cameraX = 0;
	Camera::cameraY = 0;
	timer.start();
}

int StateCreditos::unload() {
	return 0;

}
int StateCreditos::update(int deltaFrame){
	processEvents();

	time += deltaFrame;
	frameSkip = time / FRAME_TIME;
	time = time % FRAME_TIME;

	if(frameSkip){
		Camera::cameraY += 4;
	}

	if(timer.getTime() > 78000)
		return ESTADO_MENU;

	return returnUpdate;

}
void StateCreditos::render(){
	background->render(0 - Camera::cameraX,0 - Camera::cameraY);
}

void StateCreditos::processEvents(){
	InputManager::getInputManager()->update();
	if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		returnUpdate = ESTADO_MENU;
	}
}



