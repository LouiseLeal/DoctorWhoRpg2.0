/*
 * Batalha.cpp
 *
 *  Created on: May 30, 2013
 *      Author: Carol
 */

#ifndef BATALHA_CPP_
#define BATALHA_CPP_

#include "../headers/StateBatalha.h"

int StateBatalha::unload() {
	return 0;
}

void StateBatalha::load(int pilha) {
	GAME_OVER = false;
	FIM_BATALHA = false;
	defesaViloes = 0;
	defesaMocinhos = 0;
	ATAQUE_MOCINHOS = true;
	ATAQUE_VILOES = false;
	estado_mocinhos = ESTADOTIPOACAO;
	estado_viloes = 0;
	PRIMEIRO_LOAD = true;
	ESPERA_INPUT = false;
	background = new Sprite("../images/battleBackground.bmp");
	//background->rotoZoom(0,1,2,true);
	spCaixaTexto = new Sprite("../images/tardis_box.png");
	tbPosX = (800/2) - (spCaixaTexto->getWidth() / 2);
	tbPosY = 600 - spCaixaTexto->getHeight() - 10;

	SDL_Color cor = {255,255,255};
	txDano = new Text("../fonts/CCRedAlert.ttf","dano",30,1,cor,0,0);
	bgVitoria = new Sprite("../images/background_vitoria.png");
	waitTimer = 0;
	retornoFimBatalha = ESTADO_BATALHA;

	txtExperiencia = new Text("../fonts/CCRedAlert.ttf","Experience: ",30,1,cor,340,300);
	txtPassouLevel = new Text("../fonts/CCRedAlert.ttf","Level Up!",18,1,cor,320,380);

	tileSet = new TileSet(64,64, "../images/TileSetLondres.png");
	tileMap = new TileMap("../resources/TileMapBatalhaLondres.txt", tileSet);

	sfxBackgroundMusic = new Audio("../sfx/battleSong.mp3",0);
	sfxVictory = new Audio("../sfx/VICTORY.wav",1);
	sfxBlip = new Audio("../sfx/Blip.wav",1);
	sfxLevaDano = new Audio("../sfx/recebe dano.wav",1);
	sfxItem = new Audio("../sfx/item.wav",1);

	lifeBar = new Sprite("../images/lifeBar.png");
	lifeVermelho = new Sprite("../images/red.png");
	lifeVerde = new Sprite("../images/green.png");
	lifeAmarelo = new Sprite("../images/yellow.png");

	spriteVictory = new Sprite("../images/victory!.png");
	spriteLevelUp = new Sprite("../images/levelUp.png");

	barMocinhosX = 490;
	barMocinhosY = 410;

	barViloesX = barMocinhosX - 420;
	barViloesY = barMocinhosY;

	probDeixarBatalha = 75;

	txtNomeAtaque = new Text("../fonts/CCRedAlert.ttf","walk",20,TTF_STYLE_NORMAL,cor,260,488);
	txtTipoAtaque = new Text("../fonts/CCRedAlert.ttf","tipo",20,TTF_STYLE_NORMAL,cor,260,528);;

}

void StateBatalha::setGrupoMocinhos(GrupoCenario *vGrupoMocinhos) {
	escolheuItem = false;
	porcentagemExperiencia = 1;
	sfxBackgroundMusic->play(500);
	grupoMocinhos = vGrupoMocinhos;
	grupoBatalhaMocinhos = new GrupoBatalha(grupoMocinhos->level,grupoMocinhos->vectorPersonagensBatalha);
	grupoBatalhaMocinhos->calculaValores();
	grupoViloes = new GrupoViloes(grupoMocinhos->getLevel());
	printf("Level viloes: %d %d %d\n",grupoViloes->level->getAttackLevel(),grupoViloes->level->getIntelligenceLevel(),grupoViloes->level->getDefenseLevel());
	grupoBatalhaViloes = new GrupoBatalha(grupoViloes->getLevel(),grupoViloes->listVilans);
	grupoBatalhaViloes->calculaValores();
	vinteLifeViloes = grupoBatalhaViloes->lifeValue*0.2;
	GAME_OVER = false;
	FIM_BATALHA = false;
	estado_mocinhos = ESTADOTIPOACAO;
	estado_viloes = 0;
	ATAQUE_MOCINHOS = true;
	ATAQUE_VILOES = false;
	PASSOU_LEVEL = false;
	retornoFimBatalha = ESTADO_BATALHA;

	animacaoSelecionada = NULL;
	personagemSelecionado = NULL;
	ataqueSelecionado = NULL;

	//ATENCAO!!!! -------------- SIMULANDO PERDA!!!
	//grupoBatalhaMocinhos->lifeValue = 10;
	//ATENCAO!!!! -------------- SIMULANDO PERDA!!!

// ATUALIZANDO POSICAO DE BATALHA DOS PERSONAGENS
	/*
	 * 672,256
	 * 608,320
	 * 672,384
	 *
	 * Viloes: 	- 64*7.5 = 480
	 * 			- 64*5.5 = 352
	 */
	int posMocinhosX[] = {672,608,672};
	int posMocinhosY[] = {256,320,384};

	vector<PersonagemAtivo*>::iterator itAux;
	int i = 0;
	for(itAux = grupoMocinhos->vectorPersonagensBatalha.begin(); itAux < grupoMocinhos->vectorPersonagensBatalha.end(); itAux++){
		(*itAux)->setCurrentAnimation("posicao_batalha");
		(*itAux)->boundingBox.posX = posMocinhosX[i];
		(*itAux)->boundingBox.posY = posMocinhosY[i];
		i++;
	}

	printf("size vet personagens %lu\n",grupoMocinhos->vectorPersonagensBatalha.size());
	printf("%f %f\n",grupoMocinhos->vectorPersonagensBatalha.front()->boundingBox.posX,grupoMocinhos->vectorPersonagensBatalha.front()->boundingBox.posY);

	int dif = 480;
	i = 0;
	for(itAux = grupoViloes->listVilans.begin(); itAux < grupoViloes->listVilans.end(); itAux++){
		(*itAux)->setCurrentAnimation("posicao_batalha");

		if(i== 1)
			dif = 352;
		else
			dif = 480;
		(*itAux)->boundingBox.posX = posMocinhosX[i] - dif;
		(*itAux)->boundingBox.posY = posMocinhosY[i];
		i++;
	}
//--------------

	printf("NEXT LEVEL: %d\n",grupoMocinhos->nextLevel);
	defesaViloes = 0;
	defesaMocinhos = 0;
	ESPERA_INPUT = false;
	ESTADO_ANIMACAO = 0;

	Camera::cameraX = 0;
	Camera::cameraY = 0;


//------------------
	vidaInicialMocinhos = grupoBatalhaMocinhos->lifeValue;
	vidaInicialViloes = grupoBatalhaViloes->lifeValue;

	lifeBarMocinhos = 56;
	lifeBarViloes = 56;
	waitTimer = 0;
	timerRender.start();
}

