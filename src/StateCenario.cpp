/*
 * StateCenario.cpp
 *
 *  Created on: Jun 11, 2013
 *      Author: Carol
 */


#include "../headers/StateCenario.h"

void StateCenario::load(int pilha){
	Sprite *spriteDoc = new Sprite("../images/doctor.png");
	Sprite *spriteRose = new Sprite("../images/rose.png");
	Sprite *spriteJackie = new Sprite("../images/jackie.png");
	background = new Sprite("../images/big_ben.png");
	spriteFadeBatalha = new Sprite("../images/fade_screen.png");
	spriteToBeContinued = new Sprite("../images/fade_fim.png");

	tileSet = new TileSet(64,64, "../images/TileSetLondres.png");
	tileMap = new TileMap("../resources/TileMapLondres.txt", tileSet);

	limiteMapaLeft = tileSet->columns*64;
	limiteMapaBotton = tileSet->lines*64;

	//printf("sprites feitos\n");
	grupoCenario = new GrupoCenario(spriteDoc,spriteRose, spriteJackie);
	//printf("fim grupo cenrio load\n");

	//pos inicial do doctor
	grupoCenario->vetorPersonages.front()->boundingBox.posX = 568;
	grupoCenario->vetorPersonages.front()->boundingBox.posY = 668;
	oldX = 1670;
	oldY = 1170;

	Camera::cameraX = grupoCenario->vetorPersonages.front()->boundingBox.posX - 400 + 32;
	Camera::cameraY = grupoCenario->vetorPersonages.front()->boundingBox.posY - 300 + 32;

	//estado de retorno no update
	Camera::cameraX = 0;
	Camera::cameraY = 0;
	returnUpdate = ESTADO_CENARIO;
	limiteProbBatalha = 25;

	sfxBackgroundMusic = new Audio("../sfx/londresSong.wav",1);
	sfxEnterBattle = new Audio("../sfx/battleSfx.wav",1);
	EM_ESPERA = false;
	renderCaixaTexto = false;

	caixaDialogo = new CaixaTexto("vazio");

	geraInativos();

	TILE_BATALHA tileAux;
	tileAux.x = 28;
	tileAux.y = 22;
	vetTilesBatalha.push_back(tileAux);
	for(int i = 0; i < 19; i++) {
		tileAux.x = (int)(rand() % 48);
		tileAux.y = (int)(rand() % 40);
		vetTilesBatalha.push_back(tileAux);
		//printf("tileAuxx %d tileAuxy %d\n",tileAux.x,tileAux.y);
	}

	currentFrameFadeBatalha = 0;
	maxFrameFadeBatalha = 7;

	TARDIS_TILE_X = 37; //tile 37
	TARDIS_TILE_Y = 32; //tile 32
	waitTARDIS = 2000;
	ultimoTempoTARDIS = 0;
	currentFrameTARDIS = 0;
	maxFrameTARDIS = 5;
}

void StateCenario::begin(){
	returnUpdate = ESTADO_CENARIO;
	ENTRA_TARDIS = false;
	grupoCenario->vetorPersonages.front()->boundingBox.posX = oldX;
	grupoCenario->vetorPersonages.front()->boundingBox.posY = oldY;
	grupoCenario->vetorPersonages.front()->setCurrentAnimation("parado_frente");
	timerTransicao.pause();
	EM_ESPERA = false;
	renderCaixaTexto = false;
	pbBatalhaEsq = 0;
	pbBatalhaDir = 0;
	pbBatalhaFre = 0;
	pbBatalhaCos = 0;
	limiteProbBatalha = 25;
	Camera::cameraX = grupoCenario->vetorPersonages.front()->boundingBox.posX - 400 + 32;
	Camera::cameraY = grupoCenario->vetorPersonages.front()->boundingBox.posY - 300 + 32;
	pbBatalhaCos = 0;
	pbBatalhaDir = 0;
	pbBatalhaEsq = 0;
	pbBatalhaFre = 0;

	currentFrameFadeBatalha = 0;
	maxFrameFadeBatalha = 7;
	ultimoFrame = 0;

	tocaIntroBatalha = false;

	currentFrameTARDIS = 0;
	maxFrameTARDIS = 5;
	ultimoTempoTARDIS = 0;

	sfxBackgroundMusic->play(500);
	geraInativos();
	printf("play musicaaa!\n");
}


