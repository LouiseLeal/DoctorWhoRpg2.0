/*
 * PersonagemAtivo.c
 *
 *  Created on: 01/06/2013
 *      Author: Louise
 */
#include "../headers/PersonagemAtivo.h"


PersonagemAtivo::PersonagemAtivo(string filePath, string nome, Sprite *spriteRef) : Personagem(nome, spriteRef) {

	//string filePathDados = "DoctorWhoRpg/resources/";
	//filePathDados += nome + ".txt";
	//printf("filepath: %s\n",filePathDados.c_str());
	//loadDadosAnimacoes(filePathDados);

	loadXml(filePath);

	animacaoEscolhida = "parado_frente";
	std::map<string,Animation*>::iterator itAnimacao;
	itAnimacao = listAnimacoes.find(animacaoEscolhida);
	if(itAnimacao == listAnimacoes.end()){
		printf("Erro no find da animacao.\n");
		printf("Animacao escolhida: %s\n",animacaoEscolhida.c_str());
		exit(1);
	}
	currentAnimation = (*itAnimacao).second;

}

std::string PersonagemAtivo::getName(){
	return this->nome;
}
Habilidade PersonagemAtivo::getHability(){
	return this->habilidade;
}
int PersonagemAtivo::getType(){
	return this->type;
}

