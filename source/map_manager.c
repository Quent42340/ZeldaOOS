/*
	* =====================================================================================
	*
	*       Filename:  map_manager.c
	*
	*    Description:  A simple manager for map system
	*
	*        Version:  1.0
	*        Created:  19/01/2014 21:11:44
	*       Revision:  none
	*       Compiler:  gcc
	*
	*         Author:  Quentin BAZIN, <quent42340@gmail.com>
	*        Company:  Deloptia
	*
	* =====================================================================================
	*/
#include <stdio.h>
#include <nds.h>
#include "tileset.h"
#include "map.h"
#include "map_manager.h"

#include "plain.h"
#include "indoor.h"
#include "underground.h"

uint8_t g_area_sizes[AREA_NB];
t_tileset **g_tilesets;
t_map ***g_maps;
t_map *g_current_map;

uint8_t g_plain_info[256] ={
 0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
 1,1,1,1,1,1,1,1,0,0,0,0,4,0,1,1,
 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,11,1,
 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
 1,1,1,1,1,1,1,1,1,1,11,6,1,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,1,
 8,9,10,7,12,13,13,1,14,15,1,16,17,0,18,1
};

uint8_t g_indoor_info[256] = {
 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
 1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,
 1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,
 1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
 1,1,1,1,1,1,1,1,1,1,0,11,11,1,1,0,
 1,1,1,1,1,1,1,1,1,1,0,11,11,0,0,0,
 1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,
 1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,1,
 1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 8,9,10,7,0,0,1,12,15,15,11,15,0,0,0,0
};

uint8_t g_underground_info[256] = {
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,11,0,11,11,0,0,0,0,0,0,0,0,0,0,
 8,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0
};

uint8_t g_non_passable_tiles[13] = {
 1,3,4,5,6,8,9,10,12,16,17,18,0
};

uint8_t g_change_map_tiles[3] = {
	11,15,0
};

void map_manager_load_tilesets()
 {
  g_tilesets = (t_tileset **)malloc(TILESET_NB * sizeof(t_tileset *));
		
		g_tilesets[0] = tileset_new(g_plain_info, 16, plainTiles, plainTilesLen, plainPal, plainPalLen);
		g_tilesets[1] = tileset_new(g_indoor_info, 16, indoorTiles, indoorTilesLen, indoorPal, indoorPalLen);
		g_tilesets[2] = tileset_new(g_underground_info, 16, undergroundTiles, undergroundTilesLen, undergroundPal, undergroundPalLen);
	}

void map_manager_load_maps()
 {
		g_area_sizes[0] = 3;
		g_area_sizes[1] = 2;
		g_area_sizes[2] = 2;
		
  g_maps = (t_map ***)malloc(AREA_NB * sizeof(t_map **));
		
		g_maps[0] = (t_map **)malloc(g_area_sizes[0] * g_area_sizes[0] * sizeof(t_map *));
		
		g_maps[0][0] = map_new(g_tilesets[0], "/maps/a1.map", 16, 12, 0, 0, 0);
		g_maps[0][1] = map_new(g_tilesets[0], "/maps/a2.map", 16, 12, 0, 1, 0);
		g_maps[0][2] = map_new(g_tilesets[0], "/maps/a3.map", 16, 12, 0, 2, 0);
		g_maps[0][3] = map_new(g_tilesets[0], "/maps/b1.map", 16, 12, 0, 0, 1);
		g_maps[0][4] = map_new(g_tilesets[0], "/maps/b2.map", 16, 12, 0, 1, 1);
		g_maps[0][5] = map_new(g_tilesets[0], "/maps/b3.map", 16, 12, 0, 2, 1);
		g_maps[0][6] = map_new(g_tilesets[0], "/maps/c1.map", 16, 12, 0, 0, 2);
		g_maps[0][7] = map_new(g_tilesets[0], "/maps/c2.map", 16, 12, 0, 1, 2);
		g_maps[0][8] = map_new(g_tilesets[0], "/maps/c3.map", 16, 12, 0, 2, 2);
		
		g_maps[1] = (t_map **)malloc(g_area_sizes[1] * g_area_sizes[1] * sizeof(t_map *));
		
		g_maps[1][0] = map_new(g_tilesets[1], "/maps/ina1.map", 16, 12, 1, 0, 0);
		g_maps[1][1] = map_new(g_tilesets[1], "/maps/ina2.map", 16, 12, 1, 1, 0);
		g_maps[1][2] = NULL;
		g_maps[1][3] = NULL;
		
		g_maps[2] = (t_map **)malloc(g_area_sizes[2] * g_area_sizes[2] * sizeof(t_map *));
		
		g_maps[2][0] = map_new(g_tilesets[2], "/maps/ca1a1.map", 16, 12, 2, 0, 0);
		g_maps[2][1] = map_new(g_tilesets[2], "/maps/ca1a2.map", 16, 12, 2, 1, 0);
		g_maps[2][2] = NULL;
		g_maps[2][3] = map_new(g_tilesets[2], "/maps/ca1b2.map", 16, 12, 2, 1, 1);
	}

void map_manager_load_all()
 {
		map_manager_load_tilesets();
		map_manager_load_maps();
		
		g_current_map = g_maps[0][0];
	}

void      map_manager_free_all()
 {
		uint8_t i, j;
		
		if(g_tilesets)
		 {
				for(i = 0 ; i < TILESET_NB ; i++)
				 {
						tileset_free(g_tilesets[i]);
					}
				free(g_tilesets);
			}
		
		if(g_maps)
		 {
				for(i = 0 ; i < AREA_NB ; i++)
				 {
						if(g_maps[i])
						 {
								for(j = 0 ; j < g_area_sizes[i] ; j++)
								 {
										map_free(g_maps[i][j]);
									}
							}
					}
			}
	}

void map_manager_init_transition()
 {
		dmaFillWords(0xFFFFFFFF, bgGetGfxPtr(g_transition_bg) + 32, 64);
		dmaFillWords(0x00010001, bgGetMapPtr(g_transition_bg), 32 * 24 * 2);
	}

void      map_manager_transition()
 {
		uint8_t x, y;
		
		for(x = 0 ; x < 16 ; x++)
	  {
				swiWaitForVBlank();
				for(y = 0 ; y < 24 ; y++)
				 {
						((uint16_t *)bgGetMapPtr(g_transition_bg))[(15 - x) + (y << 5)] = 0;
						((uint16_t *)bgGetMapPtr(g_transition_bg))[(16 + x) + (y << 5)] = 0;
					}
			}
	}

bool in_table(uint8_t t[], uint8_t n)
 {
		uint8_t i = 0;
		
		while(t[i])
		 {
				if(t[i] == n)
				 {
						return true;
					}
				i++;
			}
		
		return false;
	}

bool in_tiles(int16_t tile_x, int16_t tile_y, uint8_t tiles[])
 {
		return in_table(tiles, g_current_map->tileset->info[map_get_tile(g_current_map, tile_x, tile_y)]);
	}

bool passable(int16_t x, int16_t y)
 {
		return !in_tiles(x / 16, y / 16, g_non_passable_tiles);
	}