/*
 * Estado de grame over: retorna 0 para fim de jogo
 * Estado de win: retorno 1 para o state de jogo
 * Estado de continua batalha retorna 2
 *
 * ATAQUE_MOCINHOS
 * estado_mocinhos:
 * 	0: Update - pega os tipos de ataques diposniveis no grupo selecionado (Ataque e/ou Inteligencia e/ou Defea)
 * 	1: Render - mostra na tela os tipos de ataques disponiveis para escolha
 * 	2: Update - dado o tipo de ataque escolhido, seleciona os ataques disponiveis daquele tipo
 * 	3: Render - mostra os ataques disponiveis para escolha
 * 	4: Update - dado o ataque escolhido, realiza o calculo dos danos e aplica o ataque
 * 	5: Render - renderiza a animacao do ataque. Cria um wait ate que a animacao seja toda tocada. Troca contexto.
 *
 * 	ATAQUE_VILOES
 * 	estado_viloes:
 * 	0: Update - escolhe randomicamente um ataque disponivel e calcula os danos
 * 	1: Render - Toca a animacao do ataque escolhido. Cria um wait ate que a animacao seja toda tocada. Troca contexto.
 */
int StateBatalha::update(int deltaFrame) {
	processEvents();
	vector<PersonagemAtivo*> itPersonagem;
	bool seguraUpdate = false;
	//update das posicoes dos mocinhos
	vector<PersonagemAtivo*>::iterator itAux;
	for(itAux = grupoMocinhos->vectorPersonagensBatalha.begin(); itAux < grupoMocinhos->vectorPersonagensBatalha.end(); itAux++){
		(*itAux)->update(deltaFrame);
		if((*itAux)->currentAnimation->animationRunning())
			seguraUpdate = true;
	}

	if(animacaoSelecionada != NULL && animacaoSelecionada->running){
		seguraUpdate = true;
		ESTADO_ANIMACAO = 1;
	}


	//update das posicoes dos viloes
	for(itAux = grupoViloes->listVilans.begin(); itAux < grupoViloes->listVilans.end(); itAux++){
		(*itAux)->update(deltaFrame);
		if((*itAux)->currentAnimation->animationRunning())
			seguraUpdate = true;
	}

	//printf("waitTime: %d\n",waitTimer);
	if(timerRender.getTime() < waitTimer)
		seguraUpdate = true;

	//printf("Estadosmocinhos: %d %d %d %d\n",estado_mocinhos, ESPERA_INPUT,seguraUpdate, ATAQUE_MOCINHOS);
	if(seguraUpdate)
		return ESTADO_BATALHA;

	if(ESTADO_ANIMACAO == 1) {
		if(ataqueSelecionado->tipoAtaque == DEFESA){
			for(int i = 0; i < grupoMocinhos->vectorPersonagensBatalha.size(); i++)
				grupoMocinhos->vectorPersonagensBatalha[i]->setCurrentAnimation("posicao_batalha");
		}
		else
			personagemSelecionado->setCurrentAnimation("posicao_batalha");
		ESTADO_ANIMACAO = 2;
	}

	if (ATAQUE_MOCINHOS) {
		if(estado_mocinhos == ESTADORUN){
			int probRun = rand() % 100;
			if(probRun <= probDeixarBatalha){
				sfxBackgroundMusic->stop();
				return ESTADO_CENARIO;
			}
		}
		else if (estado_mocinhos == ESTADOTIPOACAO && !ESPERA_INPUT) {
			//printf("uahsiudhaiuhfiuahiduofaiusdf\n");
			for(itAux = grupoViloes->listVilans.begin(); itAux < grupoViloes->listVilans.end(); itAux++){
				(*itAux)->setCurrentAnimation("posicao_batalha");
			}
			listaTiposAtaques = getListaTiposAtaques();
			Sprite *sprite = new Sprite("../images/seta_branca.png");
			textoTipoAcao = new TextOpcoes(listaTiposAtaques, tbPosX + 25 + 32, tbPosY + 58,20,sprite);
		} else if (estado_mocinhos == ESTADOTIPOATAQUE && !ESPERA_INPUT) {
			listaAtaques = getListaAtaque(tipoEscolhido);

			//printf("max: %d\n",textoTipoAcao->getWidthMax());
			Sprite *sprite = new Sprite("../images/seta_branca.png");
			textoAtaque = new TextOpcoes(listaAtaques,textoTipoAcao->getWidthMax() + tbPosX + 25 + 64, tbPosY + 58,20,sprite);

		} else if (estado_mocinhos == ESTADOATAQUESELECIONADO && !ESPERA_INPUT) {
			if(opcaoEscolhida == 2){
				getAtaqueSelecionado("Defence");
			}
			else {
				getAtaqueSelecionado(listaAtaques[opcaoEscolhida]);
			}

			ataqueMocinhos(ataqueSelecionado);
			txtNomeAtaque->setText(ataqueSelecionado->nome);
			string strTipo;
			if(ataqueSelecionado->tipoAtaque == ATAQUE){
				if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0)
					strTipo = "Type: Attack";
				else
					strTipo = "Tipo: Ataque";
			}
			else if(ataqueSelecionado->tipoAtaque == INTELIGENCIA){
					if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0)
						strTipo = "Type: Intelligence";
					else
						strTipo = "Tipo: Inteligencia";
			}
			else if(ataqueSelecionado->tipoAtaque == DEFESA){
					if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0)
						strTipo = "Type: Defence";
					else
						strTipo = "Tipo: Defesa";
			}
			txtTipoAtaque->setText(strTipo);
			//printf("FileName: %s\n",sfxAtaque->fileName.c_str());
			sfxAtaque->play(0);

			//DEBUG
			printf("Life Mocinhos: %d\tLife Viloes %d\nDano aplicado Por mocinhos: %d\n",grupoBatalhaMocinhos->lifeValue, grupoBatalhaViloes->lifeValue,danoAplicado);
			printf("GAME: %d\tFIM_B: %d\n", GAME_OVER, FIM_BATALHA);

		}else if(estado_mocinhos == ESTADOTIPOITEM && !ESPERA_INPUT){
			//para imprimir os itens que o personagem tem
			listaItens=getListaItem();
			Sprite *sprite = new Sprite("../images/seta_branca.png");
			textoItem = new TextOpcoes(listaItens,textoTipoAcao->getWidthMax() + tbPosX + 25 + 64, tbPosY + 58, 20, sprite);

		}else if(estado_mocinhos == ESTADOITEMSELECIONADO && !ESPERA_INPUT){
			//para pegar o item que foi selecionado na batalha

			printf("Item selecionadoo!\n");
			itemSelecionado = grupoMocinhos->listaItens[opcaoEscolhida];


			if(itemSelecionado->attackEffect != 0)
				grupoBatalhaMocinhos->attackValue += (grupoBatalhaMocinhos->attackValue * itemSelecionado->attackEffect)/100;
			if(itemSelecionado->inteligenceEffect != 0)
				grupoBatalhaMocinhos->inteligenceValue += (grupoBatalhaMocinhos->inteligenceValue * itemSelecionado->inteligenceEffect)/100;
			if(itemSelecionado->defenseEffect != 0)
				grupoBatalhaMocinhos->defenceValue += (grupoBatalhaMocinhos->defenceValue * itemSelecionado->defenseEffect)/100;
			if(itemSelecionado->hpEffect != 0){
				grupoBatalhaMocinhos->lifeValue += itemSelecionado->hpEffect;
				if(vidaInicialMocinhos < grupoBatalhaMocinhos->lifeValue)
					grupoBatalhaMocinhos->lifeValue = vidaInicialMocinhos;
			}
			if(itemSelecionado->xpEffect != 0)
				porcentagemExperiencia += itemSelecionado->xpEffect;

			sfxItem->play(0);
		}
		else if(estado_mocinhos == ESTADOVITORIA){
			grupoMocinhos->experiencia += (vinteLifeViloes/0.2) + ((vinteLifeViloes/0.2)*porcentagemExperiencia/100);
			sfxBackgroundMusic->stop();
			sfxVictory->play(0);
			printf("Level atual: %d proxLvel: %d\n",grupoMocinhos->experiencia, grupoMocinhos->nextLevel);
			if(grupoMocinhos->experiencia >= grupoMocinhos->nextLevel){
				grupoMocinhos->nextLevel = 2*exp(grupoMocinhos->level->getTotalLevel()*0.7) + 200;
				grupoMocinhos->levelDisponivel++;
				printf("grupoMocinhos level up %d\n",grupoMocinhos->levelDisponivel);
				PASSOU_LEVEL = true;
			}
			char strExperiencia[50];
			int valorExperiencia = (int)vinteLifeViloes / 0.2;
			printf("valor exp: %d\n",valorExperiencia);
			if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0)
				sprintf(strExperiencia,"Experience: %d",valorExperiencia);
			else
				sprintf(strExperiencia,"Experiencia: %d",valorExperiencia);

			txtExperiencia->setText(strExperiencia);
			ATAQUE_MOCINHOS = false;
			ATAQUE_VILOES = false;
		}
		else if(estado_mocinhos == ESTADORENDER){

			if(!escolheuItem) {
				if(ataqueSelecionado->tipoAtaque != DEFESA) {
					ATAQUE_VILOES = true;
					ATAQUE_MOCINHOS = false;
					sfxLevaDano->play(3);
					estado_mocinhos = ESTADOTIPOACAO;
					estado_viloes = ESTADOLEVADANO;
					for(itAux = grupoViloes->listVilans.begin(); itAux < grupoViloes->listVilans.end(); itAux++){
						(*itAux)->setCurrentAnimation("leva_ataque");
					}
				}
				else {
					printf("nao levou ataque viloes!!!\n");
					ATAQUE_VILOES = true;
					ATAQUE_MOCINHOS = false;
					estado_mocinhos = ESTADOTIPOACAO;
					estado_viloes = 0;
					for(itAux = grupoViloes->listVilans.begin(); itAux < grupoViloes->listVilans.end(); itAux++){
						(*itAux)->setCurrentAnimation("posicao_batalha");
					}
				}
			}
			else {
				ATAQUE_VILOES = true;
				ATAQUE_MOCINHOS = false;
				estado_mocinhos = ESTADOTIPOACAO;
				estado_viloes = 0;
				lifeBarMocinhos = (grupoBatalhaMocinhos->lifeValue * 56)/ vidaInicialMocinhos;
			}
		}
		else if(estado_mocinhos == ESTADOLEVADANO){
			printf("Leva ataque viloes!!!\n");
			ATAQUE_VILOES = false;
			ATAQUE_MOCINHOS = true;
			estado_mocinhos = ESTADOTIPOACAO;
			estado_viloes = 0;
			for(itAux = grupoMocinhos->vectorPersonagensBatalha.begin(); itAux < grupoMocinhos->vectorPersonagensBatalha.end(); itAux++){
				(*itAux)->setCurrentAnimation("posicao_batalha");
			}
			//update life bars
			lifeBarMocinhos = (grupoBatalhaMocinhos->lifeValue * 56)/ vidaInicialMocinhos;
		}

	} else if (ATAQUE_VILOES) {
		if(estado_viloes == 0) {
			ataqueSelecionado = grupoViloes->selecionaAtaque();
			//printf("Ataque escolhido pelos viloes: %d\n",ataqueSelecionado->tipoAtaque);
			ataqueViloes(ataqueSelecionado);
			Animation *aniAux = grupoBatalhaViloes->personagemAtaque->listAnimacoes[ataqueSelecionado->nome];
			sfxAtaque = aniAux->sfxAnimation;
			sfxAtaque->play(0);
			txtNomeAtaque->setText(ataqueSelecionado->nome);
			string strTipo;
			if(ataqueSelecionado->tipoAtaque == ATAQUE){
				if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0)
					strTipo = "Type: Attack";
				else
					strTipo = "Tipo: Ataque";
			}
			else if(ataqueSelecionado->tipoAtaque == INTELIGENCIA){
					if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0)
						strTipo = "Type: Intelligence";
					else
						strTipo = "Tipo: Inteligencia";
			}
			else if(ataqueSelecionado->tipoAtaque == DEFESA){
					if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0)
						strTipo = "Type: Defense";
					else
						strTipo = "Tipo: Defesa";
			}
			txtTipoAtaque->setText(strTipo);
			estado_viloes = 1;
			printf("Life Mocinhos: %d\tLife Viloes %d\nDano aplicado Por viloes: %d\n",grupoBatalhaMocinhos->lifeValue, grupoBatalhaViloes->lifeValue,danoAplicado);
			printf("GAME: %d\tFIM_B: %d\n", GAME_OVER, FIM_BATALHA);
		}
		else if(estado_viloes == ESTADORENDER){
			if(ataqueSelecionado->tipoAtaque != DEFESA){
			ATAQUE_MOCINHOS = true;
			ATAQUE_VILOES = false;
			sfxLevaDano->play(3);
			estado_viloes = 0;
			estado_mocinhos = ESTADOLEVADANO;
			for(itAux = grupoMocinhos->vectorPersonagensBatalha.begin(); itAux < grupoMocinhos->vectorPersonagensBatalha.end(); itAux++){
				(*itAux)->setCurrentAnimation("leva_ataque");
			}
			}else{
				ATAQUE_MOCINHOS = true;
				ATAQUE_VILOES = false;
				estado_viloes = 0;
				estado_mocinhos = ESTADOTIPOACAO;
				for(itAux = grupoMocinhos->vectorPersonagensBatalha.begin(); itAux < grupoMocinhos->vectorPersonagensBatalha.end(); itAux++){
					(*itAux)->setCurrentAnimation("posicao_batalha");
				}

			}
		}
		if(estado_viloes == ESTADOLEVADANO){
			//printf("Leva ataque viloes!!!\n");
			ATAQUE_MOCINHOS = false;
			ATAQUE_VILOES = true;
			estado_viloes = 0;
			estado_mocinhos = ESTADOTIPOACAO;
			for(itAux = grupoViloes->listVilans.begin(); itAux < grupoViloes->listVilans.end(); itAux++){
				(*itAux)->setCurrentAnimation("posicao_batalha");
			}
			//update barra de life
			lifeBarViloes = (grupoBatalhaViloes->lifeValue * 56)/ vidaInicialViloes;
		}
	}

	if (GAME_OVER)
		return ESTADO_GAME_OVER;
	else if (FIM_BATALHA){
		estado_mocinhos = ESTADOVITORIA;
		if(retornoFimBatalha != ESTADO_BATALHA){
			sfxVictory->stop();
			sfxBackgroundMusic->stop();
		}
		return retornoFimBatalha;
	}
	else
		return ESTADO_BATALHA;
}

