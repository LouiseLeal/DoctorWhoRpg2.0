/*
 * StateMenu.cpp
 *
 *  Created on: Jul 19, 2013
 *      Author: Carol
 */


#include "../headers/StateMenu.h"

void StateMenu::load(int pilha){

	returnUpdate = ESTADO_MENU;
	loadStrings();

	//string strStart = "Start";
	//string strQuit = "Quit";
	//vector<string> vetStr;
	//vetStr.push_back(strStart);
	//vetStr.push_back(strQuit);
	//opcoesMenus->seta->~Sprite();
	//opcoesMenus->seta = spriteAux;

	string fontFile = "../fonts/CCRedAlert.ttf";
	SDL_Color corBranco = { 255, 255, 255 };

	txtTitulo = new Text(fontFile,"Doctor Who",52,TTF_STYLE_NORMAL,corBranco,260,200);
	txtSubTitulo = new Text(fontFile,"An Army of Ghosts",42,TTF_STYLE_NORMAL,corBranco,260,240);

	background = new Sprite("../images/main_screen.png");

	sfxBlip = new Audio("../sfx/Blip.wav",1);
	sfxMenu = new Audio("../sfx/temaPrincipal.wav",1);
	spriteIntrucoes = new Sprite("../images/howto.png");
}

void StateMenu::begin() {
	if(strcmp(SDLBase::strLanguage.c_str(),"_pt.xml") == 0){
		spriteIntrucoes->~Sprite();
		spriteIntrucoes = new Sprite("../images/howto_pt.png");
	}
	sfxMenu->play(500);
	printInstrucoes = false;
	returnUpdate = ESTADO_MENU;
}

int StateMenu::unload(){
	return 0;

}
int StateMenu::update(int deltaFrame){
	processEvents();

	if(returnUpdate != ESTADO_MENU)
		sfxMenu->stop();

	return returnUpdate;
}
void StateMenu::render(){
	background->render(0,0);
	//txtTitulo->render();
	//txtSubTitulo->render();
	opcoesMenus->render(true);

	if(printInstrucoes)
		spriteIntrucoes->render(0,0);

}

void StateMenu::processEvents(){
	InputManager::getInputManager()->update();
	if (InputManager::getInputManager()->isKeyDown(SDLK_UP)) {
		opcoesMenus->update(false);
		sfxBlip->play(1);
	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_DOWN)) {
		opcoesMenus->update(true);
		sfxBlip->play(1);
	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		int escolhido = opcoesMenus->getOpcao();
		if(escolhido == 0){
			sfxMenu->stop();
			returnUpdate = ESTADO_INTRODUCAO;
		}
		else if(escolhido == 1){
			sfxMenu->stop();
			if(strcmp(SDLBase::strLanguage.c_str(),"_pt.xml") == 0){
				SDLBase::strLanguage = ".xml";
				spriteIntrucoes->~Sprite();
				spriteIntrucoes = new Sprite("../images/howto.png");
			}
			else{
				spriteIntrucoes->~Sprite();
				spriteIntrucoes = new Sprite("../images/howto_pt.png");
				SDLBase::strLanguage = "_pt.xml";
			}
			loadStrings();
			this->begin();
		}
		else if(escolhido == 2){
			printInstrucoes = true;
		}
		else if(escolhido == 3){
			sfxMenu->stop();
			returnUpdate = ESTADO_CREDITOS;
		}
		else
			returnUpdate = ESTADO_FIM;
	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_BACKSPACE)) {
		if(printInstrucoes)
			printInstrucoes = false;
	}
}

void StateMenu::loadStrings(){
	XMLDocument stringsDoc;

	string filePath = "../resources/opcaoMenuInicial";
	filePath += SDLBase::strLanguage;
	stringsDoc.LoadFile(filePath.c_str());
	if(stringsDoc.ErrorID() != 0){
		printf("Erro ao tentar abrir o xml %s . ErrodId: %d\n",filePath.c_str(),stringsDoc.ErrorID());
		exit(1);
	}

	XMLNode *framesList = stringsDoc.RootElement();
	XMLElement *childFrame;

	vetStr.clear();
	for(childFrame = framesList->FirstChildElement("opcao"); childFrame; childFrame = childFrame->NextSiblingElement("opcao")){
		string strAux = childFrame->GetText();
		vetStr.push_back(strAux);

	}

	Sprite *spriteAux = new Sprite("../images/mini_tardis.png");
	opcoesMenus = new TextOpcoes(vetStr,545,300,50,spriteAux);
}

