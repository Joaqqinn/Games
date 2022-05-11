#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Personaje.h"
#include "Bloque.h"
#include "Contador.h"

//DECLARACION DE CONSTANTES
const int WIDE = 800;
const int HIGH = 600;
const int POSICION_TERRENO_Y = 495;
const int MAX_ASCENSO_SALTO_Y = 100;

using namespace sf;

class Game {

private:
	RenderWindow* ventana1;
	Personaje* jugador;
	Bloque* bloques[10];
	Contador* contador;
	Texture* txt_inicio;
	Texture* txt_background;
	Sprite* spr_inicio;
	Sprite* spr_background;
	Event* evento1;
	Clock* reloj1;
	Clock* reloj_contador;
	Time* tiempo1;
	Font* fuente;
	Text* texto_ganador;
	Text* texto_perdedor;
	float tiempo2;
	float delta_time_seconds;
	float fps;
	bool gameover;
	bool winner;
	bool teclaSaltoPresionada;
	int arreglo[10];
	int pos_arreglo;
	Music music_background;
	SoundBuffer sbuffer_coin;
	SoundBuffer sbuffer_error;
	SoundBuffer sbuffer_gameover;
	Sound sound_coin;
	Sound sound_error;
	Sound sound_gameover;

public:
	Game(Vector2f resolucion, String titulo);
	void screen_init(); //todo lo necesario para la pantalla de inicio
	void initializer(); //inicializamos variables
	void gameloop(); //bucle continuo del juego
	void drawing(); //dibujamos
	void update(); //actualizamos los objetos
	void process_event(); //eventos relacionados al salto
	void check_collisions(); //chequeamos colisiones entre los objetos
	void order_array(); //creamos un arreglo y lo ordenamos

};