void PersonagemAtivo::loadXml(string filePath){

	XMLDocument personagemDoc;
	personagemDoc.LoadFile(filePath.c_str());
	if(personagemDoc.ErrorID() != 0){
		printf("Erro ao tentar abrir o xml %s. ErrodId: %d\n",filePath.c_str(),personagemDoc.ErrorID());
		exit(1);
	}

	const char *tipoAux = personagemDoc.FirstChildElement("type")->GetText();
	if(tipoAux == NULL)
	{
		printf("Erro ao ler o tipo do personagem. \n");
		exit(1);
	}

	if(strcmp(tipoAux,"ataque") == 0)
		tipo = ATAQUE;
	else if (strcmp(tipoAux, "inteligencia") == 0){
		tipo = INTELIGENCIA;
	}
	else if(strcmp(tipoAux, "defesa") == 0)
		tipo = DEFESA;

	personagemDoc.FirstChildElement("life")->QueryIntText(&(life));
	personagemDoc.FirstChildElement("mana")->QueryIntText(&(mana));
	personagemDoc.FirstChildElement("sprite")->QueryIntText(&(spriteIndex));

	//posicao
	personagemDoc.FirstChildElement("initial-position")->FirstChildElement("posx")->QueryFloatText(&(boundingBox.posX));
	personagemDoc.FirstChildElement("initial-position")->FirstChildElement("posy")->QueryFloatText(&(boundingBox.posX));

	//habilidade
	personagemDoc.FirstChildElement("hability")->FirstChildElement("attack-value")->QueryIntText(&(habilidade.ataque));
	personagemDoc.FirstChildElement("hability")->FirstChildElement("inteligence-value")->QueryIntText(&(habilidade.inteligencia));
	personagemDoc.FirstChildElement("hability")->FirstChildElement("defence-value")->QueryIntText(&(habilidade.defesa));

	//sprite information
	personagemDoc.FirstChildElement("sprite-w")->QueryIntText(&(spriteW));
	boundingBox.w = spriteW;
	personagemDoc.FirstChildElement("sprite-h")->QueryIntText(&(spriteH));
	boundingBox.h = spriteH;
	personagemDoc.FirstChildElement("image-w")->QueryIntText(&(imageW));
	personagemDoc.FirstChildElement("image-h")->QueryIntText(&(imageH));

	//ataque
	XMLNode *ataqueLista = personagemDoc.FirstChildElement("attack-list");
	XMLNode *childAtaque;
	for(childAtaque = ataqueLista->FirstChildElement("attack"); childAtaque; childAtaque = childAtaque->NextSibling()){
		string nomeAtaque;
		AID_TYPES tipoAtaque;
		nomeAtaque = childAtaque->FirstChildElement("name")->GetText();
		const char *tipoAux2 = childAtaque->FirstChildElement("type")->GetText();

		if(strcmp(tipoAux2,"ataque") == 0)
			tipoAtaque = ATAQUE;
		else if (strcmp(tipoAux2, "inteligencia") == 0){
			tipoAtaque = INTELIGENCIA;
		}
		else if(strcmp(tipoAux2, "defesa") == 0)
			tipoAtaque = DEFESA;
		else
			tipoAtaque = ATAQUE;

		//Ataque *ataque = new Ataque(nomeAtaque,tipoAtaque);
		//listAttack.push_back(ataque);
		//map
		listAttack[nomeAtaque] = new Ataque(nomeAtaque,tipoAtaque);
	}


	//dados sprite
		XMLNode *linhaLista = personagemDoc.FirstChildElement("dados_sprite-list");
		XMLNode *childLinha;
		XMLNode *childSprite;
		//int contaLinha = 0;
//printf("personagem: %s\n",this->nome.c_str());
		vector<DADOS_ANIMACAO> vetDadosAnimacao;
		for(childLinha = linhaLista->FirstChildElement("linha"); childLinha; childLinha = childLinha->NextSibling()){
			DADOS_ANIMACAO dadosAnimacao;
			//printf("Linha! %d\n",contaLinha);
			//contaLinha++;
			childLinha->FirstChildElement("largura")->QueryIntText(&dadosAnimacao.largura);
			childLinha->FirstChildElement("altura")->QueryIntText(&dadosAnimacao.altura);
			//int contaSprite = 0;
			for(childSprite = childLinha->FirstChildElement("sprite"); childSprite; childSprite = childSprite->NextSibling()){

				//printf("Sprite: %d\n",contaSprite);
				int cropX = 0;
				int cropY = 0;
				int posX = 0;
				int posY;

				childSprite->FirstChildElement("cropx")->QueryIntText(&cropX);
				childSprite->FirstChildElement("cropy")->QueryIntText(&cropY);
				childSprite->FirstChildElement("deslocax")->QueryIntText(&posX);
				childSprite->FirstChildElement("deslocay")->QueryIntText(&posY);

				dadosAnimacao.vetCropX.push_back(cropX);
				dadosAnimacao.vetCropY.push_back(cropY);
				dadosAnimacao.vetPosX.push_back(posX);
				dadosAnimacao.vetPosY.push_back(posY);

			}

			vetDadosAnimacao.push_back(dadosAnimacao);
		}

	//animacoes
	XMLNode *animacaoLista = personagemDoc.FirstChildElement("animation-list");
	XMLNode *childAnimacao;
	for(childAnimacao = animacaoLista->FirstChildElement("animation"); childAnimacao; childAnimacao = childAnimacao->NextSibling()){
		int linhaSprite = 0;
		int nSprites = 0;
		int loop = false;
		string nome = childAnimacao->FirstChildElement("name")->GetText();
		childAnimacao->FirstChildElement("sprite")->QueryIntText(&linhaSprite);
		childAnimacao->FirstChildElement("frames")->QueryIntText(&nSprites);
		childAnimacao->FirstChildElement("loop")->QueryIntText(&loop);

		//Animation *animacao = new Animation(sprite,indexSprite, nSprites, loop, nome);
		//listAnimacoes.push_back(animacao);

		//map
		//printf("Nome animacao: %s\n",nome.c_str());

		string strSfx = "DoctorWhoRpg/sfx/";
		strSfx += nome;
		strSfx += ".wav";
		//printf("Strsfx: %s\n",strSfx.c_str());
		sfxAtaque = new Audio(strSfx,1);
		listAnimacoes[nome] = new Animation(sprite,linhaSprite, nSprites, loop, nome, vetDadosAnimacao[linhaSprite], sfxAtaque);
	}

	//printf("Vida: %d\nMana: %d\nSprite: %d\nPos: %f %f\n",life, mana, spriteIndex, boundingBox.posX, boundingBox.posY);
	//printf("Habilidade: %d %d %d\nAtaque: %s %d\n",habilidade.ataque, habilidade.inteligencia, habilidade.defesa, ataque->nome.c_str(), ataque->tipoAtaque);
}

