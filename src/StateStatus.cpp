/*
 * StateStatus.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Carol
 */
/*
 * StateDummie.cpp
 *
 *  Created on: Jul 19, 2013
 *      Author: Carol
 */

#include "../headers/StateStatus.h"

void StateStatus::load(int pilha) {
	background = new Sprite("../images/HUD Final Vertical.png");

	box1X = 100;
	box1Y = 100;
	box2X = 276;
	box2Y = 100;
	box3X = 550;
	box3Y = 100;

	spriteSeta = new Sprite("../images/seta_branca.png");
	renderColuna = RENDER1;

	sfxBackground = new Audio("../sfx/temaStatus.wav",1);
	sfxBlip = new Audio("../sfx/Blip.wav",1);
}

void StateStatus::begin(GrupoCenario *grupoMocinhos){
	string strItens;
	sfxBackground->play(5);
	this->grupoMocinhos = grupoMocinhos;
	if(grupoMocinhos->listaItens.empty())
		strItens = "*Itens";
	else
		strItens = "Itens";

	string strPersonagens = "Characters";
	string strAid = "AID Group";
	string strMenuPrincipal = "Menu Principal";
	vector<string> vetStr;
	vetStr.push_back(strPersonagens);
	vetStr.push_back(strItens);
	vetStr.push_back(strAid);
	vetStr.push_back(strMenuPrincipal);

	Sprite *sprite = new Sprite("../images/seta_branca.png");
	opcoesInicial = new TextOpcoes(vetStr,box1X,box1Y,50,sprite);

//	if(!grupoMocinhos->listaItens.empty())
		getListaItens();

	getListaPersonagens();

	returnUpdate = ESTADO_STATUS;

	renderColuna = RENDER1;
}

int StateStatus::unload() {
	return 0;

}
int StateStatus::update(int deltaFrame){
	processEvents();

	if(returnUpdate != ESTADO_STATUS)
		sfxBackground->stop();

	return returnUpdate;

}
void StateStatus::render(){
	background->render(0,0);

	renderSetaInicial = true;
	renderSetaSecundario = true;

	switch (renderColuna) {
	case RENDER3:
		renderSetaSecundario = false;
		switch (renderDados) {
		case RENDER_Personagens:
			estruturaStatus->render();
			break;
		case RENDER_Itens:
			estruturaItem->render();
			//render de item
			break;
		}
	case RENDER2:
		renderSetaInicial = false;
		switch (renderDados) {
		case RENDER_Personagens:
			opcoesPersonagens->render(renderSetaSecundario);
			break;
		case RENDER_Itens:
			opcoesItens->render(renderSetaSecundario);
			break;
		case RENDER_AID:
			//TODO
			//fazer o render do AID
			break;
		}
	case RENDER1 :
		opcoesInicial->render(renderSetaInicial);
		break;
	}
}

void StateStatus::processEvents(){
	InputManager::getInputManager()->update();
	returnUpdate = ESTADO_STATUS;
	if (InputManager::getInputManager()->isKeyDown(SDLK_UP)) {
		sfxBlip->play(0);
		opcoesInicial->update(false);
		opcoesItens->update(false);
		opcoesPersonagens->update(false);

	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_DOWN)) {
		sfxBlip->play(0);
		opcoesInicial->update(true);
		opcoesItens->update(true);
		opcoesPersonagens->update(true);

	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		if(renderColuna == RENDER1){
			renderColuna = RENDER2;
			//printf("Mudei para o render2!\n");
			int opcaoEscolhida = opcoesInicial->getOpcao();
			//printf("Opcao escolhida: %d\n",opcaoEscolhida);
			if(opcaoEscolhida == 0)
				renderDados = RENDER_Personagens;
			else if(opcaoEscolhida == 1)
				renderDados = RENDER_Itens;
			else if(opcaoEscolhida == 2){
				returnUpdate = ESTADO_SELECAO;
				renderDados = RENDER_AID;
			}
			else if(opcaoEscolhida == 3){
				returnUpdate = ESTADO_MENU;
				renderColuna = RENDER1;
			}
		}
		else if(renderColuna == RENDER2 && renderDados == RENDER_Personagens) {
			renderColuna = RENDER3;
			int opcaoPersonagem = opcoesPersonagens->getOpcao();
			estruturaStatus = new EstruturaStatus(grupoMocinhos->vetorPersonages[opcaoPersonagem],box3X, box3Y);
		}
		else if(renderColuna == RENDER2 && renderDados == RENDER_Itens) {
			renderColuna = RENDER3;
			int opcaoItem = opcoesItens->getOpcao();
			estruturaItem = new EstruturaItem(grupoMocinhos->listaItens[opcaoItem],box3X, box3Y);
			//estruturaStatus = new EstruturaStatus(grupoMocinhos->vetorPersonages[opcoesPersonagens]);
		}
	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_BACKSPACE)) {
		if(renderColuna == RENDER3)
			renderColuna = RENDER2;
		else if(renderColuna == RENDER2)
			renderColuna = RENDER1;
	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_ESCAPE)) {
		returnUpdate = ESTADO_CENARIO;
	}
}

void StateStatus::getListaItens() {
	vector<string> listaItens;
	vector<Item*>::iterator it;
	for(it = grupoMocinhos->listaItens.begin(); it < grupoMocinhos->listaItens.end(); it++){
		//("nome: %s\n",(*it)->nome.c_str());
		listaItens.push_back((*it)->nome);
	}

	//printf("Size lista item: %d\n",listaItens.size());
	//printf("Box2X %d box2Y:%d\n",box2X,box2Y);
	opcoesItens = new TextOpcoes(listaItens,box2X + 30, box2Y,50,spriteSeta);
}

void StateStatus::getListaPersonagens() {
	vector<string> listaPersonagens;
	for(vector<PersonagemAtivo*>::iterator it = grupoMocinhos->vetorPersonages.begin(); it < grupoMocinhos->vetorPersonages.end(); it++)
		listaPersonagens.push_back((*it)->nome);

	opcoesPersonagens = new TextOpcoes(listaPersonagens,box2X + 30, box2Y,50,spriteSeta);
}




