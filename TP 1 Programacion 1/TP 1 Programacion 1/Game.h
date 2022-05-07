#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Personaje.h"

//Declaración de constantes
const int WIDE = 800;
const int HIGH = 600;
const int POSICION_TERRENO_Y = 460;
const int MAX_ASCENSO_SALTO_Y = 100;

using namespace sf;

class Game {

private:
	RenderWindow* ventana1;
	Personaje* jugador;
	Texture* txt_background;
	Sprite* spr_background;
	Clock* reloj1;
	Time* tiempo1;
	float tiempo2;
	float fps;

	bool teclaSaltoPresionada;

	Music music_background;

public:
	Game(Vector2f resolucion, String titulo);
	void initializer();
	void gameloop(); //bucle continuo del juego
	void drawing();
	void update();
};