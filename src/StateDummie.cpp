/*
 * StateDummie.cpp
 *
 *  Created on: Jul 19, 2013
 *      Author: Carol
 */

#include "../headers/StateDummie.h"

void StateDummie::load(int pilha) {
	background = new Sprite("../images/time_vortex_pixel.png");
	//background->rotoZoom(0,0.5,0.5,true);
	contaRotacao = 0;
	rotacao = -5;

	time = 0;
	frameSkip = 0;

	animacaoTardis = new Sprite("../images/tardis_voando.png");
	tardisX = 300;
	tardisY = 200;

	tardisWidth = 186;
	tardisHeight = 136;

	currentFrame = 0;
	maxFrame = 29;

	currentFrameVortex = 0;
	maxFrameVortex = 10;

	sfxBackground = new Audio("../sfx/temaPrincipal.wav",1);
	sfxBackground->play(0);
}

int StateDummie::unload() {
	return 0;

}
int StateDummie::update(int deltaFrame){
	time += deltaFrame;
	frameSkip = time / FRAME_TIME;
	time = time % FRAME_TIME;

	if(frameSkip){
		//background
		/*background->rotoZoom(rotacao,1,1,true);
		contaRotacao++;
		if(contaRotacao > 72){
			rotacao = 5;
			contaRotacao = 0;
		}
		else
			rotacao-=5;*/
		currentFrameVortex++;
		if(currentFrameVortex > maxFrameVortex)
			currentFrameVortex = 0;


		//tardis
		currentFrame++;
		if(currentFrame > maxFrame)
			currentFrame = 0;
	}

	background->clip(0,currentFrameVortex*334,400,334);
	animacaoTardis->clip(currentFrame*tardisWidth,0,tardisWidth,tardisHeight);

	//printf("contaRotacao: %d\n",contaRotacao);

	return ESTADO_DUMMIE;

}
void StateDummie::render(){
	background->render(200,44);
	animacaoTardis->render(tardisX, tardisY);
}

void StateDummie::processEvents(){

}
