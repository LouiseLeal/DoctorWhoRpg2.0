/*
 * StateCasaRose.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: Carol
 */


#include "../headers/StateCasaRose.h"

void StateCasaRose::load(int pilha){
	tileSet = new TileSet(64,64, "../images/TileSetLondres.png");
	tileMap = new TileMap("../resources/TileMapCasaRose.txt", tileSet);
	background = new Sprite("../images/backgroundCasaRose.png");
	spriteTardisFade = new Sprite("../images/tardis_fade.png");

	currentFrameTardis = 0;
	maxFrameTardis = 4;

	//cria fantasmas
	string fileName = "../resources/fantasma0.xml";
	Sprite *sprite = new Sprite("../images/ghosts.png");
	fantasma = new PersonagemAtivo(fileName,"fantasmas0", sprite);

//	string strXml = "../resources/dialogo";
//	strXml += SDLBase::strLanguage;
//	cena = new Cena(strXml);
//	contaTempo = 0;

	rostoPersonagem = NULL;
	caixaDialogo = NULL;
	sfxBackground = new Audio("../sfx/temaCasaRose.wav",1);
	sfxTardisLanding = new Audio("../sfx/tardisLanding.wav",1);

	//iniciar texto TARDIS
	string fontFile = "../fonts/CCRedAlert.ttf";
	SDL_Color corBranco = { 255, 255, 255 };

	txtTARDIS = new Text(fontFile, "TARDIS",40,TTF_STYLE_NORMAL, corBranco, 349,439);
	txtTimeAndRelative = new Text(fontFile, "Time And Relative Dimension In Space",36,TTF_STYLE_NORMAL, corBranco, 125,495);

	//timer.start();
}

void StateCasaRose::begin(GrupoCenario *grupoMocinhos) {
	string strXml = "../resources/dialogo";
	strXml += SDLBase::strLanguage;
	cena = new Cena(strXml);
	grupoCenario = grupoMocinhos;
	returnUpdate = ESTADO_CASAROSE;
	//printf("Tamanho vet frames da cena: %d\n",cena->vetFrames.size());
	//printf("Tamanho vet grupo cenario: %d\n",grupoCenario->vetorPersonages.size());

	//volta para o frame inicial
	currentFrame = cena->vetFrames.front();
	grupoCenario->vetorPersonages[0]->boundingBox.posX  = currentFrame.vetPersonagem[0].posX;
	grupoCenario->vetorPersonages[0]->boundingBox.posY  = currentFrame.vetPersonagem[0].posY;
	grupoCenario->vetorPersonages[1]->boundingBox.posX  = currentFrame.vetPersonagem[1].posX;
	grupoCenario->vetorPersonages[1]->boundingBox.posY  = currentFrame.vetPersonagem[1].posY;
	grupoCenario->vetorPersonages[2]->boundingBox.posX  = currentFrame.vetPersonagem[2].posX;
	grupoCenario->vetorPersonages[2]->boundingBox.posY  = currentFrame.vetPersonagem[2].posY;

	//render caixa texto inicial nao
	renderCaixaTexto = false;

	//time para o som da tardis
	timer.start();

	//som da tardis
	sfxTardisLanding->play(0);
	seguraRender = true;

	//conta tempo de algo
	contaTempo = 0;
	//sfxBackground->play(5);

	seguraRender = true;
	ligaMusica = true;

	Camera::cameraX = 0;
	Camera::cameraY = 0;

	currentFrameTardis = 0;
	maxFrameTardis = 4;
	somaFrameTardis = 1;
}