int StateCenario::unload(){
	return 0;
}

int StateCenario::update(int deltaFrame){
	//printf("update grupo cenario.\n");
	//vai para o state de batalha

	if(!EM_ESPERA)
		processEvent();

	time += deltaFrame;
	frameSkip = time / FRAME_TIME;
	time = time % FRAME_TIME;

	Camera::cameraX = grupoCenario->vetorPersonages.front()->boundingBox.posX - 400 + 32;
	Camera::cameraY = grupoCenario->vetorPersonages.front()->boundingBox.posY - 300 + 32;

	grupoCenario->vetorPersonages.front()->update(deltaFrame);

	if(returnUpdate == ESTADO_BATALHA && !EM_ESPERA){
		printf("stop musica!!\n");
		sfxBackgroundMusic->stop();
//		sfxEnterBattle->stop();
		oldX = grupoCenario->vetorPersonages.front()->boundingBox.posX;
		oldY = grupoCenario->vetorPersonages.front()->boundingBox.posY;
		timerTransicao.start();
		EM_ESPERA = true;
		tocaIntroBatalha = true;
	}

	if(renderCaixaTexto)
		caixaDialogo->update(deltaFrame);

	if(ENTRA_TARDIS){
		sfxBackgroundMusic->stop();
		if(timerTARDIS.getTime() < waitTARDIS){
			//printf("Tempo: %d\n",timerTARDIS.getTime());
			if(timerTARDIS.getTime() - ultimoTempoTARDIS > 250 ){
				ultimoTempoTARDIS = timerTARDIS.getTime();
				currentFrameTARDIS++;
				//printf("CurrentFrame: %d\n",currentFrameTARDIS);
				if(currentFrameTARDIS > maxFrameTARDIS - 1)
					currentFrameTARDIS--;
			}

			return returnUpdate;
		}
		else {
			return ESTADO_CREDITOS;
		}
	}


	if(EM_ESPERA){
		if(timerTransicao.getTime() < 100 && tocaIntroBatalha){
			tocaIntroBatalha = false;
			sfxBackgroundMusic->stop();
			sfxEnterBattle->play(0);
		}
		if (timerTransicao.getTime() >= 2000){
			sfxEnterBattle->stop();
			return returnUpdate;
		}

		if(timerTransicao.getTime() - ultimoFrame > 285 ){
			ultimoFrame = timerTransicao.getTime();
			currentFrameFadeBatalha++;
			if(currentFrameFadeBatalha > maxFrameFadeBatalha)
				currentFrameFadeBatalha--;
		}
		//printf("currentFrame: %d\n",currentFrameFadeBatalha);

		return ESTADO_CENARIO;
	}
	else{
		if(returnUpdate != ESTADO_CENARIO){
			sfxEnterBattle->stop();
			sfxBackgroundMusic->stop();
			printf("stop musica fim update!\n");
		}
		return returnUpdate;
	}
}

void StateCenario::render(){
	tileMap->rederLayer(0);
	tileMap->rederLayer(1);
	grupoCenario->vetorPersonages.front()->render();

	for(vector<PersonagemInativo*>::iterator it = vetPersonagensInativos.begin(); it < vetPersonagensInativos.end(); it++)
		(*it)->render();

	tileMap->rederLayer(2);

	if(renderCaixaTexto)
		caixaDialogo->render();

	if(ENTRA_TARDIS){
		spriteToBeContinued->clip(currentFrameTARDIS*spriteToBeContinued->getWidth()/5,0,spriteToBeContinued->getWidth()/5, spriteToBeContinued->getHeight());
		spriteToBeContinued->render(0,0);
	}

	if(EM_ESPERA){
		spriteFadeBatalha->clip(currentFrameFadeBatalha*spriteFadeBatalha->getWidth()/7,0,spriteFadeBatalha->getWidth()/7, spriteFadeBatalha->getHeight());
		spriteFadeBatalha->render(0,0);
	}
}

