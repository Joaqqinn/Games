#include "game.h"

Game::Game(Vector2f resolucion, String titulo) {

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(60);
	
	initializer();
	music_background.play();
	gameloop();
}

void Game::initializer() {

	fps = 1 / 60.f;
	reloj1 = new Clock();
	tiempo1 = new Time();
	tiempo2 = 0.f;


	//VISUAL
	txt_background = new Texture;
	spr_background = new Sprite;
	txt_background->loadFromFile("images/fondo.jpg");
	spr_background->setTexture(*txt_background);

	//SOUNDS
	music_background.openFromFile("Sounds/background.ogg");
	music_background.setVolume(35);
	music_background.setLoop(true);

}

void Game::gameloop() {

	while (ventana1->isOpen()) {
		
		*tiempo1 = reloj1->getElapsedTime();

			
	}
}

void Game::update() {

	

}

void Game::drawing() {

	//actualizar con update la posicion
	ventana1->clear(Color(255, 255, 255, 255));
	ventana1->draw(*spr_background);
	//jugador->drawing(ventana1);
	ventana1->display();

}