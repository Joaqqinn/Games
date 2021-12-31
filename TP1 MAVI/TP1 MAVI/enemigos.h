#pragma once
#include "SFML/Graphics.hpp"
#include <stdlib.h>

using namespace sf;
using namespace std;


class enemigos {

private:
	Texture txt_enemigos;
	Sprite spr_enemigos;
	Clock* reloj1;
	Time* tiempo1;

public:
	enemigos(Vector2f posicion);
	Sprite get_sprite();
	float get_seconds();
};