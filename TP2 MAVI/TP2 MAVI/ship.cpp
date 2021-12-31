#include "ship.h"
#include <iostream>

using namespace std;

ship::ship() {
	// NAVE JUGADOR
	txt_ship = new Texture();
	txt_ship->loadFromFile("Sprites/nave.png");
	spr_ship = new Sprite(*txt_ship);
	spr_ship->setScale(0.15, 0.15);
	spr_ship->setOrigin(spr_ship->getTexture()->getSize().x / 2.f, spr_ship->getTexture()->getSize().y / 2.f);
}

ship::~ship() {}

void ship::set_rotation(float rotation) {

	spr_ship->setRotation(spr_ship->getRotation() + rotation);

}

void ship::update() {

	set_translation(velocidad);

}

void ship::set_translation(Vector2f translation) {

	posicion += translation;
	spr_ship->setPosition(posicion);
}

Vector2f ship::get_angle(float velocidad1) {

	vel = velocidad1;

	Vector2f angulo;
	
	angulo.x = (vel * cos(gradosaradianes(spr_ship->getRotation())));
	angulo.y = (vel * sin(gradosaradianes(spr_ship->getRotation())));
	
	return angulo;

}