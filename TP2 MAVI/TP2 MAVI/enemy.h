#pragma once
#include "SFML/Graphics.hpp"
#include <ctime>

using namespace sf;

class enemy {

private:
	Texture* txt_enemy_big;
	Sprite* spr_enemy_big;
	Texture* txt_enemy_small;
	Sprite* spr_enemy_small;
	Vector2f velocidad;


public:
	enemy(int pos_x, int pos_y);
	~enemy();
	Sprite get_spr_big() { return *spr_enemy_big; } //retorna sprite big asteroid
	Sprite get_spr_small() { return *spr_enemy_small; } //retorna sprite small asteroid
	void update(float delta_t, int num_spr); //actualizamos la posicion
};