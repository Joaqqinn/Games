#include "enemigos.h"


enemigos::enemigos(Vector2f posicion) {

	int numero_enemigos;

	numero_enemigos = rand() % 5 + 1;

	reloj1 = new Clock;
	tiempo1 = new Time;
	*tiempo1 = reloj1->getElapsedTime();

	String path;
	path = "enemigo" + to_string(numero_enemigos) + ".png";
	txt_enemigos.loadFromFile(path);
	spr_enemigos.setTexture(txt_enemigos);
	spr_enemigos.setScale(0.20, 0.20);
	spr_enemigos.setPosition(posicion);

}

Sprite enemigos::get_sprite() {

	return spr_enemigos;
}

float enemigos::get_seconds() {

	*tiempo1 = reloj1->getElapsedTime();

	return tiempo1->asSeconds();
}