void StateCenario::processEvent(){

	int coordX;
	int coordY;
	//probabilidade de ocorrer uma batalha
	// int probBatalha = 0;

	InputManager::getInputManager()->update();
	if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		if(caixaDialogo->TXT_END)
			renderCaixaTexto = false;
	}

	PersonagemAtivo *doctor = grupoCenario->vetorPersonages.front();
	Animation *currentAnimation = doctor->currentAnimation;

	oldX = doctor->boundingBox.posX;
	oldY = doctor->boundingBox.posY;

	bool input = false;
	//movimetnos
	if(!currentAnimation->animationRunning()) {
		//reseta animacoes sem loop quando terminam para o primeiro frame
		if(!currentAnimation->loop)
			currentAnimation->reset();

		//retorna para um estado especifico apos animacao sem loop
		if(!currentAnimation->loop && currentAnimation->nSprites > 1 ){
			doctor->setCurrentAnimation("posicao_batalha");
		}

		if( InputManager::getInputManager()->isKeyDown(SDLK_a) || InputManager::getInputManager()->isKeyPressed(SDLK_a)){
			doctor->setCurrentAnimation("andar_esq");
			doctor->boundingBox.posX -= DESLOCAMENTO;

			//verifica se a coordenada e negativa para fazer colisao com limite do mapa
			int parcialX = doctor->boundingBox.posX - doctor->boundingBox.w;
			if(parcialX > 0)
				coordX = parcialX / tileSet->tileWidth;
			else
				coordX = -1;

			coordY = ((int)doctor->boundingBox.posY / tileSet->tileHeight);

			if(verificaColisao(coordX, coordY, coordX, coordY-1))
				doctor->boundingBox.posX += DESLOCAMENTO;
			else
				pbBatalhaEsq+=4;

			input = true;

		}
		else if( InputManager::getInputManager()->isKeyDown(SDLK_d) || InputManager::getInputManager()->isKeyPressed(SDLK_d)){
			doctor->setCurrentAnimation("andar_dir");
			doctor->boundingBox.posX += DESLOCAMENTO;

			coordX = ((int)doctor->boundingBox.posX/ tileSet->tileWidth);
			coordY = ((int)doctor->boundingBox.posY / tileSet->tileHeight);

			if(verificaColisao(coordX, coordY, coordX, coordY-1))
				doctor->boundingBox.posX -= DESLOCAMENTO;
			else
				pbBatalhaDir+=4;

			input = true;

		}
		else if( InputManager::getInputManager()->isKeyDown(SDLK_w) || InputManager::getInputManager()->isKeyPressed(SDLK_w)){
			doctor->setCurrentAnimation("andar_tras");
			doctor->boundingBox.posY -= DESLOCAMENTO;

			coordX = ((int)doctor->boundingBox.posX/ tileSet->tileWidth);
			int parcialY = doctor->boundingBox.posY - doctor->boundingBox.h;
			if(parcialY > 0 )
				coordY = parcialY/ tileSet->tileHeight;
			else
				coordY = -1;

			if(verificaColisao(coordX, coordY, coordX-1, coordY))
				doctor->boundingBox.posY = (coordY+2)*(tileSet->tileHeight);
			else
				pbBatalhaCos+=4;

			input = true;

		}
		else if( InputManager::getInputManager()->isKeyDown(SDLK_s) || InputManager::getInputManager()->isKeyPressed(SDLK_s) ){
			doctor->setCurrentAnimation("andar_frente");
			doctor->boundingBox.posY += DESLOCAMENTO;

			coordX = ((int)doctor->boundingBox.posX / tileSet->tileWidth);
			coordY = ((int)doctor->boundingBox.posY / tileSet->tileHeight);

			if(verificaColisao(coordX, coordY, coordX-1, coordY))
				doctor->boundingBox.posY = (coordY)*(tileSet->tileHeight);
			else
				pbBatalhaFre+=4;

			input = true;

		}

		if( InputManager::getInputManager()->isKeyDown(SDLK_ESCAPE)){
			returnUpdate = ESTADO_STATUS;
		}

		if( InputManager::getInputManager()->isKeyDown(SDLK_SPACE)){
			//printf("espaco!\n");
			bool fala = false;
			SDL_Rect *TARDIS = new SDL_Rect();
			TARDIS->w = 64;
			TARDIS->h = 64;
			vector<PersonagemInativo*>::iterator it;
			if(strcmp(doctor->currentAnimation->name.c_str(),"parado_frente") == 0 ){
				printf("parado_frente\n");
				coordX = doctor->boundingBox.posX;
				coordY = doctor->boundingBox.posY + 32;
				TARDIS->x = TARDIS_TILE_X * 64;
				TARDIS->h = TARDIS_TILE_Y *64 - 32;
			}
			else if(strcmp(doctor->currentAnimation->name.c_str(),"parado_tras") == 0 ){
				printf("parado_tras\n");
				coordX = doctor->boundingBox.posX;
				coordY = doctor->boundingBox.posY - 32;

				TARDIS->x = TARDIS_TILE_X * 64;
				TARDIS->h = TARDIS_TILE_Y *64 + 32;
			}
			else if(strcmp(doctor->currentAnimation->name.c_str(),"parado_dir") == 0 ){
				printf("parado_tras\n");
				coordX = doctor->boundingBox.posX + 32;
				coordY = doctor->boundingBox.posY;

				TARDIS->x = TARDIS_TILE_X * 64 - 32;
				TARDIS->h = TARDIS_TILE_Y *64;
			}
			else if(strcmp(doctor->currentAnimation->name.c_str(),"parado_esq") == 0 ){
				printf("parado_tras\n");
				coordX = doctor->boundingBox.posX - 32;
				coordY = doctor->boundingBox.posY;

				TARDIS->x = TARDIS_TILE_X * 64 + 32;
				TARDIS->h = TARDIS_TILE_Y *64;
			}

			SDL_Rect *rectAux = new SDL_Rect();
			rectAux->x = coordX;
			rectAux->y = coordY;
			rectAux->h = 64;
			rectAux->w = 64;

			for(it = vetPersonagensInativos.begin(); it < vetPersonagensInativos.end(); it++){
				if((*it)->collidesWith(rectAux)){
					fala = true;
					break;
				}
			}

			if(fala){
				//printf("Fala: %s\n",(*it)->fala.c_str());
				caixaDialogo = new CaixaTexto((*it)->fala);
				renderCaixaTexto = true;
			}
			else {
				//printf("TARDIS: %d %d\n",TARDIS_TILE_X * 64,TARDIS_TILE_Y * 64);
				//printf("Doctor: %f %f\n",doctor->boundingBox.posX,doctor->boundingBox.posY);
				if(doctor->collidesWith(TARDIS)){
					printf("Colidiu TARDIS!\n");
					timerTARDIS.start();
					ENTRA_TARDIS = true;
				}
			}
		}

		//estaticos
		if( InputManager::getInputManager()->isKeyUp(SDLK_w)){
			currentAnimation->reset();
			doctor->setCurrentAnimation("parado_tras");
			input = true;
		}
		if( InputManager::getInputManager()->isKeyUp(SDLK_s)){
			currentAnimation->reset();
			doctor->setCurrentAnimation("parado_frente");
			input = true;
		}
		if( InputManager::getInputManager()->isKeyUp(SDLK_d)){
			currentAnimation->reset();
			doctor->setCurrentAnimation("parado_dir");
			input = true;
		}
		if( InputManager::getInputManager()->isKeyUp(SDLK_a)){
			currentAnimation->reset();
			doctor->setCurrentAnimation("parado_esq");
			input = true;
		}

		//if(input)
			//currentAnimation->start();
	}

	//verifica colisao com tiles de batalha
	coordX = ((int)doctor->boundingBox.posX/ tileSet->tileWidth);
	coordY = ((int)doctor->boundingBox.posY / tileSet->tileHeight);
	//printf("Coordx: %d coordy: %d\n",coordX, coordY);
	for(vector<TILE_BATALHA>::iterator it = vetTilesBatalha.begin(); it < vetTilesBatalha.end(); it++){
		if((*it).x == coordX && (*it).y == coordY) {
			(*it).x = rand() % 48;
			(*it).y = rand() % 40;
			returnUpdate = ESTADO_BATALHA;
		}
	}

	for(vector<PersonagemInativo*>::iterator it = vetPersonagensInativos.begin(); it < vetPersonagensInativos.end(); it++){
		SDL_Rect *rect = new SDL_Rect();
		rect->x = (*it)->boundingBox.posX;
		rect->y = (*it)->boundingBox.posY;
		rect->h = (*it)->boundingBox.h;
		rect->w = (*it)->boundingBox.w;
		if(doctor->collidesWith(rect)) {
			doctor->boundingBox.posX = oldX;
			doctor->boundingBox.posY = oldY;
			break;
		}
	}

}

