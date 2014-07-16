/*
 * =====================================================================================
 *
 *       Filename:  MapManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 14:21:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <math.h>

#include <nds.h>

#include "TilesInfos.hpp"
#include "TilesetsInfos.hpp"
#include "MapManager.hpp"

#include "plain.h"

u16 MapManager::mapBg;

std::vector<Tileset*> MapManager::tilesets;
std::vector<std::vector<Map*>> MapManager::maps;

Map *MapManager::currentMap = NULL;

void MapManager::init() {
	mapBg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
	
	bgSetPriority(mapBg, 1);
	
	initTilesets();
	
	initMaps();
	
	currentMap = maps[0][0];
}

void MapManager::free() {
	while(maps.size() != 0) {
		while(maps.back().size() != 0) {
			delete maps.back().back();
			maps.back().pop_back();
		}
		
		maps.pop_back();
	}
}

void MapManager::initTilesets() {
	tilesets.push_back(new Tileset(TilesetsInfos::plainInfo, plainTiles, plainTilesLen, plainPal, plainPalLen));
}

void MapManager::initMaps() {
	std::vector<Map*> overworld;
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/a1.map", 16, 12, 0, 0, 0));
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/a2.map", 16, 12, 0, 1, 0));
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/a3.map", 16, 12, 0, 2, 0));
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/b1.map", 16, 12, 0, 0, 1));
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/b2.map", 16, 12, 0, 1, 1));
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/b3.map", 16, 12, 0, 2, 1));
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/c1.map", 16, 12, 0, 0, 2));
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/c2.map", 16, 12, 0, 1, 2));
	overworld.push_back(new Map(tilesets[0], "nitro:/maps/c3.map", 16, 12, 0, 2, 2));
	
	maps.push_back(overworld);
}

void MapManager::scrollMaps(s8 dx, s8 dy) {
	Map *nextMap = maps[currentMap->zone()][currentMap->x() + dx + (currentMap->y() + dy) * sqrt(maps[currentMap->zone()].size())];
	
	if(dx != 0) {
		for(u8 i = 0 ; i < 32 ; i++) {
			for(u8 j = 0 ; j < 8 * abs(dx) ; j++) {
				if(!(Map::scrollX & 15)) {
					for(u16 k = Map::scrollY / 16 ; k < Map::scrollY / 16 + 12 ; k++) {
						if(dx > 0) {
							nextMap->loadTile(Map::scrollX / 16, k, 16);
						} else {
							nextMap->loadTile(Map::scrollX / 16 - 1, k);
						}
					}
				}
				
				Map::scrollX += dx;
			}
			
			bgSetScroll(mapBg, Map::scrollX, Map::scrollY);
			bgUpdate();
			
			swiWaitForVBlank();
		}
	}
	
	if(dy != 0) {
		for(u8 i = 0 ; i < 24 ; i++) {
			for(u8 j = 0 ; j < 8 * abs(dy) ; j++) {
				if(!(Map::scrollY & 15)) {
					for(u16 k = Map::scrollX/ 16 ; k < Map::scrollX / 16 + 16 ; k++) {
						if(dy > 0) {
							nextMap->loadTile(k, Map::scrollY / 16, 0, 12);
						} else {
							nextMap->loadTile(k, Map::scrollY / 16 - 1);
						}
					}
				}
				
				Map::scrollY += dy;
			}
			
			bgSetScroll(mapBg, Map::scrollX, Map::scrollY);
			bgUpdate();
			
			swiWaitForVBlank();
		}
	}
	
	currentMap = nextMap;
}

bool inTable(u8 t[], u8 n) {
	while(*t) {
		if(*t == n) {
			return true;
		}
		t++;
	}
	return false;
}

bool inTiles(s16 tileX, s16 tileY, u8 tiles[]) {
	return true;
}

bool passable(s16 x, s16 y) {
	u8 tile = MapManager::currentMap->tileset()->info[MapManager::currentMap->getTile(x >> 4, y >> 4)];
	// TODO: Understand why I wrote that
	if(tilesInfo[tile][((x - ((x >> 4) << 4)) >> 3) + ((y - ((y >> 4) << 4)) >> 3) * 2] == 1) {
		return false;
	} else {
		return true;
	}
}

