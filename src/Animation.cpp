/*
 * Animation.cpp
 *
 *  Created on: Jun 1, 2013
 *      Author: Carol e Louise
 */



#include "../headers/Animation.h"

//comentario
Animation::Animation(Sprite *sprite, int linhaSprite, int nSprites, int loop, string nome, DADOS_ANIMACAO dadosAnimacao, Audio *sfx){
	refSprite = sprite;
	time = 0;
	frameSkip = 0;
	Animation::linhaSprite = linhaSprite;
	Animation::nSprites = nSprites;
	Animation::loop = loop;
	clipX = 0;
	clipY = 0;
	running = false;
	frameTime = FRAME_TIME;
	name = nome;

	currentFrame = 0;
	ultimoFrame = nSprites - 1;

	sfxAnimation = sfx;
	//printf("nome: %s\n",nome.c_str());
	//printf("ultimo frame %d\n",ultimoFrame);

	Animation::dadosAnimacao = dadosAnimacao;
}

void Animation::reset() {
	running = false;
	currentFrame = 0;
}

bool Animation::animationRunning(){
	if(!loop) {
		return running;
	}
	return false;
}

void Animation::start(){
	//coloca animacoes sem loop como iniciando
	if(!loop) {
		running = true;
		timer.start();
		currentFrame = 0;
	}
	else{
	//animacoes em loop sao consideradas sempre como estaticas pois podem parar em qualquer frame
		running = false;
	}
}

void Animation::update(int deltaFrame){//, int spriteW, int spriteH, int imageCollumns, int imageLines) {
	time += deltaFrame;
	frameSkip = time / FRAME_TIME;
	time = time % FRAME_TIME;
	//printf("nome: %s\n",name.c_str());
	//printf("Fs: %d t: %d ft: %d cf: %d is: %d np: %d\n",frameSkip, time, frameTime, currentFrame, linhaSprite, nSprites);
	//printf("frame: %d\t fim: %f\n",currentFrame,ultimoFrame);
	if(frameSkip){
		currentFrame += 1;
		//if(currentFrame >= ultimoFrame){
		if(currentFrame > ultimoFrame){
			if(!loop){
				//mantem o frame no ultimo
				currentFrame = ultimoFrame;
				running = false;
				//printf("Tempo animacao %s: %d\n",name.c_str(),timer.getTime());
			}
			else {
				currentFrame = 0;
			}
		}
	}

	clipY = dadosAnimacao.altura;
	clipX = dadosAnimacao.largura * currentFrame;

	//for(int i = 0; i < currentFrame - 1; i++){
	//	clipX += dadosAnimacao.vetCropX[i];
	//}

	//printf("sprite\n");
	//printf("%d\t%d\t%d %d %d %d\n",currentFrame,linhaSprite,clipX, clipY,dadosAnimacao.largura,64);
	//printf("Clipx %d Clipy %d \n",clipX, clipY);
	//printf("CropY: %d\n",dadosAnimacao.vetCropY[currentFrame]);
	refSprite->clip(clipX,clipY,dadosAnimacao.largura,dadosAnimacao.vetCropY[currentFrame]);
	//printf("sprite fim\n");
}

void Animation::render(int x, int y){
	refSprite->render(x,y);
}

