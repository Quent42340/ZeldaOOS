#include "icon.h"

Icon::Icon(int i, u8* s_gfx) : qSprite(i, SpriteSize_32x32, &oamSub) {
	
}

Icon::~Icon() {
}
