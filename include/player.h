#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
#include "sprite3D.h"

#include "link_png.h"

enum PlayerDirection {
	DIR_UP = 4,
	DIR_DOWN = 1,
	DIR_LEFT = 3,
	DIR_RIGHT = 2
};

class Player : public Sprite3D {
	public:
		// Construct & Destruct
		Player();
		~Player();
		
		// Update functions
		void move();
		void draw();
		
	private:
		// Player lifes
		int s_lifes;
		
		// Player movement vectors
		s8 s_vx;
		s8 s_vy;
		
		// Direction
		PlayerDirection s_direction;
};

#endif // PLAYER_H
