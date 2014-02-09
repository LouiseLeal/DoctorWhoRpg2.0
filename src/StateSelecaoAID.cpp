/*
 * StateSelecaoAID.cpp
 *
 *  Created on: Jul 1, 2013
 *      Author: Carol
 */

#include "../headers/StateSelecaoAID.h"

void StateSelecaoAID::load(int pilha){
	//carrega sprite de fundo e botao
	background = new Sprite("../images/backgroundAID.png");
	botao = new Sprite("../images/ok_button.png");

	estadoAtual = ESTADO_AID;

	spriteAid = new Sprite("../images/AIDVazio.png");
	spriteAidSelecionado = new Sprite("../images/selectedAID.png");
	spriteSeta = new Sprite("../images/seta_branca.png");
	botaoSelecionado= new Sprite("../images/botao_selecionado.png");
	spriteBlock = new Sprite("../images/selected.png");
	iconeLevelDisponivel = new Sprite("../images/levelUp.png");

	btSelecionado = false;

	//cria vetor de selecao
	vetSpriteAid.push_back(spriteAidSelecionado);
	vetSpriteAid.push_back(spriteAid);
	vetSpriteAid.push_back(spriteAid);

	vetAid.push_back(-1);
	vetAid.push_back(-1);
	vetAid.push_back(-1);


	aidEscolhido = 0;

	btX = 740;
	btY = 555;
	aidX = 42;
	aidY = 81;
	grupoX = 35;
	grupoY = 381;
	setaX = aidX - spriteSeta->getWidth()/2 - 10;
	//printf("setaX: %d\n", setaX);
	setaY = aidY + spriteAid->getHeight()/2 - spriteSeta->getHeight()/2;

	aidXIntervalo = 180;
	groupXIntervalo = 10;


	//iniciar texto aid
	string fontFile = "../fonts/CCRedAlert.ttf";
	SDL_Color corBranco = { 255, 255, 255 };

	Text *txtAux = new Text(fontFile,"ATT - ",25,TTF_STYLE_NORMAL,corBranco, 640, 200);
	textoAid.push_back(txtAux);
	txtAux = new Text(fontFile,"INT : ",25,TTF_STYLE_NORMAL,corBranco, 640, 237);
	textoAid.push_back(txtAux);
	txtAux = new Text(fontFile,"DEF : ",25,TTF_STYLE_NORMAL,corBranco, 640, 273);
	textoAid.push_back(txtAux);
	txtAux = new Text(fontFile,"LIFE : ",25,TTF_STYLE_NORMAL,corBranco, 640, 125);
	textoAid.push_back(txtAux);

	//iniciar texto aid

	txtAux = new Text(fontFile," ",25,TTF_STYLE_NORMAL,corBranco, 447, 444);
	textoGrupo.push_back(txtAux);
	txtAux = new Text(fontFile,"ATT : ",25,TTF_STYLE_NORMAL,corBranco, 603, 498);
	textoGrupo.push_back(txtAux);
	txtAux = new Text(fontFile,"INT : ",25,TTF_STYLE_NORMAL,corBranco, 603, 426);
	textoGrupo.push_back(txtAux);
	txtAux = new Text(fontFile,"DEF : ",25,TTF_STYLE_NORMAL,corBranco, 603, 464);
	textoGrupo.push_back(txtAux);
	txtAux = new Text(fontFile,"LIFE : ",25,TTF_STYLE_NORMAL,corBranco, 447, 478);
	textoGrupo.push_back(txtAux);

	// SDL_Color corPreta = {0,0,0};
	int x = aidX + (vetSpriteAid[0]->getWidth()/2) - 18;
	txtAux = new Text(fontFile,"x1",36,TTF_STYLE_NORMAL,corBranco, x, 32);
	textoMultiplicadores.push_back(txtAux);
	x += 160;
	txtAux = new Text(fontFile,"x1",36,TTF_STYLE_NORMAL,corBranco, x, 32);
	textoMultiplicadores.push_back(txtAux);
	x += 160;
	txtAux = new Text(fontFile,"x1",36,TTF_STYLE_NORMAL,corBranco, x, 32);
	textoMultiplicadores.push_back(txtAux);

	sfxBlip = new Audio("../sfx/Blip.wav",1);
	//sfxSelectNot = new Audio("../sfx/selecNot.wav",1);
	sfxBackground = new Audio("../sfx/temaStatus.wav",0);

	for(int i = 0; i < vetSpriteGrupo.size(); i++)
		vetSelecionados[i] = false;

}
int StateSelecaoAID::update(int deltaFrame){
	processEvents();
	populaTextoAid();

	if(returnUpdate != ESTADO_SELECAO)
	{
		printf("stop musica!!!\n");
		sfxBackground->stop();
	}

	return returnUpdate;

	if(estadoAtual == ESTADO_BATALHA)
		return ESTADO_BATALHA;
	else
		return ESTADO_SELECAO;
}
void StateSelecaoAID::setGrupoCenario(GrupoCenario *grupoMocinhos, int estado_retorno_ok){
	ESTADO_RETORNO_OK = estado_retorno_ok;
	returnUpdate = ESTADO_SELECAO;

	vetAid.clear();
	vetAid.push_back(-1);
	vetAid.push_back(-1);
	vetAid.push_back(-1);

	grupoCenario = grupoMocinhos;
//	vetSpriteAid[0] = spriteAidSelecionado;
//	vetSpriteAid[1] = spriteAid;
//	vetSpriteAid[2] = spriteAid;

	//grupoCenario->vectorPersonagensBatalha.clear();
	vetSpriteGrupo.clear();
	vetSpriteAid.clear();
	int countPersonagem = 0;
	for(vector<PersonagemAtivo*>::iterator it= grupoCenario->vetorPersonages.begin() ; it< grupoCenario->vetorPersonages.end(); it++){

		//printf("It personagem - nomePersonagem: %s\n",(*it)->nome.c_str());
		//printf("Vet grupoBatalha size %d\n",grupoCenario->vectorPersonagensBatalha.size());
		for(int i = 0; i < (int)grupoCenario->vectorPersonagensBatalha.size(); i++){
			//printf("Nomebatalha: %s nomePersonagem: %s\n",grupoCenario->vectorPersonagensBatalha[i]->nome.c_str(),(*it)->nome.c_str());
			if(strcmp(grupoCenario->vectorPersonagensBatalha[i]->nome.c_str(), (*it)->nome.c_str()) == 0)
				vetAid[i] = countPersonagem;
		}
		countPersonagem++;
		string nome = "../images/";
		Sprite * aux;
		nome += (*it)->nome;
		string nomeAid = nome;
		nome +="_Normal_Little.png";
		nomeAid += "_Normal_Big.png";
		aux = new Sprite(nome);
//		float scaleX = (74/ aux->getWidth());
//		float scaleY = (92/ aux->getHeight());
//		aux->rotoZoom(0,scaleX,scaleY,true);
		//printf("nome: %s \n", nome.c_str());
		vetSpriteGrupo.push_back(aux);

		aux = new Sprite(nomeAid);
		vetSpriteAid.push_back(aux);
	}

	char strAux[10];
	sprintf(strAux,"ATT x%d",grupoMocinhos->level->getAttackLevel());
	textoMultiplicadores[0]->setText(strAux);
	sprintf(strAux,"INT x%d",grupoMocinhos->level->getIntelligenceLevel());
	textoMultiplicadores[1]->setText(strAux);
	sprintf(strAux,"DEF x%d",grupoMocinhos->level->getDefenseLevel());
	textoMultiplicadores[2]->setText(strAux);

	levelDisponivel = false;
	if(grupoCenario->levelDisponivel > 0){
		levelDisponivel = true;
		timerLevelDisponivel.start();
	}
	estadoAtual = ESTADO_AID;

	aidEscolhido = 0;

	btSelecionado = false;
	sfxBackground->play(5);
	setaX = aidX - spriteSeta->getWidth()/2 - 10;
	setaY = aidY + spriteAid->getHeight()/2 - spriteSeta->getHeight()/2;

}
int StateSelecaoAID::unload(){
	return 0;
}

