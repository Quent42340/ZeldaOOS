/*
 * =====================================================================================
 *
 *       Filename:  TilesInfos.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 17:25:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "TilesInfos.hpp"

u8 tilesInfo[TILE_NB][4] = {
	// Tile 0: Passable
	{0, 0,
	 0, 0},
	
	// Tile 1: Non passable
	{1, 1,
	 1, 1},
	
	// Tile 2: Change map
	{2, 2,
	 2, 2},
	
	// Tile 3: Half bottom passable
	{1, 1,
	 0, 0},
	
	// Tile 4: Half top passable
	{0, 0,
	 1, 1},
	
	// Tile 5: Half right passable
	{1, 0,
	 1, 0},
	
	// Tile 6; Half left passable
	{0, 1,
	 0, 1},
	
	// Tile 7: Half bottom non passable / top change map
	{2, 2,
	 1, 1},
	
	// Tile 8: Half top non passable / bottom change map
	{1, 1,
	 2, 2},
	
	// Tile 9: Half right non passable / left change map
	{2, 1,
	 2, 1},
	
	// Tile 10; Half left non passable / right change map
	{1, 2,
	 1, 2},
	
	// Tile 11: Slowing tile
	{0, 0,
	 0, 0},
	
	// Tile 12: Low grass tile
	{0, 0,
	 0, 0},
	
	// Tile 13: Low water tile
	{0, 0,
	 0, 0},
	
	// Tile 14: Grass tile
	{1, 1,
	 1, 1}
};

