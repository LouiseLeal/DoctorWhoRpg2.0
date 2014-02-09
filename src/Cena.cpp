/*
 * Cena.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Carol
 */

#include "../headers/Cena.h"

Cena::Cena(string filePath) {
	XMLDocument frameDoc;
	frameDoc.LoadFile(filePath.c_str());
	if(frameDoc.ErrorID() != 0){
		printf("Erro ao tentar abrir o xml %s. ErrodId: %d\n",filePath.c_str(),frameDoc.ErrorID());
		exit(1);
	}

	//frames
	XMLNode *framesList = frameDoc.RootElement();
	XMLNode *childFrame;
	for(childFrame = framesList->FirstChildElement("dadosframe"); childFrame; childFrame = childFrame->NextSibling()){
		//printf("lendo um dados frame\n");
		FRAME frameAux;
		childFrame->FirstChildElement("frame")->QueryIntText(&frameAux.frame);
		childFrame->FirstChildElement("tempo")->QueryIntText(&frameAux.tempo);

		XMLNode *jackie = childFrame->FirstChildElement("jackie");
		XMLNode *rose = childFrame->FirstChildElement("rose");
		XMLNode *doctor = childFrame->FirstChildElement("doctor");
		XMLNode *fantasma = childFrame->FirstChildElement("fantasma");

		PERSONAGEM jackieDados;
		PERSONAGEM roseDados;
		PERSONAGEM doctorDados;
		PERSONAGEM fantasmaDados;

		jackie->FirstChildElement("posx")->QueryIntText(&jackieDados.posX);
		jackie->FirstChildElement("posy")->QueryIntText(&jackieDados.posY);
		jackieDados.direcao = jackie->FirstChildElement("direcao")->GetText();
		jackie->FirstChildElement("fala")->QueryIntText(&jackieDados.fala);
		if(jackieDados.fala) {
			jackieDados.conteudo = jackie->FirstChildElement("conteudo")->GetText();
			jackieDados.expressao = jackie->FirstChildElement("expressao")->GetText();
		}
		//printf("li jackie\n");

		rose->FirstChildElement("posx")->QueryIntText(&roseDados.posX);
		rose->FirstChildElement("posy")->QueryIntText(&roseDados.posY);
		roseDados.direcao = rose->FirstChildElement("direcao")->GetText();
		rose->FirstChildElement("fala")->QueryIntText(&roseDados.fala);
		if(roseDados.fala) {
			roseDados.conteudo = rose->FirstChildElement("conteudo")->GetText();
			roseDados.expressao = rose->FirstChildElement("expressao")->GetText();
		}

		//printf("li rose\n");

		doctor->FirstChildElement("posx")->QueryIntText(&doctorDados.posX);
		doctor->FirstChildElement("posy")->QueryIntText(&doctorDados.posY);
		doctorDados.direcao = doctor->FirstChildElement("direcao")->GetText();
		doctor->FirstChildElement("fala")->QueryIntText(&doctorDados.fala);
		if(doctorDados.fala) {
			doctorDados.conteudo = doctor->FirstChildElement("conteudo")->GetText();
			doctorDados.expressao = doctor->FirstChildElement("expressao")->GetText();
		}

		//printf("li doctor\n");

		fantasma->FirstChildElement("posx")->QueryIntText(&fantasmaDados.posX);
		fantasma->FirstChildElement("posy")->QueryIntText(&fantasmaDados.posY);
		fantasmaDados.direcao = fantasma->FirstChildElement("direcao")->GetText();
		fantasma->FirstChildElement("fala")->QueryIntText(&fantasmaDados.fala);
		if(fantasmaDados.fala) {
			fantasmaDados.conteudo = fantasma->FirstChildElement("conteudo")->GetText();
			fantasmaDados.expressao = fantasma->FirstChildElement("expressao")->GetText();
		}

		frameAux.vetPersonagem.push_back(doctorDados);
		frameAux.vetPersonagem.push_back(roseDados);
		frameAux.vetPersonagem.push_back(jackieDados);

		frameAux.fantasma = fantasmaDados;

		vetFrames.push_back(frameAux);
	}

}


