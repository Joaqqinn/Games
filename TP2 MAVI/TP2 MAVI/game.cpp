#include "game.h"
#include <iostream>

game::game(Vector2f resolucion, String titulo) {

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	
	menu();
	initializer();
	load_graphics();
	load_sounds();
	gameloop();
}

void game::menu() {

	initializer_menu();
	drawing_menu();
	music_background.play();
	while (gaming) {
		while (ventana1->pollEvent(*evento_menu)) {
			process_event_menu();
		}
	}
}

void game::initializer_menu() {

	_menu = true;
	gaming = true;
	controls = false;
	_gameover = false;

	evento_menu = new Event();
	txt_menu = new Texture;
	spr_menu = new Sprite;

	txt_controls = new Texture;
	spr_controls = new Sprite;

	fuente1 = new Font();
	fuente1->loadFromFile("Fonts/asteroid.ttf");
                                     //TEXTO
	//PLAY
	texto_play = new Text();
	texto_play->setFont(*fuente1);
	texto_play->setString("PLAY {");
	texto_play->setOrigin(texto_play->getGlobalBounds().width / 2, texto_play->getGlobalBounds().height / 2);
	texto_play->setPosition(640, 700);
	texto_play->setCharacterSize(50);
	//CONTROLS
	texto_controls = new Text();
	texto_controls->setFont(*fuente1);
	texto_controls->setString("CONTROLS");
	texto_controls->setOrigin(texto_controls->getGlobalBounds().width / 2, texto_controls->getGlobalBounds().height / 2);
	texto_controls->setPosition(623, 765);
	texto_controls->setCharacterSize(50);
	//BACK
	texto_back = new Text();
	texto_back->setFont(*fuente1);
	texto_back->setString("BACK");
	texto_back->setOrigin(texto_back->getGlobalBounds().width / 2, texto_back->getGlobalBounds().height / 2);
	texto_back->setPosition(100, 50);
	texto_back->setCharacterSize(75);
	//GAME OVER
	texto_repeat = new Text();
	texto_repeat->setFont(*fuente1);
	texto_repeat->setString("WANT TO PLAY AGAIN ?");
	texto_repeat->setOrigin(texto_repeat->getGlobalBounds().width / 2, texto_repeat->getGlobalBounds().height / 2);
	texto_repeat->setPosition(375, 412);
	texto_repeat->setCharacterSize(75);
	//YES
	texto_yes = new Text();
	texto_yes->setFont(*fuente1);
	texto_yes->setString("YES (Y)");
	texto_yes->setOrigin(texto_yes->getGlobalBounds().width / 2, texto_yes->getGlobalBounds().height / 2);
	texto_yes->setPosition(350, 550);
	texto_yes->setCharacterSize(75);
	//NO
	texto_no = new Text();
	texto_no->setFont(*fuente1);
	texto_no->setString("NO (ESC)");
	texto_no->setOrigin(texto_no->getGlobalBounds().width / 2, texto_no->getGlobalBounds().height / 2);
	texto_no->setPosition(750, 550);
	texto_no->setCharacterSize(75);
	//MENSAJE SCORE
	texto_score = new Text();
	texto_score->setFont(*fuente1);
	texto_score->setString("ASTEROIDS DESTROYED: ");
	texto_score->setOrigin(texto_score->getGlobalBounds().width / 2, texto_score->getGlobalBounds().height / 2);
	texto_score->setPosition(300, 650);
	texto_score->setCharacterSize(75);
	//SCORE
	texto_points = new Text();
	texto_points->setFont(*fuente1);
	texto_points->setString(to_string(asteroids_destroyed));
	texto_points->setOrigin(texto_points->getGlobalBounds().width / 2, texto_points->getGlobalBounds().height / 2);
	texto_points->setPosition(1100, 650);
	texto_points->setCharacterSize(75);
	
	//MENU
	txt_menu->loadFromFile("Sprites/menu.png");
	spr_menu->setTexture(*txt_menu);
	spr_menu->setScale((float)ventana1->getSize().x / txt_menu->getSize().x, (float)ventana1->getSize().y / txt_menu->getSize().y);
	//CONTROLS
	txt_controls->loadFromFile("Sprites/controls.jpg");
	spr_controls->setTexture(*txt_controls);
	spr_controls->setScale((float)ventana1->getSize().x / txt_controls->getSize().x, (float)ventana1->getSize().y / txt_controls->getSize().y);
	                                      //SOUNDS
	//MUSIC BACKGROUND
	music_background.openFromFile("Sounds/background.ogg");
	music_background.setVolume(80);
	music_background.setLoop(true);
    //BUTTONS
	sbuffer_buttons.loadFromFile("Sounds/buttons.wav");
	sound_buttons.setBuffer(sbuffer_buttons);
	sound_buttons.setVolume(20);
	//BACK
	sbuffer_buttonback.loadFromFile("Sounds/button_back.wav");
	sound_buttonback.setBuffer(sbuffer_buttonback);
	sound_buttonback.setVolume(20);
}

