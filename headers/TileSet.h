/*
 * TileSet.h
 *
 *  Created on: May 11, 2013
 *      Author: LOUISE
 */

#ifndef TILESET_H
#define TILESET_H



// #include<stdio.h>
// #include<stdlib.h>
// #include<SDL/SDL.h>
// #include<vector>
// #include<iostream>
// #include<time.h>
// #include"SDLBase.h"
#include"Sprite.h"

using namespace std;
using std::vector;

class TileSet{
public:
	/// Atributos
	int tileWidth , tileHeight;
	vector<Sprite*>*vTiles;
	int lines, columns;
	Sprite* tileSet;
	SDL_Rect* destRect;
	bool useSingleFile;

	///Métodos
	TileSet(int tileWight, int TileHeight, string filePath );
	TileSet(string filePath,int lines, int columns);
    TileSet(int tileWidth, int tileHeight);
    virtual ~TileSet();
	void addTile(string filePath);
	void render(int index, float posX, float posY);
	bool usingSingleFile();
	int getTileWidth();
	int getTileHeight();



};


#endif /* TILESET_H_ */
