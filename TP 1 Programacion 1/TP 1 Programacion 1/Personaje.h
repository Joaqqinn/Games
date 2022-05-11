#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Afichmation.h"

//DECLARACION DE CONSTANTES
const float	SPEED_X = 30.0f;
const float	SPEED_Y = 30.0f;

class Personaje {

private:
	Afichmation* anim;
	bool saltoEnProceso;
	bool enAscenso;
	int	posicionTerrenoY;
	int maxAscensoSaltoY;

	SoundBuffer sbuffer_jump;
	Sound sound_jump;

public:
	Personaje(int x, int y);
	~Personaje() {}
	void initializer(); //iniciamos variables
	void update_jump(bool teclaSaltoPresionada, float delta_time_seconds); //actualizamos el salto
	void movement(float delta_time_seconds); //movimiento por teclas
	void drawing(RenderWindow* v); //metodo para dibujar el spritesheet
	FloatRect get_bounds(); //obtener los bounds de nuestro personaje 
	void stop_jump() { enAscenso = false; } //detenemos la subida del salto

};