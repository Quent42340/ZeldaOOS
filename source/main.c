/*
 * =====================================================================================
 *
 *   Program name:  ZeldaOracle
 *       Filename:  main.c
 *
 *    Description:  ZeldaOracle is a 2D Zelda: Oracle
 *                  of-like engine written in pure C
 *                  with the libnds
 *
 *        Version:  1.0
 *        Created:  06/01/2014 20:31:35
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
#include <fat.h>
#include <filesystem.h>
#include "libs5.h"
#include "timer.h"
#include "animation.h"
#include "sprite.h"
#include "tileset.h"
#include "map.h"
#include "character.h"
#include "player.h"

#include "plain.h"

void video_init()
 {
  videoSetMode(MODE_5_2D);
  videoSetModeSub(MODE_5_2D);
  
  vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
  vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
  vramSetBankC(VRAM_C_SUB_BG_0x06200000);
  vramSetBankD(VRAM_D_SUB_SPRITE);
  
  sprite_system_init();
  
  map_system_init();
 }

int main(void)
 {
  defaultExceptionHandler();
  
  printf("NitroFS loading...\n");
	 
  if(!nitroFSInit())
   {
    printf("FATAL ERROR: Bad nitroFS init\n");
    while(1)
     {
      swiWaitForVBlank();
     }
   }
  
  printf("NitroFS loaded!\n");
  
  consoleClear();
  
  timer_system_init();
  
	 video_init();
  
  consoleDemoInit();
  
  t_character *link = player_new();
  
  t_tileset *plain = tileset_new(NULL, plainTiles, plainTilesLen, plainPal, plainPalLen);
  
  t_map *a1 = map_new(plain, "/maps/a1.map", 16, 12, 0, 0, 0);
  
  map_load(a1);
  
  while(1)
   {
    scanKeys();
    
    character_move(link);
    
    character_render(link);
    
	 	 swiWaitForVBlank();
	  }
  
  map_free(a1);
  
  tileset_free(plain);
  
  character_free(link);
 }

