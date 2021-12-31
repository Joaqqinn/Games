#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class ship {

private:
	Texture* txt_ship;
	Sprite* spr_ship;
	Vector2f posicion = { 640.0, 512.0 }; //centramos el sprite
	Vector2f velocidad;
	
public:
	ship();
	~ship();
	Sprite get_spr() { return *spr_ship; }
	Vector2f get_angle(float velocidad1); //obtenemos el angulo de movimiento en base a la rotation del sprite
	void update(); //actualizamos la posicion
	void set_velocidad(Vector2f vel) { velocidad = vel; } // obtenemos la velocidad para el impulso
	void set_translation(Vector2f translation); //pasa la velocidad para modificar la posicion
	void set_rotation(float rotation); //variamos la rotacion en base a las teclas
	float gradosaradianes(float grados) { return grados * 3.14 / 180; } //convertimos los datos para usar en get_angle
	float vel = 0;

};