void game::drawing_menu() {

	ventana1->clear();
	if (_menu) {
		ventana1->draw(*spr_menu);
		ventana1->draw(*texto_play);
		ventana1->draw(*texto_controls);
	}
	if (controls) {
		ventana1->draw(*spr_controls);
		ventana1->draw(*texto_back);
	}
	ventana1->display();
}

void game::process_event_menu() {

	switch (evento_menu->type) {

	case Event::Closed:
		exit(1);
		break;

	case Event::MouseButtonPressed:

		posicion_mousse = Mouse::getPosition(*ventana1);
		posicion_mousse = (Vector2i)ventana1->mapPixelToCoords(posicion_mousse);
		FloatRect mousse((Vector2f)posicion_mousse, {32, 32});

		if (_menu) {
			if (texto_play->getGlobalBounds().intersects(mousse)) {
				sound_buttons.play();
				gaming = false;
			}
			if (texto_controls->getGlobalBounds().intersects(mousse)) {
				sound_buttons.play();
				controls = true;
				_menu = false;
				drawing_menu();
		    }
		}
		if (controls) {
			if (texto_back->getGlobalBounds().intersects(mousse)) {
				sound_buttonback.play();
				controls = false;
				_menu = true;
				drawing_menu();
			}
		}	
	}
}

void game::initializer() {

	fps = 60;

	asteroids_destroyed = 0;

	ventana1->setFramerateLimit(fps);

	ventana1->setMouseCursorVisible(false);

	game_over = false;

	ship1 = new ship();

	evento = new Event();
	
	reloj1 = new Clock();

	tiempo1 = new Time();

	reloj2 = new Clock();

	tiempobala = new Time();

	txt_background = new Texture;
	spr_background = new Sprite;

	txt_explosion = new Texture;
	spr_explosion = new Sprite;

	txt_ship_impulse = new Texture;
	spr_ship_impulse = new Sprite;

	txt_explosion_asteroids = new Texture;
	spr_explosion_asteroids = new Sprite;
}

void game::gameloop() {

	*tiempo1 = reloj1->getElapsedTime();
	
	if (tiempo1->asSeconds() > tiempo2 / fps) {

		tiempo2 = tiempo1->asSeconds();

		while (!game_over) {
			while (ventana1->pollEvent(*evento)) {
				process_event();
			}
			if (!_gameover) {
				update();
			}
			check_collisions();
			drawing();
			reloj1->restart();
		}
	}
}

void game::update() {
	//ACTUALIZAMOS CADA OBJETO
	ship1->update();
	for (int i = 0; i < 100; i++) {
		if (bullets[i]) {
			bullets[i]->update();
		}
	}
	load_enemys();
	for (int i = 0; i < 15; i++) {
		if (big_asteroid[i]) {
			big_asteroid[i]->update(tiempo2, 1);
		}
	}
	for (int i = 0; i < 15; i++) {
		if (small_asteroids[i]) {
			small_asteroids[i]->update(tiempo2, 2);
		}
	}
}

