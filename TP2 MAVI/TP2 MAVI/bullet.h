#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class bullet {

private:
	Texture* txt_bullet;
	Sprite* spr_bullet;
	Vector2f posicion = { 640.0, 512.0 };
	Vector2f velocidad;

public:
	bullet(Vector2f posicion, float angulo);
	~bullet();
	Sprite get_spr() { return *spr_bullet; }
	void update(); //actualizamos la posicion
	void set_velocidad(Vector2f vel) { velocidad = vel; } // obtenemos la velocidad para el impulso
	void set_translation(Vector2f translation); //pasa la velocidad para modificar la posicion
};