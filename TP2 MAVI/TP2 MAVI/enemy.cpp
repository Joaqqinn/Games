#include "enemy.h"

enemy::enemy(int pos_x, int pos_y) {

	txt_enemy_big = new Texture;
	txt_enemy_big->loadFromFile("Sprites/asteroids1.png");
	spr_enemy_big = new Sprite(*txt_enemy_big);
	spr_enemy_big->setScale(0.45, 0.45);
	spr_enemy_big->setOrigin(spr_enemy_big->getTexture()->getSize().x / 2.f, spr_enemy_big->getTexture()->getSize().y / 2.f);
	spr_enemy_big->setPosition(pos_x, pos_y);

	txt_enemy_small = new Texture;
	txt_enemy_small->loadFromFile("Sprites/asteroids2.png");
	spr_enemy_small = new Sprite(*txt_enemy_small);
	spr_enemy_small->setScale(0.45, 0.45);
	spr_enemy_small->setOrigin(spr_enemy_small->getTexture()->getSize().x / 2.f, spr_enemy_small->getTexture()->getSize().y / 2.f);
	spr_enemy_small->setPosition(pos_x, pos_y);

	velocidad.x = (rand() % 2);
	velocidad.y = (rand() % 2)+1;

}

enemy::~enemy() {}

void enemy::update(float delta_t, int num_spr) {
	//1 ASTEROIDS BIG // 2 ASTEROIDS SMALL
	if (num_spr == 1) {
		if (spr_enemy_big->getPosition().x == 1280) {
			velocidad.x = velocidad.x * -1;
			velocidad.y = velocidad.y * -1;
			spr_enemy_big->setPosition((spr_enemy_big->getPosition().x + velocidad.x * delta_t), (spr_enemy_big->getPosition().y + velocidad.y * delta_t));
		}
		else {
			spr_enemy_big->setPosition(spr_enemy_big->getPosition().x + velocidad.x * delta_t, spr_enemy_big->getPosition().y + velocidad.y * delta_t);
		}
	}
	if (num_spr == 2) {
		int direccion = (rand() % 10);
		if (direccion < 5) {
			spr_enemy_small->setPosition((spr_enemy_small->getPosition().x + velocidad.x * delta_t), (spr_enemy_small->getPosition().y + velocidad.y * delta_t));
		}
		else if (direccion > 5) {
			spr_enemy_small->setPosition(spr_enemy_small->getPosition().x + velocidad.x * delta_t, spr_enemy_small->getPosition().y + velocidad.y * delta_t);
		}
	}
}