bool StateCenario::verificaColisao(int coordX, int coordY, int coordX2, int coordY2){

	PersonagemAtivo *doctor = grupoCenario->vetorPersonages.front();

	//printf("Coord %d %d Coord2 %d %d\n",coordX, coordY, coordX2, coordY2);

	int tileColisao = tileMap->at(coordX, coordY, 1);
	int tileColisao2 = tileMap->at(coordX2, coordY2, 1);

	//printf("Tilecolisao = %d\n",tileColisao);
	//printf("Tilecolisao2 = %d\n",tileColisao2);

	if(tileColisao < 0 && tileColisao2 < 0){
		return false;
	}
	else {
		bool tile1 = false;
		bool tile2 = false;
		if(tileColisao > 0 ) {
			SDL_Rect retangulo;
			retangulo.x = tileMap->mapWidth * coordX;
			retangulo.y = tileMap->mapHeight * coordY;
			retangulo.w = tileMap->mapWidth;
			retangulo.h = tileMap->mapHeight;

			//printf("rectx %d recty %d w %d h %d\n",retangulo.x, retangulo.y, retangulo.w, retangulo.h);
			tile1 = doctor->collidesWith(&retangulo);
		}

		if(tileColisao2 > 0 ) {
			SDL_Rect retangulo;
			retangulo.x = tileMap->mapWidth * coordX2;
			retangulo.y = tileMap->mapHeight * coordY2;
			retangulo.w = tileMap->mapWidth;
			retangulo.h = tileMap->mapHeight;

			//printf("rectx %d recty %d w %d h %d\n",retangulo.x, retangulo.y, retangulo.w, retangulo.h);
			tile2 = doctor->collidesWith(&retangulo);
		}

		//printf("tiled 1 %d tiled2 %d\n",tile1,tile2);
		return (tile1 || tile2);
	}
}