/*
 * ATAQUE_MOCINHOS
 * estado_mocinhos:
 * 	0: Update - pega os tipos de ataques diposniveis no grupo selecionado (Ataque e/ou Inteligencia e/ou Defea)
 * 	1: Render - mostra na tela os tipos de ataques disponiveis para escolha
 * 	2: Update - dado o tipo de ataque escolhido, seleciona os ataques disponiveis daquele tipo
 * 	3: Render - mostra os ataques disponiveis para escolha
 * 	4: Update - dado o ataque escolhido, realiza o calculo dos danos e aplica o ataque
 * 	5: Render - renderiza a animacao do ataque. Cria um wait ate que a animacao seja toda tocada. Troca contexto.
 *
 * 	ATAQUE_VILOES
 * 	estado_viloes:
 * 	0: Update - escolhe randomicamente um ataque disponivel e calcula os danos
 * 	1: Render - Toca a animacao do ataque escolhido. Cria um wait ate que a animacao seja toda tocada. Troca contexto.
 */
void StateBatalha::render() {
	background->render(0,0);
	//tileMap->render();

	spCaixaTexto->render(tbPosX, tbPosY);
	if (ATAQUE_MOCINHOS) {
		if (estado_mocinhos == ESTADOTIPOACAO) {
			ESPERA_INPUT = true;
			textoSelecionado = textoTipoAcao;
			textoSelecionado->render(true);

		} else if (estado_mocinhos == ESTADOTIPOATAQUE) {
			ESPERA_INPUT = true;
			textoSelecionado = textoAtaque;
			textoAtaque->render(true);
			textoTipoAcao->render(false);

		} else if (estado_mocinhos == ESTADOTIPOITEM) {
			ESPERA_INPUT = true;
			textoSelecionado = textoItem;
			textoTipoAcao->render(false);
			textoItem->render(true);

		} else if (estado_mocinhos == ESTADOATAQUESELECIONADO) {
			//txDano->render();
			//timerRender.start();
			//printf("START timer: %d\n",Render.getTime());
			//waitTimer = 100;
			estado_mocinhos = ESTADORENDER;
		}
		else if (estado_mocinhos == ESTADORENDER){
			//faz nada
			if(escolheuItem)
				itemSelecionado->sprite->render(690,300);
		}else if (estado_mocinhos == ESTADOLEVADANO){
			txDano->render();

		}else if( estado_mocinhos == ESTADOITEMSELECIONADO ){
			timerRender.start();
			itemSelecionado->sprite->render(690,300);
			waitTimer = 1000;
			estado_mocinhos = ESTADORENDER;
			//fazer ainda
		}
	} else if (ATAQUE_VILOES) {
		if(estado_viloes == 1) {
			//txDano->render();
			estado_viloes = ESTADORENDER;
		}
		else if(estado_viloes == ESTADORENDER){
		}else if (estado_viloes == ESTADOLEVADANO){
			txDano->render();

		}
	//mudar render do vilao
	}

	if(ATAQUE_MOCINHOS || ATAQUE_VILOES)
	{
		lifeBar->render(barMocinhosX, barMocinhosY);
		lifeBar->render(barViloesX, barViloesY);
			// 28 = 50% das barrinhas de life
			Sprite *spriteBarra;
			if(lifeBarMocinhos > 28)
				spriteBarra = lifeVerde;
			// 12 = 20% das barrinhas de life
			else if( lifeBarMocinhos > 12)
				spriteBarra = lifeAmarelo;
			else
				spriteBarra = lifeVermelho;

			for(int i = 0; i < lifeBarMocinhos; i++)
				spriteBarra->render(barMocinhosX + 4 + i*spriteBarra->getWidth(),barMocinhosY + 4);

			if(lifeBarViloes > 28)
				spriteBarra = lifeVerde;
			else if( lifeBarViloes > 12)
				spriteBarra = lifeAmarelo;
			else
				spriteBarra = lifeVermelho;

			for(int i = 0; i < lifeBarViloes; i++)
				spriteBarra->render(barViloesX + 4 + i*spriteBarra->getWidth(),barViloesY + 4);
	}

	//render personagens na tela
	bool seguraRender = false;
	vector<PersonagemAtivo*> itPersonagem;
	//update das posicoes dos mocinhos
	vector<PersonagemAtivo*>::iterator itAux;
	for(itAux = grupoMocinhos->vectorPersonagensBatalha.begin(); itAux < grupoMocinhos->vectorPersonagensBatalha.end(); itAux++){
		(*itAux)->render();
		if((*itAux)->currentAnimation->running)
			seguraRender = true;
	}

	//update das posicoes dos viloes
	for(itAux = grupoViloes->listVilans.begin(); itAux < grupoViloes->listVilans.end(); itAux++){
		(*itAux)->render();
		if((*itAux)->currentAnimation->running)
			seguraRender = true;
	}

	if(seguraRender){
		txtNomeAtaque->render();
		txtTipoAtaque->render();
	}

	if(FIM_BATALHA && !seguraRender){
		//printf("Fim batalha e not segura render\n");
		bgVitoria->render(100,80);
		int victoryX = (bgVitoria->getWidth()/2 - spriteVictory->getWidth()/2);
		int victorY = spriteVictory->getHeight() + 10;
		spriteVictory->render(100 + victoryX, victorY + 60);
		txtExperiencia->render();
		if(PASSOU_LEVEL){
			//txtPassouLevel->render();
			if(timerLevelUp.getTime() < 500)
				spriteLevelUp->render(320,380);
			if(timerLevelUp.getTime() > 1000)
				timerLevelUp.start();
		}
	}

}