void game::process_event() {

	switch (evento->type) {

	case Event::Closed:
		exit(1);
	break;

	case Event::KeyPressed:
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			exit(1);
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				ship1->set_rotation(-7);
				ship1->set_velocidad(Vector2f(ship1->get_angle(5.0)));
				
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				ship1->set_rotation(-7);
				shoot();
			}
			else {
				ship1->set_rotation(-7);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				ship1->set_rotation(+7);
				ship1->set_velocidad(Vector2f(ship1->get_angle(5.0)));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				ship1->set_rotation(+7);
				shoot();
			}
			else {
				ship1->set_rotation(+7);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::W)) {
			
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				ship1->set_velocidad(Vector2f(ship1->get_angle(5.0)));
				shoot();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space)) {
				ship1->set_velocidad(Vector2f(ship1->get_angle(10.0)));
				sound_impulse.play();
				impulso = true;
			}
			else {
				ship1->set_velocidad(Vector2f(ship1->get_angle(5.0)));
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				shoot();
		}
		if (_gameover) {
			if (Keyboard::isKeyPressed(Keyboard::Y)) {
				sound_buttons.play();
				_gameover = false;
			}
		}
		break;

		// SOLTAR TECLAS

	case Event::KeyReleased:

		if (evento->key.code == Keyboard::W) {

			if (evento->key.code == Keyboard::Space) {
				ship1->set_velocidad(Vector2f(ship1->get_angle(2.5)));
			}
			else {
				ship1->set_velocidad(Vector2f(ship1->get_angle(1.5)));
				impulso = false;
			}
		}
		else if (evento->key.code == Keyboard::Space) {
			
				ship1->set_velocidad(Vector2f(ship1->get_angle(2.5)));
				impulso = false;
		}
		break;
	}
}

void game::load_graphics() {
	//background
	txt_background->loadFromFile("Sprites/fondo.jpg");
	spr_background->setTexture(*txt_background);
	//animacion explosion nave
	txt_explosion->loadFromFile("Sprites/explosion.png");
	spr_explosion->setTexture(*txt_explosion);
	spr_explosion->setOrigin((spr_explosion->getTexture()->getSize().x / 48) / 2.f, spr_explosion->getTexture()->getSize().y / 2.f);
	//animacion impulso nave
	txt_ship_impulse->loadFromFile("Sprites/naveimp.png");
	spr_ship_impulse->setTexture(*txt_ship_impulse);
	spr_ship_impulse->setScale(0.15, 0.15);
	spr_ship_impulse->setOrigin((spr_ship_impulse->getTexture()->getSize().x) / 2.f, spr_ship_impulse->getTexture()->getSize().y / 2.f);
	//animacion choque bala y asteroides
	txt_explosion_asteroids->loadFromFile("Sprites/explosion_ast.png");
	spr_explosion_asteroids->setTexture(*txt_explosion_asteroids);
	spr_explosion_asteroids->setOrigin((spr_explosion_asteroids->getTexture()->getSize().x / 64) / 2.f, spr_explosion->getTexture()->getSize().y / 2.f);
}

void game::load_sounds() {
	//DISPAROS
	sbuffer_shoot.loadFromFile("Sounds/shoot.wav");
	sound_shoot.setBuffer(sbuffer_shoot);
	//EXPLOSION NAVE
	sbuffer_expship.loadFromFile("Sounds/expship.wav");
	sound_expship.setBuffer(sbuffer_expship);
	sound_expship.setPitch(2);
	//EXPLOSION BIG ASTEROIDS
	sbuffer_bigasteroids.loadFromFile("Sounds/exp_bigasterroids.wav");
	sound_bigasteroids.setBuffer(sbuffer_bigasteroids);
	sound_bigasteroids.setVolume(70);
	//EXPLOSIONES SMALL ASTEROIDS
	sbuffer_smallasteroids.loadFromFile("Sounds/exp_smallasteroids.wav");
	sound_smallasteroids.setBuffer(sbuffer_smallasteroids);
	//IMPULSO NAVE
	sbuffer_impulse.loadFromFile("Sounds/impulse.wav");
	sound_impulse.setBuffer(sbuffer_impulse);
	sound_impulse.setVolume(20);
	sound_impulse.setPitch(2);
}

