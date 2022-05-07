#include "bullet.h"

bullet::bullet(Vector2f pos, float angulo) {

	posicion = pos;
	txt_bullet = new Texture();
	txt_bullet->loadFromFile("Sprites/bala.png");
	spr_bullet = new Sprite(*txt_bullet);
	spr_bullet->setOrigin(spr_bullet->getTexture()->getSize().x / 2.f, spr_bullet->getTexture()->getSize().y / 2.f);
	spr_bullet->setPosition(pos);
	spr_bullet->setRotation(angulo);
}

bullet::~bullet(){}

void bullet::update() {

	set_translation(velocidad);

}

void bullet::set_translation(Vector2f translation) {

	posicion += translation;
	spr_bullet->setPosition(posicion);
}