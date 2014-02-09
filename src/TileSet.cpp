/*
 * TileSet.cpp
 *
 *  Created on: May 11, 2013
 *      Author: LOUISE
 */
#include "../headers/TileSet.h"



TileSet::TileSet(string filePath , int columns, int lines ){
	tileSet= new Sprite(filePath);
	this->tileWidth=(tileSet->getWidth())/columns;
	this->tileHeight=(tileSet->getHeight())/lines;

	this->useSingleFile=true;
	this->columns=columns;
	this->lines=lines;
	this->destRect=NULL;
	vTiles=NULL;
}
TileSet::TileSet(int tileWight, int tileHeight, string filePath ){
		tileSet = new Sprite(filePath);
		this->tileHeight=tileHeight;
		this->tileWidth=tileWight;
		this->useSingleFile=true;
		this->columns=(tileSet->getWidth()/tileWight);
		this->lines=(tileSet->getHeight()/tileHeight);
		this->destRect=NULL;
		vTiles=NULL;
		//printf("widht: %d height: %d column: %d line: %d\n",tileWight, tileHeight, columns, lines);

}

TileSet::TileSet(int tileWight, int tileHeight){
	this->tileHeight=tileHeight;
	this->tileWidth=tileWight;
	this->tileSet= 0;
	this->useSingleFile=false;
	this->columns=0;
	this->lines=0;
	this->destRect=NULL;
	vTiles=new std::vector<Sprite*>();
}

TileSet::~TileSet(){

 }

void TileSet::addTile(string filePath){
	if(!usingSingleFile()){
		vTiles->push_back(new Sprite(filePath));
	}else{
		cout<<"(TileSet::addTile)Erro:TileSet esta configurado para usar um unico Tile."<<endl;
	}
}

void TileSet::render(int index, float posX, float posY){
	if(usingSingleFile()){

		int columnsAux, linesAux;
		columnsAux = (index%columns)*tileWidth ;
		linesAux = (index/columns*tileHeight);
		//printf("colum %d line %d\n columns: %d lines: %d -- tw %d th %d\n",columnsAux,linesAux,columns, lines, tileWidth, tileHeight);
		tileSet->clip(columnsAux, linesAux,tileWidth , tileWidth);
		tileSet->render(posX,posY);


	}else{

		vTiles->operator [](index)->Sprite::render(posX,posY);

	}

}

bool TileSet::usingSingleFile(){
	if(this->tileSet!=NULL){
		return true;
	}else{
		return false;
	}
}

int TileSet::getTileWidth(){
	return this->tileWidth;
}

int TileSet::getTileHeight(){
	return this->tileHeight;
}