vector<string> StateBatalha::getListaTiposAtaques() {
	//vector<Ataque*>::iterator iteratorAtaque;
	map<string,Ataque*>::iterator iteratorAtaque;
	vector<PersonagemAtivo*>::iterator iteratorPersonagem;
	vector<string> vectorAux;

	bool ataque = false;
	bool inteligencia = false;
	bool defesa = false;
	if (grupoMocinhos->vetorPersonages.empty()) {
		printf("Vetor de mocinhos vazio. \n");
		exit(1);
	}

	for (iteratorPersonagem = grupoMocinhos->vetorPersonages.begin();
			iteratorPersonagem < grupoMocinhos->vetorPersonages.end();
			iteratorPersonagem++) {
		if (!(*iteratorPersonagem)->listAttack.empty()) {
			//for (iteratorAtaque = (*iteratorPersonagem)->listAttack.begin();iteratorAtaque < (*iteratorPersonagem)->listAttack.end(); iteratorAtaque++) {
			for (iteratorAtaque = (*iteratorPersonagem)->listAttack.begin();iteratorAtaque != (*iteratorPersonagem)->listAttack.end(); ++iteratorAtaque) {
				//itera pelos ataques de cada personage

				if ((*iteratorAtaque).second->tipoAtaque == ATAQUE)
					ataque = true;
				else if ((*iteratorAtaque).second->tipoAtaque == INTELIGENCIA)
					inteligencia = true;
				else if ((*iteratorAtaque).second->tipoAtaque == DEFESA)
					defesa = true;

				if (ataque && inteligencia && defesa)
					break;

			}
		}

		if (ataque && inteligencia && defesa)
			break;
	}
	if(strcmp(SDLBase::strLanguage.c_str(),".xml") == 0){
		if (ataque)
			vectorAux.push_back("Attack");
		else
			vectorAux.push_back("*Attack");
		if (inteligencia)
			vectorAux.push_back("Inteligence");
		else
			vectorAux.push_back("*Inteligence");
		if (defesa)
			vectorAux.push_back("Defence");
		else
			vectorAux.push_back("*Defence");
		if (!grupoMocinhos->listaItens.empty())
			vectorAux.push_back("Item");
		else
			vectorAux.push_back("*Item");

		vectorAux.push_back("Run");
	}
	else {
		if (ataque)
			vectorAux.push_back("Ataque");
		else
			vectorAux.push_back("*Ataque");
		if (inteligencia)
			vectorAux.push_back("Inteligencia");
		else
			vectorAux.push_back("*Inteligencia");
		if (defesa)
			vectorAux.push_back("Defesa");
		else
			vectorAux.push_back("*Defesa");
		if (!grupoMocinhos->listaItens.empty())
			vectorAux.push_back("Item");
		else
			vectorAux.push_back("*Item");

		vectorAux.push_back("Fugir");
	}


	return vectorAux;
}


