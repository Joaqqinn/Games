#pragma once
#include "Afichmation.h"
#include "Game.h"

using namespace sf;

//DECLARACION DE CONSTANTES
const float	SPEED_X = 200.0f;
const float	SPEED_Y = 500.0f;

class Personaje {

private:
	Afichmation* anim;
	//string path;
	bool saltoEnProceso;
	bool enAscenso;
	int	posicionTerrenoY;
	int maxAscensoSaltoY;

	SoundBuffer sbuffer_jump;
	Sound sound_jump;

public:
	Personaje(int x, int y);
	~Personaje();
	void initializer();
	void update_jump(bool teclaSaltoPresionada, float delta_time_seconds);
	void movement(float delta_time_seconds); //movimiento
	void drawing(RenderWindow* v);
};