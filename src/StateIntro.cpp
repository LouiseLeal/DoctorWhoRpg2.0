/*
 * StateIntro.cpp
 *
 *  Created on: Jun 30, 2013
 *      Author: Carol
 */

#include "../headers/StateIntro.h"

void StateIntro::load(int pilha) {
	background = new Sprite("../images/earth.png");
	caixaMonologo = new CaixaTexto("Planet Earth. This is where I was born, and this is where I died. The first 19 years of my life, nothing happened. Nothing at all. Not ever. And then I met a man called the Doctor. A man who can change his face. He took me away from home in his magical machine. He showed me the whole of time and space. I thought it would never end. That's what I thought. But then came the army of ghosts, and came torchwood and the war. That's when it all ended. This is the story of how I died.");
	sfxBackground = new Audio("../sfx/temaIntroducaoMonologo.wav",1);
}

void StateIntro::begin() {
	sfxBackground->play(5);
	returnUpdate = ESTADO_INTRODUCAO;
	if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0)
		caixaMonologo = new CaixaTexto("Planet Earth. This is where I was born, and this is where I died. The first 19 years of my life, nothing happened. Nothing at all. Not ever. And then I met a man called the Doctor. A man who can change his face. He took me away from home in his magical machine. He showed me the whole of time and space. I thought it would never end. That's what I thought. But then came the army of ghosts, and came torchwood and the war. That's when it all ended. This is the story of how I died.");
	else
		caixaMonologo = new CaixaTexto("Planeta terra. O lugar onde eu nasci. O lugar onde eu morri. Nos primeiros 19 anos da minha vida nada aconteceu. E entao eu conheci um homem chamado 'Doctor'. Um homem que podia mudar sua aparencia. Ele me levou em sua maquina magica. Ele me mostrou todo o tempo e espaco e eu pensei que nunca acabaria. Foi o que eu pensei. Mas entao veio o exercito de fantasmas e torchwood e a guerra. Foi quando tudo acabou. Essa é a historia de como eu morri.");
}

int StateIntro::unload(){
	return 0;

}

int StateIntro::update(int deltaFrame){
	processEvents();
	caixaMonologo->update(deltaFrame);
	if(caixaMonologo->TXT_END && !caixaMonologo->PAUSE){
		sfxBackground->stop();
		return ESTADO_CASAROSE;
	}
	else
		return returnUpdate;
}

void StateIntro::render(){
	background->render(0,0);
	caixaMonologo->render();

}

void StateIntro::processEvents() {
	InputManager::getInputManager()->update();
	if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		caixaMonologo->PAUSE = false;
		caixaMonologo->countLinhasEscritas = 0;
	}
	if (InputManager::getInputManager()->isKeyDown(SDLK_ESCAPE)) {
		sfxBackground->stop();
		returnUpdate = ESTADO_CASAROSE;
	}
}