void game::drawing() {

	ventana1->clear();
	ventana1->draw(*spr_background);
	if (impulso) { //SPRITE NAVE CON IMPULSO
		spr_ship_impulse->setPosition(ship1->get_spr().getPosition());
		spr_ship_impulse->setRotation(ship1->get_spr().getRotation());
		ventana1->draw(*spr_ship_impulse);
	}
	else if (_gameover) { //DESAPARECEMOS LA NAVE SI COLISIONA
		ship1->get_spr().setPosition(1300, 1100);
	}
	else {//SPRITE NAVE NORMAL
		ventana1->draw(ship1->get_spr());
	}
	for (int i = 0; i < 15; i++) { //DIBUJAMOS ASTEROIDS GRANDES
		if (big_asteroid[i]) {
			ventana1->draw(big_asteroid[i]->get_spr_big());
		}
	}
	for (int i = 0; i < 15; i++) { //DIBUJAMOS ASTEROIDS PEQUEÑOS
		if (small_asteroids[i]) {
			ventana1->draw(small_asteroids[i]->get_spr_small());
		}
	}
	for (int i = 0; i < 100; i++) { // DIBUJAMOS LAS BALAS
		if (bullets[i]) {
			ventana1->draw(bullets[i]->get_spr());
		}
	}
	if (_gameover) { // SI GAMEOVER ES VERDADERO DIBUJAMOS MENU
		ventana1->draw(*texto_repeat);
		ventana1->draw(*texto_yes);
		ventana1->draw(*texto_no);
		ventana1->draw(*texto_score);
		texto_points->setString(to_string(asteroids_destroyed));
		ventana1->draw(*texto_points);
	}
	if (explosion_ship) { //SI LA NAVE COLISIONA DIBUJAMOS LA ANIMACION
		if (frame_actual.x < 48) {
			frame_actual.x++;
		}
		else {
			frame_actual.x = 0;
			explosion_ship = false;
		}
		animations(frame_actual);
		ventana1->draw(*spr_explosion);
	}
	if (explosion_asteroid) { //SI BALA Y ASTEROIDS COLISIONAN DIBUJAMOS ANIMACION
		if (frame_actual.x < 64) {
			frame_actual.x++;
		}
		else {
			frame_actual.x = 0;
			explosion_asteroid = false;
		}
		animations(frame_actual);
		ventana1->draw(*spr_explosion_asteroids);
	}
	ventana1->display();
}

void game::check_collisions() {

	float pos_x_nave = ship1->get_spr().getPosition().x;
	float pos_y_nave = ship1->get_spr().getPosition().y;

	// LOOP DE LA NAVE CUANDO LLEGA A LOS LIMITES DE PANTALLA
	if (pos_x_nave <= 0) {ship1->set_translation({ 1280.0 , 0.0});} 
	else if (pos_x_nave >= 1280) {ship1->set_translation({ -ship1->get_spr().getPosition().x , 0.0});} 
	if (pos_y_nave <= 0) {ship1->set_translation({ 0.0 , 1024.0 });}
	else if (pos_y_nave >= 1024) {	ship1->set_translation({ 0.0, -ship1->get_spr().getPosition().y});}
	//ELIMINAMOS LOS OBJETOS QUE SALEN DE PANTALLA
	delete_objects();
	//COLISON NAVE CON BIG ASTEROIDES
	for (int i = 0; i < 15; i++) {
		if (big_asteroid[i]) {
			if (big_asteroid[i]->get_spr_big().getGlobalBounds().intersects(ship1->get_spr().getGlobalBounds())) {
				sound_expship.play();
				explosion_ship = true;
				big_asteroid[i]->~enemy();
				big_asteroid[i] = NULL;
				_gameover = true;
			}
		}
	}	
	//COLISON NAVE CON SMALL ASTEROIDES
	for (int i = 0; i < 15; i++) {
		if (small_asteroids[i]) {
			if (small_asteroids[i]->get_spr_small().getGlobalBounds().intersects(ship1->get_spr().getGlobalBounds())) {
				sound_expship.play();
				explosion_ship = true;
				small_asteroids[i]->~enemy();
				small_asteroids[i] = NULL;
				_gameover = true;
			}
		}
	}
	//COLISIONES BALAS CON BIG ASTEROIDS
	for (int i = 0; i < 100; i++) {
		if (bullets[i]) {
			for (int j = 0; j < 15; j++) {
				if (big_asteroid[j]) {
					if (bullets[i]->get_spr().getGlobalBounds().intersects(big_asteroid[j]->get_spr_big().getGlobalBounds())) {
						sound_bigasteroids.play();
						spr_explosion_asteroids->setScale(1.0, 1.0);
						spr_explosion_asteroids->setPosition(big_asteroid[j]->get_spr_big().getPosition());
						explosion_asteroid = true;
						if (!small_asteroids[j]) {
							small_asteroids[j] = new enemy(big_asteroid[j]->get_spr_big().getPosition().x, big_asteroid[j]->get_spr_big().getPosition().y);
						}
						big_asteroid[j]->~enemy();
						big_asteroid[j] = NULL;
						bullets[i]->set_velocidad(Vector2f(ship1->get_angle(1000.0)));
						asteroids_destroyed++;
					}
				}
			}
		}
	}
	//COLISIONES BALAS CON SMALL ASTEROIDS
	for (int i = 0; i < 100; i++) {
		if (bullets[i]) {
			for (int j = 0; j < 15; j++) {
				if (small_asteroids[j]) {
					if (bullets[i]->get_spr().getGlobalBounds().intersects(small_asteroids[j]->get_spr_small().getGlobalBounds())) {
						sound_smallasteroids.play();
						spr_explosion_asteroids->setScale(0.5, 0.5);
						spr_explosion_asteroids->setPosition(small_asteroids[j]->get_spr_small().getPosition());
						explosion_asteroid = true;
						small_asteroids[j]->~enemy();
						small_asteroids[j] = NULL;
						bullets[i]->set_velocidad(Vector2f(ship1->get_angle(1000.0)));
						asteroids_destroyed++;
					}
				}
			}
		}
	}
}