void StateCenario::geraInativos() {
	string filePath = "../resources/inativo.xml";
	vector<int> inativosX;
	vector<int> inativosY;

	vetPersonagensInativos.clear();

	int inativoxAux = 1126;
	int inativoyAux = 1436;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 1183;
	inativoyAux = 1580;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 547;
	inativoyAux = 1706;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 484;
	inativoyAux = 1904;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 559;
	inativoyAux = 1565;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 880;
	inativoyAux = 1820;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 950;
	inativoyAux = 1820;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 1051;
	inativoyAux = 1322;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 664;
	inativoyAux = 1325;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 1465;
	inativoyAux = 1567;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);
	inativoxAux = 1441;
	inativoyAux = 1126;
	inativosX.push_back(inativoxAux);
	inativosY.push_back(inativoyAux);

	XMLDocument falasDoc;
	string strFalas = "../resources/InativosFalas";
	strFalas += SDLBase::strLanguage;
	falasDoc.LoadFile(strFalas.c_str());
	if(falasDoc.ErrorID() != 0){
		printf("Erro ao tentar abrir o xml %s. ErrodId: %d\n",filePath.c_str(),falasDoc.ErrorID());
		exit(1);
	}

	XMLNode *root = falasDoc.RootElement();
	XMLElement *childFala = root->FirstChildElement("fala");

	for(int i = 0; i < 11 ; i ++){
		char strSprite[100];
		sprintf(strSprite,"../images/inativo%d.png",i);
		Sprite *sprite = new Sprite(strSprite);

		char nome[10];
		sprintf(nome, "inativo%d",i);
		PersonagemInativo *pAux = new PersonagemInativo(filePath,nome,sprite);
		pAux->fala = childFala->GetText();
		childFala = childFala->NextSiblingElement("fala");
		//printf(" fala: %s\n",pAux->fala.c_str());

		pAux->boundingBox.posX = inativosX[i];
		pAux->boundingBox.posY = inativosY[i];
		//printf(" %f %f\n",pAux->boundingBox.posX, pAux->boundingBox.posY);

		vetPersonagensInativos.push_back(pAux);
	}
}
