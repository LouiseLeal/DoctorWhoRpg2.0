/*
 * TileMap.cpp
 *
 *  Created on: May 11, 2013
 *      Author: LOUISE
 */

#include "../headers/TileMap.h"

using namespace std;
TileMap::TileMap(int width, int height, int tileSize, int layer,
		TileSet* tilesetMap) {

	this->mapWidth = width;
	this->mapHeight = height;
	this->mapLayer = layer;
	this->tilesetMap = tilesetMap;

	tileMap.assign(mapWidth,
			std::vector<std::vector<int> >(mapHeight,
					std::vector<int>(mapLayer, -1)));

	for (unsigned int i = 0; i < tileMap.size(); ++i) {
		for (unsigned int j = 0; j < tileMap[0].size(); ++j) {
			for (unsigned int z = 0; z < tileMap[0][0].size(); ++z) {
				tileMap[i][j][z] = -1;
			}
		}
	}
}
TileMap::TileMap(std::string mapa, TileSet* tileset) {
	this->mapHeight = tileset->tileWidth;
	this->mapLayer = 0;
	this->mapWidth = tileset->tileHeight;
	this->tilesetMap = tileset;
	load(mapa);
}

void TileMap::load(string mapPath) {
	FILE *map;
	map = fopen(mapPath.c_str(), "r");
	int aux, ly, c, l;

	if (map) {
		fscanf(map, "%d,", &c);
		fscanf(map, "%d,", &l);
		fscanf(map, "%d,", &ly);
		columns = c;
		lines = l;
		mapLayer = ly;
		//printf("Coluna: %d linha: %d layer: %d\n",c,l,ly);
		tileMap.assign(c,
				std::vector<std::vector<int> >(l, std::vector<int>(ly, -1)));
		for (int z = 0; z < ly; z++) {
			for (int y = 0; y < l; y++) {
				for (int x = 0; x < c; x++) {
					fscanf(map, "%d,", &aux);
					//printf("item %d\t",aux);
					aux--;
					tileMap[x][y][z] = aux;
				}
				//printf("\n");
			}
		}
	} else {
		cout << "(TileMap::load)Erro ao abrir aquivo do map";
	}
	fclose(map);
}
TileMap::~TileMap() {

}

void TileMap::setTileSet(TileSet* tilesetMap) {
	this->tilesetMap = tilesetMap;
}

int& TileMap::at(int x, int y, int z) {

	if(x < 0 || x > columns || y < 0 || y > lines){
		int *valor = (int*)malloc(sizeof(int));
		*valor = 500;
		return *valor;
	}

	return tileMap[x][y][z];
}

void TileMap::render() {
	int index;
	for (unsigned int z = 0; z < tileMap[0][0].size(); z++) {;
		for (unsigned int i = 0; i < tileMap.size(); ++i) {
			for (unsigned int j = 0; j < tileMap[0].size(); ++j) {
				if (tileMap[i][j][z] >= 0) {
					index = tileMap[i][j][z];
					int posx, posy;
					posx = (tilesetMap->getTileWidth() * i);
					posy = (tilesetMap->getTileHeight() * j);
					/// Cofiguração para simular parellax
					//float camAuxX=Camera::cameraX*((z+1)*(0.1));
					//float camAuxY=Camera::cameraY*((z+1)*(0.1));
					//printf("Index: %d\n",index);
					tilesetMap->render(index, posx - Camera::cameraX ,	posy - Camera::cameraY );
				}
			}

		}
	}

}



void TileMap::rederLayer(int layer) {
	int index;
	for (unsigned int i = 0; i < tileMap.size(); ++i) {
		for (unsigned int j = 0; j < tileMap[0].size(); ++j) {
			if (tileMap[i][j][layer] >= 0) {
				index = tileMap[i][j][layer];
				int posx, posy;
				posx = (tilesetMap->getTileWidth() * i);
				posy = (tilesetMap->getTileHeight() * j);
				tilesetMap->render(index, posx - Camera::cameraX ,	posy - Camera::cameraY );
			}
		}
	}
}

int TileMap::getWidth() {
	return this->mapWidth;
}

int TileMap::getHeight() {
	return this->mapHeight;
}

int TileMap::getLayer() {
	return this->mapLayer;
}