vector<string> StateBatalha::getListaAtaque(AID_TYPES tipoAtaque) {
	//vector<Ataque*>::iterator iteratorAtaque;
	map<string,Ataque*>::iterator iteratorAtaque;
	vector<PersonagemAtivo*>::iterator iteratorPersonagem;
	vector<string> vectorAux;

	for (iteratorPersonagem = grupoMocinhos->vetorPersonages.begin();
			iteratorPersonagem < grupoMocinhos->vetorPersonages.end();
			iteratorPersonagem++) {
		//for (iteratorAtaque = (*iteratorPersonagem)->listAttack.begin();iteratorAtaque < (*iteratorPersonagem)->listAttack.end();iteratorAtaque++) {
		for (iteratorAtaque = (*iteratorPersonagem)->listAttack.begin();iteratorAtaque != (*iteratorPersonagem)->listAttack.end();iteratorAtaque++) {
			//itera pelos ataques de cada personage
			if((*iteratorAtaque).second->tipoAtaque == tipoAtaque)
				vectorAux.push_back((*iteratorAtaque).second->nome);
			//if ((*iteratorAtaque)->tipoAtaque == tipoAtaque)
				//vectorAux.push_back((*iteratorAtaque)->nome);
		}
	}

	return vectorAux;
}

vector<string> StateBatalha::getListaItem() {
	//vector<Ataque*>::iterator iteratorAtaque;
	vector<Item*>::iterator itItem;
	vector<string> vectorAux;

	for (itItem = grupoMocinhos->listaItens.begin();
			itItem < grupoMocinhos->listaItens.end();
			itItem++) {
		//for (iteratorAtaque = (*iteratorPersonagem)->listAttack.begin();iteratorAtaque < (*iteratorPersonagem)->listAttack.end();iteratorAtaque++) {
		vectorAux.push_back((*itItem)->nome);
	}

	return vectorAux;
}


