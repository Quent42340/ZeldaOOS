/*---------------------------------------------------------------------------------

	Eleandra
	Copyright (C) 2012 Quentin BAZIN quent42340@gmail.com
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <sys/stat.h>
#include "timer.h"
#include "sprites.h"
#include "map.h"
#include "mapManager.h"
#include "player.h"
#include "game.h"

int Map::nbMaps = 0;

s16 Map::scrollX = 0;
s16 Map::scrollY = 0;

Map::Map(Tileset *tileset, char *filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight, u8 bg) {
	m_id = nbMaps;
	nbMaps++;
	
	m_mapY = m_id / WM_SIZE;
	m_mapX = m_id - m_mapY * WM_SIZE;
	
	m_tileset = tileset;
	m_filename = filename;
	m_width = width;
	m_height = height;
	m_tileWidth = tileWidth;
	m_tileHeight = tileHeight;
	
	// Make temporary table to get map file data
	u16* table = (u16*)malloc(m_width * m_height * sizeof(u16));
	
	// Load map from file
	struct stat file_status;
	if(stat(filename, &file_status) != 0){
		printf("Unable to load %s", m_filename);
	}
	int filesize = file_status.st_size;
	
	FILE* f = fopen(filename, "r");
	fread(table, 2, filesize, f);
	fclose(f);
	
	m_map = table;
	m_bg = bg;
}

Map::~Map() {
}

void Map::init() {
	dmaCopy(m_tileset->tiles, bgGetGfxPtr(m_bg), m_tileset->tilesLen);
	dmaCopy(m_tileset->palette, BG_PALETTE, m_tileset->paletteLen);
	
	u16 x, y;
	for(y = 0 ; y < 12 ; y++) {
		for(x = 0 ; x < 16 ; x++) {
			putTile(x, y, this, x, y);
		}
	}
}

u16 Map::screenPos(s16 x, s16 y) const {
	return ((x & 31) + ((x & 32) << 5) + ((y & 31) << 5) + ((y & 32) << 6));
}

void Map::putTile(s16 x, s16 y, const Map* map, s16 mapX, s16 mapY) {
	mapX &= 15;
	mapY %= 12;
	u16 *mapPtr = (u16*)bgGetMapPtr(m_bg);
	mapPtr[screenPos(x * 2, y * 2)] = map->map()[mapX + mapY * map->width()] * 4;
	mapPtr[screenPos(x * 2 + 1, y * 2)] = map->map()[mapX + mapY * map->width()] * 4 + 1;
	mapPtr[screenPos(x * 2, y * 2 + 1)] = map->map()[mapX + mapY * map->width()] * 4 + 2;
	mapPtr[screenPos(x * 2 + 1, y * 2 + 1)] = map->map()[mapX + mapY * map->width()] * 4 + 3;
}

void Map::scroll(s16 xx, s16 yy) {
	if(xx > 0) { // Scroll right
		m_nextMap = Game::maps[m_mapX + 1 + m_mapY * WM_SIZE]; // Next map to scroll on
		
		for(int i = 0 ; (i < xx) && (scrollX < m_width * WM_SIZE * 16 - 256) ; i++) {
			if(!(scrollX & 15)) {
				for(int j = scrollY / 16 ; j < scrollY / 16 + 12 ; j++) {
					putTile(scrollX / 16 + 16, j, m_nextMap, scrollX / 16, j);
				}
			}
			scrollX++; // Scroll the map
		}
		
		REG_BG0HOFS = scrollX & 1023; // Scroll the BG
	}
	else if(xx < 0) { // Scroll left
		m_nextMap = Game::maps[m_mapX - 1 + m_mapY * WM_SIZE]; // Next map to scroll on
		
		for(int i = 0 ; (i < -xx) && (scrollX > 0) ; i++) {
			if(!(scrollX & 15)) {
				for(int j = scrollY / 16 ; j < scrollY / 16 + 12 ; j++) {
					putTile(scrollX / 16 - 1, j, m_nextMap, scrollX / 16 - 1, j);
				}
			}
			scrollX--; // Scroll the map
		}
		
		REG_BG0HOFS = scrollX & 1023; // Scroll the BG
	}
	
	if(yy > 0) { // Scroll down
		m_nextMap = Game::maps[m_mapX + (m_mapY + 1) * WM_SIZE]; // Next map to scroll on
		
		for(int i = 0 ; (i < yy) && (scrollY < m_height * WM_SIZE * 16 - 192) ; i++) {
			if(!(scrollY & 15)) {
				for(int j = scrollX / 16 ; j < scrollX / 16 + 16 ; j++) {
					putTile(j, scrollY / 16 + 12, m_nextMap, j, scrollY / 16);
				}
			}
			scrollY++; // Scroll the map
		}
		
		REG_BG0VOFS = scrollY & 1023; // Scroll the BG
	}
	else if(yy < 0) { // Scroll up
		m_nextMap = Game::maps[m_mapX + (m_mapY - 1) * WM_SIZE]; // Next map to scroll on
		
		for(int i = 0 ; (i < -yy) && (scrollY > 0) ; i++) {
			if(!(scrollY & 15)) {
				for(int j = scrollX / 16 ; j < scrollX / 16 + 16 ; j++) {
					putTile(j, scrollY / 16 - 1, m_nextMap, j, scrollY / 16 - 1);
				}
			}
			scrollY--; // Scroll the map
		}
		
		REG_BG0VOFS = scrollY & 1023; // Scroll the BG
	}
}

void Map::setTile(s16 tileX, s16 tileY, u16 tile) {
	m_map[tileX + tileY * m_width] = tile;
}

u16 Map::getTile(s16 tileX, s16 tileY) {
	return m_map[tileX + tileY * m_width];
}