void StateSelecaoAID::processEvents() {
	InputManager::getInputManager()->update();
	if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		//sfxBlip->play(0);
		switch(estadoAtual){
		case ESTADO_AID:
			if(levelDisponivel) {
				if(aidEscolhido == 0){
					printf("ESCOLHIDO UPA ATAQUE\n");
					grupoCenario->level->setAttackLevel(grupoCenario->level->getAttackLevel() + 1);
					char strAux[50];
					sprintf(strAux,"ATT x%d",grupoCenario->level->getAttackLevel());
					textoMultiplicadores[0]->setText(strAux);
					sprintf(strAux,"ATT - %d",grupoCenario->level->getAttackLevel() * grupoCenario->level->getAttackLevel());
					textoAid[0]->setText(strAux);
				}
				else if(aidEscolhido == 1){
					printf("ESCOLHIDO UPA INTELIGENCIA\n");
					grupoCenario->level->setAttackLevel(grupoCenario->level->getAttackLevel() + 1);
					char strAux[50];
					sprintf(strAux,"INT x%d",grupoCenario->level->getAttackLevel());
					textoMultiplicadores[1]->setText(strAux);
					sprintf(strAux,"INT - %d",grupoCenario->level->getIntelligenceLevel() * grupoCenario->level->getIntelligenceLevel());
					textoAid[1]->setText(strAux);
				}
				else if(aidEscolhido == 2){
					printf("ESCOLHIDO UPA DEFESA\n");
					grupoCenario->level->setAttackLevel(grupoCenario->level->getAttackLevel() + 1);
					char strAux[50];
					sprintf(strAux,"DEF x%d",grupoCenario->level->getAttackLevel());
					textoMultiplicadores[2]->setText(strAux);
					sprintf(strAux,"DEF - %d",grupoCenario->level->getDefenseLevel() * grupoCenario->level->getDefenseLevel());
					textoAid[2]->setText(strAux);
				}
				levelDisponivel = false;
			}
			else {
				estadoAtual = ESTADO_GRUPO;
				populaTextoGrupo(0);
				setaX = grupoX*((0%3)+1)+70*(0%3) - spriteSeta->getWidth()/2 - 10;
				setaY = grupoY*((0/3)+1)+70*(0/3);
			}
		break;
		case ESTADO_GRUPO:
			estadoAtual = ESTADO_AID;
			//for para colocar o escolhido na posicao aid
			for(int i = 0; i < grupoCenario->vetorPersonages.size(); i++){
				int setaAuxX = grupoX*((i%3)+1)+70*(i%3) - spriteSeta->getWidth()/2 - 10;
				if(setaX == setaAuxX){
					//for para verificar se o escolhido ja nao estava em outra posicao
					for(int j = 0; j < vetAid.size(); j++){
						if(vetAid[j] == i)
							vetAid[j] = -1;
					}

					vetAid[aidEscolhido] = i;
					break;
				}
			}

			aidEscolhido = 0;
			setaX = aidX - spriteSeta->getWidth()/2 - 10;
			setaY = aidY + spriteAid->getHeight()/2 - spriteSeta->getHeight()/2;
		break;
		case ESTADO_OK:
			//coloca em um vetor separado o grupo que ira para a batalha e suas respectivas posicoes no grupo AID
			//printf("ataque escolhido: %d\n",ataqueEscolhido);
			//printf("inteligencia escolhido: %d\n",inteligenciaEscolhido);
			//printf("defesa escolhido: %d\n",defesaEscolhido);
			//printf("tamanho verPersonagens: %d\n",grupoCenario->vetorPersonages.size());
			if(!grupoCenario->vectorPersonagensBatalha.empty())
				grupoCenario->vectorPersonagensBatalha.clear();

			printf("VetAid[0] %d vetAid[1] %d vetAid[2] %d\n",vetAid[0],vetAid[1],vetAid[2]);

			if(vetAid[0] >= 0 )
				grupoCenario->vectorPersonagensBatalha.push_back(grupoCenario->vetorPersonages[vetAid[0]]);
			if(vetAid[1] >= 0 )
				grupoCenario->vectorPersonagensBatalha.push_back(grupoCenario->vetorPersonages[vetAid[1]]);
			if(vetAid[2] >= 0 )
				grupoCenario->vectorPersonagensBatalha.push_back(grupoCenario->vetorPersonages[vetAid[2]]);
			//printf("terminei de setar vet batalha!\n");
			printf("Vet grupoBatalha size no process event %lu\n",grupoCenario->vectorPersonagensBatalha.size());
			estadoAtual = ESTADO_BATALHA;
			returnUpdate = ESTADO_RETORNO_OK;
		break;
		}

	}
	if(InputManager::getInputManager()->isKeyDown(SDLK_DOWN)){
		sfxBlip->play(0);
		switch(estadoAtual){
		case ESTADO_AID:
			estadoAtual = ESTADO_OK;
			setaX = btX - spriteSeta->getWidth() + 15;
			setaY = btY - 15;
			//btSelecionado =true;

		break;
		case ESTADO_GRUPO:

		break;
		case ESTADO_OK:
			setaX = aidX - spriteSeta->getWidth()/2 - 10;
			setaY = aidY + spriteAid->getHeight()/2 - spriteSeta->getHeight()/2;
			estadoAtual = ESTADO_AID;
			//btSelecionado = false;
		break;
		}
	}
	if(InputManager::getInputManager()->isKeyDown(SDLK_UP)){
		sfxBlip->play(0);
		switch(estadoAtual){
		case ESTADO_AID:
			estadoAtual = ESTADO_OK;
			setaX = btX - spriteSeta->getWidth() + 15;
			setaY = btY - 15;
			//btSelecionado = true;
		break;
		case ESTADO_GRUPO:

		break;
		case ESTADO_OK:
			setaX = aidX - spriteSeta->getWidth()/2 - 10;
			setaY = aidY + spriteAid->getHeight()/2 - spriteSeta->getHeight()/2;
			estadoAtual = ESTADO_AID;
			//btSelecionado = false;
		break;
		}
	}

	if(InputManager::getInputManager()->isKeyDown(SDLK_RIGHT)){
		sfxBlip->play(0);
		switch(estadoAtual){
		case ESTADO_AID:
			for(int i = 0; i < 3; i++){
				int setaAuxX = aidX+180*i - spriteSeta->getWidth()/2 - 10;
				if(setaX == setaAuxX){
					if(i == 2){
						setaX = aidX+180*0 - spriteSeta->getWidth()/2 - 10;
						aidEscolhido = 0;
					}
					else{
						setaX = aidX+180*(i+1) - spriteSeta->getWidth()/2 -10;
						aidEscolhido = i+1;
					}
					//printf("setaX: %d setAuxX %d escolhido: %d\n",setaX, setaAuxX,aidEscolhido);
					break;
				}
			}
		break;
		case ESTADO_GRUPO:
			for(int i = 0; i < vetSpriteGrupo.size(); i++){
				int setaAuxX = grupoX*((i%3)+1)+70*(i%3) - spriteSeta->getWidth()/2 - 10;

				if(setaX == setaAuxX){
					if(i == (vetSpriteGrupo.size() - 1))
					{
						populaTextoGrupo(0);
						setaX = grupoX*((0%3)+1)+70*(0%3) - spriteSeta->getWidth()/2 - 10;
						setaY = grupoY*((0/3)+1)+10*(0/3);
					}
					else {
						setaX = grupoX*(((i+1)%3)+1)+70*((i+1)%3) - spriteSeta->getWidth()/2 - 10;
						setaY = grupoY*(((i+1)/3)+1)+10*((i+1)/3);
						populaTextoGrupo(i+1);
					}
					break;
				}
			}

		break;
		case ESTADO_OK:

		break;
		}
	}
	if(InputManager::getInputManager()->isKeyDown(SDLK_LEFT)){
		sfxBlip->play(0);
		//("foi pro lado esquerda \n");
		switch(estadoAtual){
		case ESTADO_AID:
			for(int i = 0; i < 3; i++){
				int setaAuxX = aidX+180*i - spriteSeta->getWidth()/2 - 10;
				//printf("setaX: %d setAuxX %d escolhido: %d\n",setaX, setaAuxX,aidEscolhido);
				if(setaX == setaAuxX){
					if(i == 0){
						setaX = aidX+180*2 - spriteSeta->getWidth()/2 - 10;
						aidEscolhido = 2;
					}
					else{
						setaX = aidX+180*(i-1) - spriteSeta->getWidth()/2 - 10;
						aidEscolhido = i-1;
					}

					break;
				}
			}
		break;
		case ESTADO_GRUPO:
			for(int i = 0; i < vetSpriteGrupo.size(); i++){
				int setaAuxX = grupoX*((i%3)+1)+70*(i%3) - spriteSeta->getWidth()/2 - 10;

				if(setaX == setaAuxX){
					if(i == 0)
					{
						setaX = grupoX*(((vetSpriteGrupo.size() -1 )%3)+1)+70*((vetSpriteGrupo.size() - 1)%3)  - spriteSeta->getWidth()/2 - 10;
						setaY = grupoY*(((vetSpriteGrupo.size() - 1)/3)+1)+10*((vetSpriteGrupo.size() - 1)/3);
						populaTextoGrupo((vetSpriteGrupo.size() -1 ));
					}
					else {
						setaX = grupoX*(((i-1)%3)+1)+70*((i-1)%3) - spriteSeta->getWidth()/2 - 10;
						setaY = grupoY*(((i-1)/3)+1)+10*((i-1)/3);
						populaTextoGrupo(i-1);

					}
					break;
				}
		}
		break;
		case ESTADO_OK:

		break;
		}
	}
}