void StateBatalha::ataqueMocinhos(Ataque *ataque) {
	int danoFinal = 0;
	int danoPotencial = 0;
	int resistenciaViloes = 0;
	AID_TYPES tipoAtaque = ataque->tipoAtaque;
	defesaMocinhos = 0;

	switch (tipoAtaque) {
	case ATAQUE:
		danoPotencial = grupoBatalhaMocinhos->attackValue;
		danoFinal = rand() % 8 + (danoPotencial - 2);
		resistenciaViloes = grupoBatalhaViloes->getMulAtaque();
		danoFinal -= rand() % 2 + (resistenciaViloes - 1);
		aplicaDano(danoFinal, MOCINHOS);
		break;
	case INTELIGENCIA:
		danoPotencial = grupoBatalhaMocinhos->inteligenceValue;
		danoFinal = rand() % 8 + (danoPotencial - 2);
		resistenciaViloes = grupoBatalhaViloes->getMulInteligencia();
		danoFinal -= rand() % 2 + (resistenciaViloes - 1);
		aplicaDano(danoFinal, MOCINHOS);
		break;
	case DEFESA:
		for(int i = 0; i < grupoMocinhos->vectorPersonagensBatalha.size(); i++)
			grupoMocinhos->vectorPersonagensBatalha[i]->setCurrentAnimation("Defence");
		defesaMocinhos = grupoBatalhaMocinhos->defenceValue;
	}

	danoAplicado = danoFinal;
	if (danoFinal < 0)
		danoFinal = 0;
	// char strDano[5];
}

