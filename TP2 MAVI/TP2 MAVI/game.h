#pragma once
#include "ship.h"
#include "bullet.h"
#include "enemy.h"
#include <vector>
#include <ctime>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

class game {

private:
	RenderWindow* ventana1;
	Texture* txt_menu;
	Texture* txt_controls;
	Texture* txt_background;
	Texture* txt_explosion;
	Texture* txt_ship_impulse;
	Texture* txt_explosion_asteroids;
	Sprite* spr_menu;
	Sprite* spr_controls;
	Sprite* spr_background;
	Sprite* spr_explosion;
	Sprite* spr_ship_impulse;
	Sprite* spr_explosion_asteroids;
	Music music_background;
	SoundBuffer sbuffer_shoot;
	SoundBuffer sbuffer_bigasteroids;
	SoundBuffer sbuffer_expship;
	SoundBuffer sbuffer_smallasteroids;
	SoundBuffer sbuffer_impulse;
	SoundBuffer sbuffer_buttons;
	SoundBuffer sbuffer_buttonback;
	Sound sound_shoot;
	Sound sound_bigasteroids;
	Sound sound_expship;
	Sound sound_smallasteroids;
	Sound sound_impulse;
	Sound sound_buttons;
	Sound sound_buttonback;
	Font* fuente1;
	Text* texto_play;
	Text* texto_controls;
	Text* texto_back;
	Text* texto_repeat;
	Text* texto_yes;
	Text* texto_no;
	Text* texto_score;
	Text* texto_points;
	ship* ship1;
	bullet* bullets[100];
	enemy* big_asteroid[15];
	enemy* small_asteroids[15];
	Event * evento;
	Event* evento_menu;
	Clock * reloj1; //reloj gameloop
	Time * tiempo1;
	Clock * reloj2; //reloj para las balas
	Time* tiempobala;
	Vector2i frame_actual;
	Vector2i posicion_mousse;
	int fps;
	int asteroids_destroyed;
	bool gaming;
	bool _menu;
	bool controls;
	bool game_over;
	bool explosion_ship;
	bool explosion_asteroid;
	bool impulso;
	bool _gameover;
	float tiempo2;


public:
	game(Vector2f resolucion, String titulo);
	void gameloop(); //bucle continuo del juego
	void update(); //actualizador
	void load_graphics(); // cargamos las texturas y sprites
	void load_sounds(); // cargamos la musica y efectos de sonido
	void menu(); //pantalla de inicio y menu
	void initializer_menu(); //inicializamos variables usadas solo en el menu
	void initializer(); // inicializador de variables
	void drawing_menu();// dibujamos el menu y sus opciones
	void drawing(); // dibujado
	void process_event_menu(); //procesamiento de eventos solo ocurridos en la pantalla del menu
	void process_event(); // procesamiento de eventos
	void check_collisions(); //chequeamos las colisiones
	void animations(Vector2i num_frame); //animaciones
	void shoot(); // dispara
	void delete_objects(); //eliminamos objetos
	void load_enemys(); // creamos asteroids
};