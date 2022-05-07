#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class inocente {

private:
	Texture txt_inocent;
	Sprite spr_inocent;
	Clock* reloj1;
	Time* tiempo1;

public:
	inocente(Vector2f posicion);
	Sprite get_sprite();
	float get_seconds();
};