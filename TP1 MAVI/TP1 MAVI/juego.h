#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "enemigos.h"
#include "inocente.h"

using namespace sf;
using namespace std;

class juego {

private:
	bool game_over;
	bool slots_enemigos[5];
	int fps;
	int enemigos_eliminados;
	int inocentenes_eliminados;
	int puntaje;
	int vida;
	float tiempo2;
	Clock* reloj1;
	Time* tiempo1;
	Event * evento1;
	Texture txt_pant_inicio;
	Sprite spr_pant_inicio;
	Texture txt_fondo;
	Sprite spr_fondo;
	Texture txt_mira;
	Sprite spr_mira;
	Texture txt_bang;
	Sprite spr_bang;
	Texture txt_oops;
	Sprite spr_oops;
	Texture txt_gameover;
	Sprite spr_gameover;
	SoundBuffer sbuff_disparo;
	SoundBuffer sbuff_herida;
	SoundBuffer sbuff_inocente;
	SoundBuffer sbuff_inicio;
	SoundBuffer sbuff_gameover;
	Sound sound_disparo;
	Sound sound_herida;
	Sound sound_inocente;
	Sound sound_inicio;
	Sound sound_gameover;
	enemigos* enemigo[5];
	inocente* inocent;
	RenderWindow* ventana1;

public:
	juego(Vector2f resolucion, String titulo);
	void gameloop();
	void cargar_graficos();
	void procesar_eventos();
	void bienvenida();
	void check_personajes();
	void check_gameover();
};
