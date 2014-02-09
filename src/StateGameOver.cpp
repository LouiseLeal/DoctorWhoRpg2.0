/*
 * StateGameOver.cpp
 *
 *  Created on: Jul 17, 2013
 *      Author: Carol
 */

#include "../headers/StateGameOver.h"

void StateGameOver::load(int pilha) {
	string fontFile = "../fonts/CCRedAlert.ttf";
	SDL_Color corBranco = { 255, 255, 255 };

	txtGameOver = new Text(fontFile,"GAME OVER!",52,TTF_STYLE_NORMAL,corBranco,260,200);

	background = new Sprite("../images/backgroundGameOver.png");

	string strRetry = "Retry";
	string strQuit = "Quit";
	vector<string> vetStrings;
	vetStrings.push_back(strRetry);
	vetStrings.push_back(strQuit);

	Sprite *sprite = new Sprite("../images/seta.gif");
	opcoes = new TextOpcoes(vetStrings, 395,300,50,sprite);

	sfxBackground = new Audio("../sfx/GAMEOVER.wav",1);

	returnUpdate = ESTADO_GAME_OVER;
}

void StateGameOver::begin(){
	sfxBackground->play(5);
}

int StateGameOver::unload() {
	return 0;

}
int StateGameOver::update(int deltaFrame){
	processEvents();
	if(returnUpdate != ESTADO_GAME_OVER)
		sfxBackground->stop();
	return returnUpdate;

}
void StateGameOver::render(){
	background->render(0,0);
	txtGameOver->render();
	opcoes->render(true);
}

void StateGameOver::processEvents(){
	InputManager::getInputManager()->update();
	if (InputManager::getInputManager()->isKeyDown(SDLK_UP)) {
		opcoes->update(false);

	}
	if (InputManager::getInputManager()->isKeyDown(SDLK_DOWN)) {
		opcoes->update(true);

	}
	if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		int opcaoEscolhida = opcoes->getOpcao();
		if(opcaoEscolhida == 0)
			returnUpdate = ESTADO_SELECAO;
		else
			returnUpdate = ESTADO_INTRODUCAO;
	}
}