void StateBatalha::ataqueViloes(Ataque *ataque) {
	int danoFinal = 0;
	int danoPotencial = 0;
	int resistenciaMocinhos = 0;
	AID_TYPES tipoAtaque = ataque->tipoAtaque;
	defesaViloes = 0;

	switch (tipoAtaque) {
	case ATAQUE:
		//pega o valor do ataque do grupo
		danoPotencial = grupoBatalhaViloes->attackValue;
		//calcula um valor de dano na regiao proxima ao valor do ataque
		danoFinal = rand() % 8 + (danoPotencial - 2);
		//calcula a resistencia do outro time em relacao ao tipo de ataque
		resistenciaMocinhos = grupoBatalhaMocinhos->getMulAtaque();
		//diminui a resistencia do valor do dano final
		danoFinal -= rand() % 2 + (resistenciaMocinhos - 1);
		//aplica o dano ao time rival
		aplicaDano(danoFinal, VILOES);
		break;
	case INTELIGENCIA:
		danoPotencial = grupoBatalhaViloes->inteligenceValue;
		danoFinal = rand() % 8 + (danoPotencial - 2);
		resistenciaMocinhos = grupoBatalhaMocinhos->getMulInteligencia();
		danoFinal -= rand() % 2 + (resistenciaMocinhos - 1);
		aplicaDano(danoFinal, VILOES);
		break;
	case DEFESA:
		//defesa para diminuir do ataque recebido se estiver no turno de defesa
		defesaViloes = grupoBatalhaViloes->defenceValue;
		//printf("Defesa viloes: %d\n",defesaViloes);
	}
	danoAplicado = danoFinal;

	if (danoFinal < 0)
		danoFinal = 0;

//	char strDano[5];
//	sprintf(strDano,"%d",danoAplicado);
//	txDano->setText(strDano);
//	txDano->setPos(700,200);
}

void StateBatalha::aplicaDano(int danoTotal, ATACANTE atacante) {
	if (atacante == MOCINHOS) {
		//diminui o dano do estado de defesa do time rival
		//printf("\n------Dano total: %d\n",danoTotal);
		danoTotal -= defesaViloes;
		if(danoTotal < 0)
			danoTotal = 0;
		//printf("------Dano total menos defesa: %d\n",danoTotal);
		//calcula o novo valor de vida do time rival
		int newLifeValue = grupoBatalhaViloes->lifeValue - danoTotal;
		//se a vida chegar a 0 ou menos, batalha acabou
		if (newLifeValue <= 0){
			FIM_BATALHA = true;
			//sfxBackgroundMusic->stop();
			//sfxVictory->play(0);
		}
		//seta o novo valor de vida do grupo rival
		grupoBatalhaViloes->lifeValue = newLifeValue;
		if(newLifeValue <= vinteLifeViloes)
		{
			grupoViloes->limitePAtaque = 20;
			grupoViloes->limitePInteligencia = 40;
			grupoViloes->limitePDefesa = 100;
		}
		printf("lPA %d lPI %d lPD %d\n",grupoViloes->limitePAtaque,grupoViloes->limitePInteligencia,grupoViloes->limitePDefesa);
		txDano->setPos(100,200);
	} else {
		danoTotal -= defesaMocinhos;
		if(danoTotal < 0)
			danoTotal = 0;
		int newLifeValue = grupoBatalhaMocinhos->lifeValue - danoTotal;
		//se os mocinhos chegarem a 0 ou menos de vida, o jogo acabou
		if (newLifeValue <= 0) {
			//FIM_BATALHA = true;
			GAME_OVER = true;
		}
		grupoBatalhaMocinhos->lifeValue = newLifeValue;
		txDano->setPos(700,200);
	}

	char strDano[5];
	sprintf(strDano,"%d",danoTotal);
	txDano->setText(strDano);
	//txDano->setPos(100,200);
}

