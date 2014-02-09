/*
 * Batalha.h
 *
 *  Created on: May 30, 2013
 *      Author: Carol
 */

#ifndef STATEBATALHA_H_
#define STATEBATALHA_H_

// #include "Types.h"
// #include "Ataque.h"
// #include "Item.h"
// #include "Audio.h"
// #include "TileMap.h"
// #include "TileSet.h"
// #include "InputManager.h"
// #include "TextOpcoes.h"
// #include "CaixaTexto.h"

#include "GrupoCenario.h"
#include "GrupoViloes.h"
#include "State.h"
#include "Tempo.h"


class StateBatalha : public State{
public:
	//StateBatalha(GrupoCenario *vGrupoMocinhos);
	//~StateBatalha();

	void setGrupoMocinhos(GrupoCenario *vGrupoMocinhos);

	//herdados
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();

	//pega a lista de ataques de acordo com o grupo e tipo de ataque
	vector<string> getListaAtaque(AID_TYPES tipoAtaque);
	vector<string> getListaTiposAtaques();
	Ataque *mostraListaAtaque(vector<Ataque*> listaAtaques);
	AID_TYPES mostraListaTiposAtaque(vector<bool> aid_types);
	//TODO
	vector<string> getListaItem();

	//aplicacao dos ataques
	//aplicacao de danos
	//play animacoes

	void getAtaqueSelecionado(string);
	void ataqueMocinhos(Ataque *ataque);
	void ataqueViloes(Ataque *ataque);
	void aplicaDano(int danoTotal, ATACANTE atacante); //atacado: 0 para mocinhos, 1 para viloes

	//uso de item
	void usaItem(Item item);
	void processEvents();



private:
	GrupoViloes *grupoViloes;
	GrupoCenario *grupoMocinhos;
	GrupoBatalha *grupoBatalhaMocinhos;
	GrupoBatalha *grupoBatalhaViloes;

	int defesaMocinhos;
	int defesaViloes;

	bool FIM_BATALHA;
	bool GAME_OVER;

	bool ATAQUE_MOCINHOS;
	bool ATAQUE_VILOES;
	bool PRIMEIRO_LOAD;
	bool ESPERA_INPUT;
	int estado_mocinhos;
	int estado_viloes;
	int danoAplicado;
	int porcentagemExperiencia;

	int opcaoEscolhida;

	vector<string> listaItens;
	vector<string> listaTiposAtaques;
	vector<string> listaAtaques;

	Animation * animacaoSelecionada;

	PersonagemAtivo *personagemSelecionado;

	Item *itemSelecionado;

	Ataque *ataqueSelecionado;
	AID_TYPES tipoEscolhido;

	TextOpcoes * textoSelecionado;
	TextOpcoes * textoTipoAcao;
	TextOpcoes * textoAtaque;
	TextOpcoes * textoItem;

	char escolhido;

	Sprite *background;
	Sprite *spriteLevelUp;

	//teste caixa texto
	Sprite *spCaixaTexto;
	int tbPosX;
	int tbPosY;

	//texto de dano
	Text *txDano;
	Tempo timerRender;
	Tempo timerLevelUp;
	int waitTimer;

	int vinteLifeViloes;

	int retornoFimBatalha;

	Sprite *bgVitoria;
	Sprite *spriteVictory;

	Audio *sfxAtaque;
	Audio *sfxBackgroundMusic;
	Audio *sfxVictory;
	Audio *sfxBlip;
	Audio *sfxLevaDano;
	Audio *sfxItem;

	Text *txtExperiencia;
	Text *txtPassouLevel;
	bool ganhouItem;
	bool PASSOU_LEVEL;
	bool escolheuItem;

	TileMap *tileMap;
	TileSet *tileSet;

	int ESTADO_ANIMACAO;

	//hud do life
	Sprite *lifeVerde;
	Sprite *lifeAmarelo;
	Sprite *lifeVermelho;
	Sprite *lifeBar;

	int barMocinhosX;
	int barMocinhosY;

	int barViloesX;
	int barViloesY;

	int vidaInicialMocinhos;
	int vidaInicialViloes;

	int lifeBarMocinhos;
	int lifeBarViloes;

	int probDeixarBatalha;

	Text *txtNomeAtaque;
	Text *txtTipoAtaque;

};


#endif /* BATALHA_H_ */
