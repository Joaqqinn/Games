#include "inocente.h"

inocente::inocente(Vector2f posicion) {

	reloj1 = new Clock;
	tiempo1 = new Time;
	*tiempo1 = reloj1->getElapsedTime();

	txt_inocent.loadFromFile("inocente.png");
	spr_inocent.setTexture(txt_inocent);
	spr_inocent.setScale(0.12, 0.12);
	spr_inocent.setPosition(posicion);
}

Sprite inocente::get_sprite() {

	return spr_inocent;
}

float inocente::get_seconds() {

	*tiempo1 = reloj1->getElapsedTime();

	return tiempo1->asSeconds();
}