void game::animations(Vector2i num_frame) {
	//ANIMACION EXPLOSION DE LA NAVE
	spr_explosion->setPosition(ship1->get_spr().getPosition());
	IntRect tamaño_frame((num_frame.x * spr_explosion->getTexture()->getSize().x / 48), 0, 256, 256);
	spr_explosion->setTextureRect(tamaño_frame);
	//ANIMACION EXPLOSION DE ASTEROIDS
	IntRect tamaño_frame1((num_frame.x * spr_explosion_asteroids->getTexture()->getSize().x / 64), 0, 192, 192);
	spr_explosion_asteroids->setTextureRect(tamaño_frame1);
}

void game::shoot() {
	//CREAMOS LAS BALAS
	*tiempobala = reloj2->getElapsedTime();
	if (tiempobala->asSeconds() > 0.1 ) {
		for (int i = 0; i < 100; i++) {
			if (!bullets[i]) {
				sound_shoot.play();
				bullets[i] = new bullet(ship1->get_spr().getPosition(), ship1->get_spr().getRotation());
				bullets[i]->set_velocidad(Vector2f(ship1->get_angle(7.0)));
				i = 101;
				reloj2->restart();
			}
		}
	}
}

void game::delete_objects() {
	// ELIMINAR BALAS
	for (int i = 0; i < 100; i++) {
		if (bullets[i]) {
			float pos_x_bullet = bullets[i]->get_spr().getPosition().x;
			float pos_y_bullet = bullets[i]->get_spr().getPosition().y;

			if (pos_x_bullet <= 0 || pos_x_bullet >= 1280 || pos_y_bullet <= 0 || pos_y_bullet >= 1024) {
				bullets[i]->~bullet();
				bullets[i] = NULL;
			}
		}
	}
	//ELMINAR BIG ASTEROIDS
	for (int i = 0; i < 15; i++) {
		if (big_asteroid[i]) {
			float pos_x_bigasteroids = big_asteroid[i]->get_spr_big().getPosition().x;
			float pos_y_bigasteroids = big_asteroid[i]->get_spr_big().getPosition().y;

			if (pos_x_bigasteroids <= 0 || pos_x_bigasteroids >= 1280 || pos_y_bigasteroids <= 0 || pos_y_bigasteroids >= 1024) {
				big_asteroid[i]->~enemy();
				big_asteroid[i] = NULL;
			}
		}
	}
	//ELIMINAR SMALL ASTEORIDS
	for (int i = 0; i < 15; i++) {
		if (small_asteroids[i]) {
			float pos_x_smallasteroids = small_asteroids[i]->get_spr_small().getPosition().x;
			float pos_y_smallasteroids = small_asteroids[i]->get_spr_small().getPosition().y;

			if (pos_x_smallasteroids <= 0 || pos_x_smallasteroids >= 1280 || pos_y_smallasteroids <= 0 || pos_y_smallasteroids >= 1024) {
				small_asteroids[i]->~enemy();
				small_asteroids[i] = NULL;
			}
		}
	}
}

void game::load_enemys() {
	//CARGAMOS ENEMIGOS EN 3 LADOS DE LA PANTALLA
	for (int i = 0; i < 5; i++) {
		int posicion_x = (rand() % 1280);
		if (!big_asteroid[i]) {
			big_asteroid[i] = new enemy(posicion_x, 0);
		}
	}
	for (int i = 5; i <10 ; i++) {
		int	posicion_y = (rand() % 1024);
		if (!big_asteroid[i]) {
			big_asteroid[i] = new enemy(0, posicion_y);
		}
	}
	for (int i = 10; i < 15; i++) {
		int	posicion_y = (rand() % 1024);
		if (!big_asteroid[i]) {
			big_asteroid[i] = new enemy(1280, posicion_y);
		}
	}
}