void StateSelecaoAID::render(){
	background->render(0,0);
	if(btSelecionado)
		botaoSelecionado->render(btX,btY);
	else
		botao->render(btX,btY);

	for(int i=0 ; i < vetAid.size(); i++){
		//printf("vetaid[%d] = %d\n",i,vetAid[i]);
		if(vetAid[i] >= 0){
			//printf("posicao: %d\n",aidX+160*i,aidY);
			vetSpriteAid[vetAid[i]]->render(aidX+180*i,aidY);
		}
	}

	for(int i=0 ; i< vetSpriteGrupo.size(); i++){
		//i%3 para saber em qual linha - +1 para nao dar zero
		//grupoX e a pos inicial dos quadrados
		//20 = gap
		vetSpriteGrupo[i]->render(grupoX*((i%3)+1)+70*(i%3),grupoY*((i/3)+1)+20*(i/3));
	}


	for(int i=0 ; i< textoMultiplicadores.size(); i++){
		textoMultiplicadores[i]->render();
	}

	spriteSeta->render(setaX, setaY);

	for(int i = 0; i < textoAid.size(); i++){
		textoAid[i]->render();
	}

	if(estadoAtual == ESTADO_GRUPO){
		for(int i = 0; i < textoGrupo.size(); i++){
			textoGrupo[i]->render();
		}
	}

	if(levelDisponivel)
	{
		if(timerLevelDisponivel.getTime() < 500)
			iconeLevelDisponivel->render(220,280);
		if(timerLevelDisponivel.getTime() > 1000)
			timerLevelDisponivel.start();
	}

}