int StateCasaRose::update(int deltaFrame){
	time += deltaFrame;
	frameSkip = time / FRAME_TIME;
	time = time % FRAME_TIME;

	if(timer.getTime() < 12000){
		if(frameSkip){
			//printf("retorno do timer no update\n");
			currentFrameTardis += somaFrameTardis;
			if(currentFrameTardis > maxFrameTardis){
				somaFrameTardis = -1;
				currentFrameTardis += somaFrameTardis;
			}
			else if(currentFrameTardis < 0){
				somaFrameTardis = 1;
				currentFrameTardis += somaFrameTardis;
			}
		}

		return returnUpdate;
	}
	else {
		if(timer.getTime() > 1200 && ligaMusica){
			sfxBackground->play(5);
			ligaMusica = false;
			//printf("liga musica background\n");
		}

		seguraRender = false;
	}

	bool seguraUpdate = false;
	processEvents();
	//se alguem estiver animando, segura o update
	/*for(int i = 0 ; i < grupoCenario->vetorPersonages.size(); i++)
		if(grupoCenario->vetorPersonages[i]->currentAnimation->running){
			seguraUpdate = true;
			printf("Animacao: %s\n",grupoCenario->vetorPersonages[i]->currentAnimation[i].name.c_str());
		}*/

	if(caixaDialogo != NULL && renderCaixaTexto == true){
		/*if(caixaDialogo->TXT_END)
			renderCaixaTexto = false;
		else{*/
			seguraUpdate = true;
			caixaDialogo->update(deltaFrame);
		//}
	}

	if(seguraUpdate){
		//printf("retornoUpdate: %d\n",returnUpdate);
		if(returnUpdate != ESTADO_CASAROSE){
			sfxBackground->stop();
			sfxTardisLanding->stop();
			//printf("parei todas as musicas!!! retuorno update: %d\n",returnUpdate);
		}
		//printf("retorno do segura update\n");
		return returnUpdate;
	}

	if(frameSkip){
		contaTempo++;
		currentFrame.tempo--;

		//verifica posicoes
		for(int i = 0 ; i < grupoCenario->vetorPersonages.size(); i++) {
			//printf("Personagem i:%d\n",i);
			//printf("posicao: %d %d\n",currentFrame.vetPersonagem[i].posX,currentFrame.vetPersonagem[i].posY);

			if(grupoCenario->vetorPersonages[i]->boundingBox.posX == -1 || currentFrame.vetPersonagem[i].posX == -1) {
				grupoCenario->vetorPersonages[i]->boundingBox.posX = currentFrame.vetPersonagem[i].posX;
				grupoCenario->vetorPersonages[i]->boundingBox.posY = currentFrame.vetPersonagem[i].posY;
			}
			else if(currentFrame.vetPersonagem[i].posX != grupoCenario->vetorPersonages[i]->boundingBox.posX){
				int diferenca = grupoCenario->vetorPersonages[i]->boundingBox.posX - currentFrame.vetPersonagem[i].posX;
				if(abs(diferenca) <= 4){
					grupoCenario->vetorPersonages[i]->boundingBox.posX = currentFrame.vetPersonagem[i].posX;
				}
				else {
					int deslocamento;
					if(currentFrame.tempo == 0)
						deslocamento = abs(diferenca);
					else
						deslocamento = abs(diferenca) / currentFrame.tempo;

					if(diferenca < 0)
						grupoCenario->vetorPersonages[i]->boundingBox.posX += deslocamento;
					else
						grupoCenario->vetorPersonages[i]->boundingBox.posX -= deslocamento;
				}
			}
			else if(currentFrame.vetPersonagem[i].posY != grupoCenario->vetorPersonages[i]->boundingBox.posY){
				int diferenca = grupoCenario->vetorPersonages[i]->boundingBox.posY - currentFrame.vetPersonagem[i].posY;
				if(abs(diferenca) <= 4){
					grupoCenario->vetorPersonages[i]->boundingBox.posY = currentFrame.vetPersonagem[i].posY;
				}
				else {
					int deslocamento;
					if(currentFrame.tempo == 0)
						deslocamento = abs(diferenca);
					else
						deslocamento = abs(diferenca) / currentFrame.tempo;

					if(diferenca < 0)
						grupoCenario->vetorPersonages[i]->boundingBox.posY += deslocamento;
					else
						grupoCenario->vetorPersonages[i]->boundingBox.posY -= deslocamento;
				}
			}


			//verifica animacao do personagem
			if(strcmp(grupoCenario->vetorPersonages[i]->currentAnimation->name.c_str(),currentFrame.vetPersonagem[i].direcao.c_str())){
				grupoCenario->vetorPersonages[i]->setCurrentAnimation(currentFrame.vetPersonagem[i].direcao);
				//printf("Nova animacao: %s\n",grupoCenario->vetorPersonages[i]->currentAnimation->name.c_str());
			}
			grupoCenario->vetorPersonages[i]->update(deltaFrame);

			//printf("Pos[%d]: %f %f\n",grupoCenario->vetorPersonages[i]->boundingBox.posX,grupoCenario->vetorPersonages[i]->boundingBox.posY);

			//verifica fala
			if(currentFrame.vetPersonagem[i].fala == 1 && !renderCaixaTexto) {
				renderCaixaTexto = true;
				if(rostoPersonagem != NULL)
					rostoPersonagem->~Sprite();

				string nomeImagem = "../images/";
				nomeImagem += grupoCenario->vetorPersonages[i]->nome;
				nomeImagem += "_";

				nomeImagem += currentFrame.vetPersonagem[i].expressao;
				nomeImagem += ".png";

				rostoPersonagem = new Sprite(nomeImagem);

				fala = currentFrame.vetPersonagem[i].conteudo;
				printf("Frame: %d I: %d\n",currentFrame.frame, i);


				if(caixaDialogo == NULL){
					//printf("caixa nula! vamos comecar\n!");
					caixaDialogo = new CaixaTexto(fala);
				}
				else
					caixaDialogo->setText(fala);
				caixaDialogo->update(deltaFrame);
			}

		}


		fantasma->boundingBox.posX = currentFrame.fantasma.posX;
		fantasma->boundingBox.posY = currentFrame.fantasma.posY;
		if(strcmp(fantasma->currentAnimation->name.c_str(),currentFrame.fantasma.direcao.c_str()) && currentFrame.fantasma.posX != -1){
			fantasma->setCurrentAnimation(currentFrame.fantasma.direcao);
			//printf("Nova animacao: %s\n",grupoCenario->vetorPersonages[i]->currentAnimation->name.c_str());
		}
		fantasma->update(deltaFrame);

		//printf("Current time: %d\n",currentFrame.tempo);
		if(currentFrame.tempo <= 0){
			//printf("currentFrame: %d size: %d\n",currentFrame.frame,cena->vetFrames.size());
			//printf("muda frame - current: %d prox: %d\n",currentFrame.frame, currentFrame.frame + 1);
			if(currentFrame.frame < cena->vetFrames.size() - 1){
				currentFrame = cena->vetFrames[currentFrame.frame + 1];
			}
			else{
				sfxBackground->stop();
				returnUpdate = ESTADO_CENARIO;
				if(returnUpdate != ESTADO_CASAROSE){
					sfxBackground->stop();
					sfxTardisLanding->stop();
				}
			}
		}

	}

	//printf("retornoUpdate: %d\n",returnUpdate);
	if(returnUpdate != ESTADO_CASAROSE){
		//printf("vou desligar os sons!!!\n");
		sfxBackground->stop();
		sfxTardisLanding->stop();
	}

	//printf("retorno fim do  update. EstadoL %d\n",returnUpdate);
	return returnUpdate;
}

