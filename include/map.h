/*
 * =====================================================================================
 *
 *       Filename:  map.h
 *
 *    Description:  Map system with scrolling
 *
 *        Version:  1.0
 *        Created:  14/01/2014 22:05:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef MAP_H_
#define MAP_H_

struct s_tileset
 {
  uint8_t *info;
  
  const uint32_t *tiles;
  uint32_t tiles_length;
  
  const uint16_t *palette;
  uint32_t pal_length;
 };

typedef struct s_tileset s_tileset;

s_tileset *tileset_new(uint8_t *info, const uint32_t *tiles, uint32_t tiles_length, const uint16_t *palette, uint32_t pal_length);
void tileset_free(s_tileset *tileset);

struct s_map
 {
  uint16_t id;
  
  s_tileset *tileset;
  
  uint16_t width;
  uint16_t height;
  
  uint16_t area;
  uint8_t x;
  uint8_t y;
  
  uint16_t *data;
 };

typedef struct s_map s_map;

void map_system_init();

s_map *map_new(s_tileset *tileset, char *filename, uint16_t width, uint16_t height, uint16_t area, uint8_t x, uint8_t y);
void map_free(s_map *map);

uint16_t map_bg_pos(uint16_t x, uint16_t y);

void map_load(s_map *map);
void map_load_tile(s_map *map, uint16_t x, uint16_t y);

#endif // MAP_H_