void StateSelecaoAID::populaTextoAid() {
	valorAtaque = 0;
	valorInteligencia = 0;
	valorDefesa = 0;
	valorLife = 0;

	if(vetAid[0] != -1) {
		PersonagemAtivo *personagemAux = grupoCenario->vetorPersonages[vetAid[0]];

		if(personagemAux->tipo == ATAQUE)
			valorAtaque += 2*personagemAux->habilidade.ataque;
		else
			valorAtaque += personagemAux->habilidade.ataque;

		valorInteligencia += personagemAux->habilidade.inteligencia;
		valorDefesa += personagemAux->habilidade.defesa;
		valorLife += personagemAux->life;
	}

	if(vetAid[1] != -1) {
		PersonagemAtivo *personagemAux = grupoCenario->vetorPersonages[vetAid[1]];
		valorAtaque += personagemAux->habilidade.ataque;

		if(personagemAux->tipo == INTELIGENCIA)
			valorInteligencia += 2*personagemAux->habilidade.inteligencia;
		else
			valorInteligencia += personagemAux->habilidade.inteligencia;

		valorDefesa += personagemAux->habilidade.defesa;
		valorLife += personagemAux->life;
	}

	if(vetAid[2] != -1) {
		PersonagemAtivo *personagemAux = grupoCenario->vetorPersonages[vetAid[2]];
		valorAtaque += personagemAux->habilidade.ataque;
		valorInteligencia += personagemAux->habilidade.inteligencia;

		if(personagemAux->tipo == DEFESA)
			valorDefesa += 2*personagemAux->habilidade.defesa;
		else
			valorDefesa += personagemAux->habilidade.defesa;

		valorLife += personagemAux->life;
	}

	valorAtaque *= grupoCenario->level->getAttackLevel();
	valorInteligencia *= grupoCenario->level->getIntelligenceLevel();
	valorDefesa *= grupoCenario->level->getDefenseLevel();

	char strAtaque[50];
	sprintf(strAtaque,"ATT - %d",valorAtaque);

	char strIteligencia[50];
	sprintf(strIteligencia,"INT - %d",valorInteligencia);

	char strDefesa[50];
	sprintf(strDefesa,"DEF - %d",valorDefesa);

	char strLife[50];
	sprintf(strLife,"LIFE - %d",valorLife);

	textoAid[0]->setText(strAtaque);
	textoAid[1]->setText(strIteligencia);
	textoAid[2]->setText(strDefesa);
	textoAid[3]->setText(strLife);
}


void StateSelecaoAID::populaTextoGrupo(int indicePersonagem) {
	PersonagemAtivo * personagemAux = grupoCenario->vetorPersonages[indicePersonagem];

	char strAtaque[50];
	sprintf(strAtaque,"ATT - %d",personagemAux->habilidade.ataque);

	char strIteligencia[50];
	sprintf(strIteligencia,"INT - %d",personagemAux->habilidade.inteligencia);

	char strDefesa[50];
	sprintf(strDefesa,"DEF - %d",personagemAux->habilidade.defesa);

	char strLife[50];
	sprintf(strLife,"LIFE - %d",personagemAux->life);

	textoGrupo[0]->setText(personagemAux->nome);
	textoGrupo[1]->setText(strAtaque);
	textoGrupo[2]->setText(strIteligencia);
	textoGrupo[3]->setText(strDefesa);
	textoGrupo[4]->setText(strLife);
}
