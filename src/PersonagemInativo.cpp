/*
 * PersonagemInativo.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: Carol
 */

#include "../headers/PersonagemInativo.h"

PersonagemInativo::PersonagemInativo(string filePath, string nome, Sprite *spriteRef) : Personagem(nome, spriteRef) {
	loadXml(filePath);
	currentAnimation = listAnimacoes["parado_frente"];
}

void PersonagemInativo::render() {
	currentAnimation->render(boundingBox.posX - Camera::cameraX, boundingBox.posY - Camera::cameraY);
}

int PersonagemInativo::update(int dt){
	return 0;

}

bool PersonagemInativo::collidesWith(SDL_Rect *rect){
	int diffX, diffY;
	int largura = currentAnimation->dadosAnimacao.largura;
	// int altura = currentAnimation->dadosAnimacao.altura;
	int cropx = currentAnimation->dadosAnimacao.vetCropX[currentAnimation->currentFrame];
	int cropy = currentAnimation->dadosAnimacao.vetCropY[currentAnimation->currentFrame];

	int posX = this->boundingBox.posX - ((largura/2) - (cropx/2));
	int posY = boundingBox.posY;

	diffX = posX - (rect->x - rect->w); //menor que a largura do rect
	diffY = posY - (rect->y - rect->h); //

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

void PersonagemInativo::loadXml(string filePath) {
	XMLDocument personagemDoc;
	personagemDoc.LoadFile(filePath.c_str());
	if(personagemDoc.ErrorID() != 0){
		printf("Erro ao tentar abrir o xml %s. ErrodId: %d\n",filePath.c_str(),personagemDoc.ErrorID());
		exit(1);
	}

	personagemDoc.FirstChildElement("sprite")->QueryIntText(&(spriteIndex));

	//sprite information
	personagemDoc.FirstChildElement("sprite-w")->QueryIntText(&(spriteW));
	boundingBox.w = spriteW;
	personagemDoc.FirstChildElement("sprite-h")->QueryIntText(&(spriteH));
	boundingBox.h = spriteH;
	personagemDoc.FirstChildElement("image-w")->QueryIntText(&(imageW));
	personagemDoc.FirstChildElement("image-h")->QueryIntText(&(imageH));


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
		listAnimacoes[nome] = new Animation(sprite,linhaSprite, nSprites, loop, nome, vetDadosAnimacao[linhaSprite]);
	}

}
