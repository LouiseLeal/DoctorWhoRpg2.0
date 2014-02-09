/*
 * InputManager.h
 *
 *  Created on: May 14, 2013
 *      Author: Carol
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define N_KEYS 320
#define N_MOUSE_BUTTON 7

#include "SDLBase.h"

class InputManager{
public:
	static InputManager *getInputManager();

	void update();
	bool isKeyDown(int key);
	bool isKeyUp(int key);
	bool isKeyPressed(int key);
	bool isMouseDown(int button);
	bool isMouseUp(int button);
	bool isMousePressed(unsigned char button);
	int mousePosX() {return mouseX;};
	int mousePosY() {return mouseY;};
	bool isMouseInside(SDL_Rect *rect);
	bool QuitGame() {return quitGame;};

private:
	void cleanArrays();

	unsigned char mouse; //guarda o estado do mouse
	unsigned char *teclado; //guarda o estado do teclado
	bool keyDown[N_KEYS]; //guarda as teclas pressionadas do teclado
	bool keyUp[N_KEYS]; //guarda as teclas liberadas do teclado
	bool mouseDown[N_MOUSE_BUTTON]; //guarda as teclas pressionadas do mouse
	bool mouseUp[N_MOUSE_BUTTON]; //guarda as teclas liberadas do mouse
	int mouseX;
	int mouseY;
	bool quitGame; //evento do fim do jogo

	static InputManager *instance; //referencia da classe (singleton)

};


#endif /* INPUTMANAGER_H_ */