void StateCasaRose::render(){
	background->render(0,0);

	if(!seguraRender) {
		tileMap->render();
		for(int i = 0 ; i < grupoCenario->vetorPersonages.size(); i++)
			grupoCenario->vetorPersonages[i]->render();

		fantasma->render();

		if(renderCaixaTexto){
			caixaDialogo->render();
			rostoPersonagem->render(caixaDialogo->posX + 500, caixaDialogo->posY - 8);
		}
	}
	else {
		spriteTardisFade->clip(currentFrameTardis*(spriteTardisFade->getWidth()/4),0,(spriteTardisFade->getWidth()/4),(spriteTardisFade->getHeight()));
		int tardisX = 400 - (spriteTardisFade->getWidth()/2)/4;
		int tardisY = 300 - spriteTardisFade->getHeight()/2;
		spriteTardisFade->render(tardisX,tardisY);
		txtTARDIS->render();
		txtTimeAndRelative->render();
	}
}

int StateCasaRose::unload(){
	return 0;
}

void StateCasaRose::processEvents(){
	InputManager::getInputManager()->update();
	if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		if(caixaDialogo->TXT_END)
			renderCaixaTexto = false;
		else if(caixaDialogo->PAUSE == true){
			caixaDialogo->PAUSE = false;
			caixaDialogo->countLinhasEscritas = 0;
		}
	}

	if (InputManager::getInputManager()->isKeyDown(SDLK_ESCAPE)) {
		returnUpdate = ESTADO_CENARIO;
		sfxBackground->stop();
	}
}

