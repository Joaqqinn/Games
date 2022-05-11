#include "game.h"
#include <Windows.h>

Game::Game(Vector2f resolucion, String titulo) {

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(60);
	
	screen_init();
	initializer();
	music_background.play();
	gameloop();
}

void Game::screen_init() {

	txt_inicio = new Texture();
	spr_inicio = new Sprite();
	txt_inicio->loadFromFile("Images/inicio.jpg");
	spr_inicio->setTexture(*txt_inicio);

	ventana1->clear();
	ventana1->draw(*spr_inicio);
	ventana1->display();
	//CUANDO PRESIONAMOS ENTER INICIAR EL JUEGO
	bool inicio = true;
	while (inicio) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			inicio = false;
		}
	}

}

void Game::initializer() {

	fps = 1 / 60.f;
	reloj1 = new Clock();
	reloj_contador = new Clock();
	tiempo1 = new Time();
	tiempo2 = 0.f;
	pos_arreglo = 0;
	gameover = false;
	winner = false;

	evento1 = new Event();

	//CREACION JUGADOR
	jugador = new Personaje(POSICION_TERRENO_Y, MAX_ASCENSO_SALTO_Y);
	
	//CREACION DE BLOQUES
	for (int i = 0; i < 10; i++) {

		bloques[i] = new Bloque();
		if (i != 0) {
			bloques[i]->set_position(bloques[i-1]->get_sprite().getPosition().x + 75, bloques[1]->get_sprite().getPosition().y);
		}
	}		

	order_array();

	//CREACION CONTADOR
	contador = new Contador(reloj_contador->getElapsedTime().asSeconds());

	//VISUAL
	txt_background = new Texture;
	spr_background = new Sprite;
	txt_background->loadFromFile("Images/fondo.jpg");
	spr_background->setTexture(*txt_background);


	//MUSIC
	music_background.openFromFile("Sounds/background.ogg");
	music_background.setVolume(20);
	music_background.setLoop(true);
	
	//SOUNDS
	sbuffer_coin.loadFromFile("Sounds/coin.wav");
	sound_coin.setBuffer(sbuffer_coin);
	sound_coin.setVolume(20);

	sbuffer_error.loadFromFile("Sounds/error.wav");
	sound_error.setBuffer(sbuffer_error);
	sound_error.setVolume(20);

	sbuffer_gameover.loadFromFile("Sounds/gameover.wav");
	sound_gameover.setBuffer(sbuffer_gameover);
	sound_gameover.setVolume(20);

	//TEXTO
	fuente = new Font();
	fuente->loadFromFile("Font/mario.ttf");
	//WINNER
	texto_ganador = new Text();
	texto_ganador->setFont(*fuente);
	texto_ganador->setString("GANASTE!");
	texto_ganador->setPosition(300, 250);
	texto_ganador->setOrigin(texto_ganador->getGlobalBounds().width / 2, texto_ganador->getGlobalBounds().height / 2);
	texto_ganador->setCharacterSize(60);
	//LOOSER
	texto_perdedor = new Text();
	texto_perdedor->setFont(*fuente);
	texto_perdedor->setString("PERDISTE!");
	texto_perdedor->setPosition(375, 250);
	texto_perdedor->setOrigin(texto_ganador->getGlobalBounds().width / 2, texto_ganador->getGlobalBounds().height / 2);
	texto_perdedor->setCharacterSize(60);

}

void Game::gameloop() {

	delta_time_seconds = reloj1->restart().asSeconds();

	*tiempo1 = reloj1->getElapsedTime();

	if (tiempo1->asSeconds() > tiempo2 / fps) {

		tiempo2 = tiempo1->asSeconds();

		while (ventana1->isOpen()) {

			if (!gameover) { //cuando el juego termina dejamos de actualizar
				update();
			}
			check_collisions();
			drawing();

		}
	}
}

void Game::update() {
	//SI SE GANA O SE PIERDE DETENEMOS EL JUEGO
	if (contador->get_fin() || winner) {
		gameover = true;
		if (contador->get_fin()) {
			music_background.pause();
			sound_gameover.play();
		}
		//PASAMOS EL ARRAY ORDENADO PARA EL DIBUJO FINAL
		for (int i = 0; i < 10; i++) {
			bloques[i]->set_num_bloques(arreglo[i], i);
			
			if (pos_arreglo > i) {
				bloques[i]->set_color(true);
			}
			else {
				bloques[i]->set_color(false);
			}
		}
	}
	process_event();
	jugador->movement(delta_time_seconds);
	jugador->update_jump(teclaSaltoPresionada, delta_time_seconds);
	contador->update(reloj_contador->getElapsedTime().asSeconds());

}

void Game::drawing() {

	ventana1->clear();
	ventana1->draw(*spr_background);
	jugador->drawing(ventana1);
	for (int i = 0; i < 10; i++) {

		ventana1->draw(bloques[i]->get_sprite());
		ventana1->draw(bloques[i]->get_text());

	}
	ventana1->draw(bloques[0]->get_text());
	ventana1->draw(contador->get_text());
	if (winner) {
		ventana1->draw(*texto_ganador);
	}
	if (contador->get_fin()) {
		ventana1->draw(*texto_perdedor);
	}
	ventana1->display();

}

void Game::process_event() {

	while (ventana1->pollEvent(*evento1)) {

		if (evento1->type == sf::Event::KeyPressed && evento1->key.code == sf::Keyboard::Space) {
			teclaSaltoPresionada = true;
		}
		if (evento1->type == sf::Event::KeyReleased && evento1->key.code == sf::Keyboard::Space) {
			teclaSaltoPresionada = false;
		}
	}
}

void Game::check_collisions() {

	for (int i = 0; i < 10; i++) {
		//SI EXISTE LA COLISION
		if (bloques[i]->get_sprite().getGlobalBounds().intersects(jugador->get_bounds())) {
			jugador->stop_jump();
			//SI EL BLOQUE CON EL QUE COLISIONA ES EL DEL NUMERO MENOR
			if (bloques[i]->get_num_bloques() == arreglo[pos_arreglo]) {
				sound_coin.play();
				bloques[i]->set_color(true);
				if (pos_arreglo < 9) { //sumamos los aciertos para controlar si se gana
					pos_arreglo++;
				}
				else {
					winner = true;
				}
			}
			else {
				sound_error.play();
				contador->decrease_time(); //en caso de error en el numero restamos tiempo
			}
		}
	}

}

void Game::order_array() {
	
	int auxiliar;

	for (int i = 0; i < 10; i++) {

		arreglo[i] = bloques[i]->get_num_bloques(); //le pasamos los numeros aleatorios que creamos en bloque

	}

	for (int i = 0; i < 10; i++) {//lo necesito para recorrerlos todos
		for (int j = 0; j < 9; j++) {//lo necesito para observar el siguiente
			if (arreglo[j] > arreglo[j + 1]) {//Si el valor actual es mayor que el valor siguiente
				//lo que tengo en el valor actual lo recuerdo en la variable auxiliar
				auxiliar = arreglo[j];
				//lo que tengo en la posición siguiente lo coloco en la posición de lectura actual
				arreglo[j] = arreglo[j + 1];
				//y lo que tenía en la posición actual (que sobreescribí antes) lo tenía salvado en el auxiliar
				//y de ese modo provoco un intercambio
				arreglo[j + 1] = auxiliar;
			}
		}
	}
}