int PersonagemAtivo::update(int dt) {
	//processEvent();
	currentAnimation->update(dt);//, spriteW,spriteH, imageW, imageH);
	return dt;
}

void PersonagemAtivo::render() {
	currentAnimation->render(boundingBox.posX - Camera::cameraX - sprite->clipRectSprite.w, boundingBox.posY - Camera::cameraY - sprite->clipRectSprite.h);
}

void PersonagemAtivo::processEvent(){

	InputManager::getInputManager()->update();
	bool input = false;
	//movimetnos
	if(!currentAnimation->animationRunning()) {
		//reseta animacoes sem loop quando terminam para o primeiro frame
		if(!currentAnimation->loop)
			currentAnimation->reset();

		//retorna para um estado especifico apos animacao sem loop
		if(!currentAnimation->loop && currentAnimation->nSprites > 1 ){
			animacaoEscolhida = "posicao_batalha";
		}

		if( InputManager::getInputManager()->isKeyDown(SDLK_a) || InputManager::getInputManager()->isKeyPressed(SDLK_a)){
			animacaoEscolhida = "andar_esq";
			//printf("aaaaaaaaaaaaaaaaa\n");
			boundingBox.posX -= 0.5;
			input = true;
		}
		if( InputManager::getInputManager()->isKeyDown(SDLK_d) || InputManager::getInputManager()->isKeyPressed(SDLK_d)){
			//printf("ddddddddddd\n");
			animacaoEscolhida = "andar_dir";
			boundingBox.posX += 0.5;
			input = true;
		}
		if( InputManager::getInputManager()->isKeyDown(SDLK_w) || InputManager::getInputManager()->isKeyPressed(SDLK_w)){
			animacaoEscolhida = "andar_tras";
			boundingBox.posY -= 0.5;
			input = true;
		}
		if( InputManager::getInputManager()->isKeyDown(SDLK_s) || InputManager::getInputManager()->isKeyPressed(SDLK_s) ){
			animacaoEscolhida = "andar_frente";
			boundingBox.posY += 0.5;
			input = true;
		}

		//estaticos
		if( InputManager::getInputManager()->isKeyUp(SDLK_w)){
			currentAnimation->reset();
			animacaoEscolhida = "parado_tras";
			input = true;
		}
		if( InputManager::getInputManager()->isKeyUp(SDLK_s)){
			currentAnimation->reset();
			animacaoEscolhida = "parado_frente";
			input = true;
		}
		if( InputManager::getInputManager()->isKeyUp(SDLK_d)){
			currentAnimation->reset();
			animacaoEscolhida = "parado_dir";
			input = true;
		}
		if( InputManager::getInputManager()->isKeyUp(SDLK_a)){
			currentAnimation->reset();
			animacaoEscolhida = "parado_esq";
			input = true;
		}

		std::map<string,Animation*>::iterator itAnimacao;
		itAnimacao = listAnimacoes.find(animacaoEscolhida);
		if(itAnimacao == listAnimacoes.end()){
			printf("Erro no find da animacao.\n");
			printf("Animacao escolhida: %s\n",animacaoEscolhida.c_str());
			exit(1);
		}
		currentAnimation = (*itAnimacao).second;
		if(input)
			currentAnimation->start();
	}

}