void StateBatalha::processEvents() {
	InputManager::getInputManager()->update();
	if (InputManager::getInputManager()->isKeyDown(SDLK_UP)) {
		textoSelecionado->update(false);
		sfxBlip->play(0);
	}
	if (InputManager::getInputManager()->isKeyDown(SDLK_DOWN)) {
		textoSelecionado->update(true);
		sfxBlip->play(0);
	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_BACKSPACE)) {
		switch(estado_mocinhos) {
			case ESTADOTIPOATAQUE:
				estado_mocinhos = ESTADOTIPOACAO;
				break;
			case ESTADOTIPOITEM:
				estado_mocinhos = ESTADOTIPOACAO;
				break;
		}

	}
	else if (InputManager::getInputManager()->isKeyDown(SDLK_RETURN)) {
		ESPERA_INPUT = false;

		if(FIM_BATALHA){
			retornoFimBatalha = ESTADO_CENARIO;
		}

		switch(estado_mocinhos) {
		case ESTADOTIPOACAO:
			opcaoEscolhida = textoTipoAcao->getOpcao();
			//printf("opcao escolhida acao %d\n",opcaoEscolhida);
			if (opcaoEscolhida == 3)
				estado_mocinhos = ESTADOTIPOITEM;
			else if(opcaoEscolhida == 4) {
				//printf("Run\n");
				estado_mocinhos = ESTADORUN;
			}
			else if(opcaoEscolhida == 2) {
				//printf("Defesa\n");
				//opcaoEscolhida = -1;
				estado_mocinhos= ESTADOATAQUESELECIONADO;
			}
			else {
				estado_mocinhos = ESTADOTIPOATAQUE;
				tipoEscolhido = (AID_TYPES) opcaoEscolhida;
			}
			break;
		case ESTADOTIPOATAQUE :
			opcaoEscolhida = textoAtaque->getOpcao();
			//printf("opcao escolhida ataque %d\n",opcaoEscolhida);
			estado_mocinhos= ESTADOATAQUESELECIONADO;
			escolheuItem = false;
			break;
		case ESTADOTIPOITEM:
			opcaoEscolhida = textoItem->getOpcao();
			estado_mocinhos = ESTADOITEMSELECIONADO;
			escolheuItem = true;
			break;

		}
	}


}

/*
void StateBatalha::getAtaqueSelecionado(string nomeAtaque) {
	vector<PersonagemAtivo*>::iterator iteratorPersonagem;
	vector<Ataque*>::iterator itAtaque;
	vector<Animation*>::iterator itAnimacao;
	map<string,Ataque*> mapAux;
	//printf("nome ataque %s\n",nomeAtaque.c_str());
	for (iteratorPersonagem = grupoMocinhos->vetorPersonages.begin(); iteratorPersonagem < grupoMocinhos->vetorPersonages.end(); iteratorPersonagem++) {
		vector<Ataque*> vetAtaque = (*iteratorPersonagem)->listAttack;
		for(itAtaque = vetAtaque.begin(); itAtaque < vetAtaque.end(); itAtaque++ ){
			if(!strcmp((*itAtaque)->nome.c_str(),nomeAtaque.c_str())){
				ataqueSelecionado = (*itAtaque);
				vector<Animation*> vetAnimacao = (*iteratorPersonagem)->listAnimacoes;
				for(itAnimacao = vetAnimacao.begin(); itAnimacao < vetAnimacao.end(); itAnimacao++){
					if(!strcmp((*itAnimacao)->name.c_str(),nomeAtaque.c_str())){
						animacaoSelecionada = (*itAnimacao);
						break;
					}
				}
			}
		}
	}
}*/

//versao com map
void StateBatalha::getAtaqueSelecionado(string nomeAtaque) {
	vector<PersonagemAtivo*>::iterator iteratorPersonagem;
	map<string,Ataque*>::iterator mapAtaque;
	for (iteratorPersonagem = grupoMocinhos->vetorPersonages.begin(); iteratorPersonagem < grupoMocinhos->vetorPersonages.end(); iteratorPersonagem++) {
		mapAtaque = (*iteratorPersonagem)->listAttack.find(nomeAtaque);
		if(mapAtaque != (*iteratorPersonagem)->listAttack.end()) {
			//printf("nome ataque: %s\n",nomeAtaque.c_str());
			ataqueSelecionado = (*mapAtaque).second;
			animacaoSelecionada = (*iteratorPersonagem)->listAnimacoes[nomeAtaque];
			personagemSelecionado = (*iteratorPersonagem);
			//printf("Do personagem: %s\n",(*iteratorPersonagem)->sfxAtaque->fileName.c_str());
			sfxAtaque = animacaoSelecionada->sfxAnimation;
			(*iteratorPersonagem)->setCurrentAnimation(nomeAtaque);
			break;
		}
	}
}

#endif /* BATALHA_CPP_ */