void PersonagemAtivo::setCurrentAnimation(string nomeAnimacao){
	animacaoEscolhida = nomeAnimacao;
	std::map<string,Animation*>::iterator itAnimacao;
	itAnimacao = listAnimacoes.find(animacaoEscolhida);
	if(itAnimacao == listAnimacoes.end()){
		printf("Erro no find da animacao.\n");
		printf("Animacao escolhida: %s\n",animacaoEscolhida.c_str());
		exit(1);
	}
	currentAnimation = (*itAnimacao).second;
	currentAnimation->start();
	//printf("fim set animation\n");
}

//void PersonagemAtivo::loadDadosAnimacoes(string filePath) {
//	int widthAnimacao = 0;
//	int linha = 0;
//	int coluna = 0;
//	char charAux;
//	char charNumero[3];
//	vetDadosAnimacoes.resize(1);
//
//	ifstream streamDadosAnimacoes(filePath.c_str());
//	if(!streamDadosAnimacoes.is_open()){
//		printf("Erro de aberturda de Arquivo.\n");
//		exit(1);
//	}
//
//	string linhaAnimacao;
//	//loop para ler o arquivo
//	while(!streamDadosAnimacoes.eof()){
//		getline(streamDadosAnimacoes, linhaAnimacao);
//		//printf("string getline %s\n",linhaAnimacao.c_str());
//		int indexInicio = 0;
//		string strAux;
//
//		//verifica onde esta o primeiro divisor
//		int divisor = linhaAnimacao.find('\t');
//		if(divisor == string::npos){
//			//so tem um numero na linha
//			strAux = linhaAnimacao.substr(indexInicio,divisor - indexInicio);
//			widthAnimacao = atoi(strAux.c_str());
//			vetDadosAnimacoes[linha].push_back(widthAnimacao);
//		}
//		else {
//			//itera pela string
//			while(divisor != string::npos){
//				strAux = linhaAnimacao.substr(indexInicio,divisor - indexInicio);
//				widthAnimacao = atoi(strAux.c_str());
//				vetDadosAnimacoes[linha].push_back(widthAnimacao);
//				indexInicio = divisor+1;
//				divisor = linhaAnimacao.find('\t',indexInicio);
//			}
//			strAux = linhaAnimacao.substr(indexInicio,linhaAnimacao.length() - indexInicio);
//			widthAnimacao = atoi(strAux.c_str());
//			vetDadosAnimacoes[linha].push_back(widthAnimacao);
//		}
//
//		//printf("Tamaho linha %d: %d\n",linha,vetDadosAnimacoes[linha].size());
//		linha++;
//		vetDadosAnimacoes.resize(linha+1);
//	}
//
//	for(vector<vector<int> >::iterator it = vetDadosAnimacoes.begin(); it < vetDadosAnimacoes.end(); it++){
//		for(vector<int>::iterator it2 = (*it).begin(); it2 < (*it).end(); it2++){
//			printf("Dados: %d\t");
//		}
//		printf("\n");
//	}
//	streamDadosAnimacoes.close();
//}

bool PersonagemAtivo::collidesWith(SDL_Rect *rect){
	int diffX, diffY;
	int largura = currentAnimation->dadosAnimacao.largura;
	// int altura = currentAnimation->dadosAnimacao.altura;
	int cropx = currentAnimation->dadosAnimacao.vetCropX[currentAnimation->currentFrame];
	int cropy = currentAnimation->dadosAnimacao.vetCropY[currentAnimation->currentFrame];

	int posX = this->boundingBox.posX - ((largura/2) - (cropx/2));
	int posY = boundingBox.posY;

	diffX = posX - (rect->x + rect->w); //menor que a largura do rect
	diffY = posY - (rect->y + rect->h); //

	//printf("Rectx: %d Recty %d ",rect->x + rect->w, rect->y + rect->h);
	//printf("cropx: %d cropy %d ",cropx, cropy);
	//printf("Diffx: %d DiffY %d posx %d posy %d\n",diffX, diffY, posX, posY);

	if(diffX >= cropx || -diffX >= rect->w ){
		return false;
	}
	if(diffY >= rect->h || -diffY >= cropy ){
		return false;
	}
	return true;
}

