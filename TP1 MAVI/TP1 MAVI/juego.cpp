#include "juego.h"
#include <iostream>
#include <Windows.h>

juego::juego(Vector2f resolucion, String titulo) {

	game_over = false;

	fps = 60;

	tiempo2 = 0;

	enemigos_eliminados = 0;

	inocentenes_eliminados = 0;

	puntaje = 0;

	vida = 3;

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);

	ventana1->setFramerateLimit(fps);

	ventana1->setMouseCursorVisible(false);

	for (int i = 0; i < 5; i++) {

		slots_enemigos[i] = false;
	
	}

	evento1 = new Event;

	cargar_graficos();

	reloj1 = new Clock;
	tiempo1 = new Time;

	bienvenida();

	gameloop();
}

void juego::gameloop() {

	while (!game_over) {

		*tiempo1 = reloj1->getElapsedTime();

		if (tiempo1->asSeconds() > 5 + tiempo2) {
			tiempo2 = tiempo1->asSeconds();

			for (int i = 0; i < 5; i++) {

				if (!slots_enemigos[i]) {
					slots_enemigos[i] = true;
					int posicion = rand () % 5 + 1;
					switch (posicion) {

					case 1:
						enemigo[i] = new enemigos({ (float)(271.0), (float)133.0 });
						inocent = new inocente({ (float)(482.0), (float)181.0 });
						break;
					case 2:
						enemigo[i] = new enemigos({ (float)(271.0), (float)240.0 });
						break;
					case 3:
						enemigo[i] = new enemigos({ (float)(180.0), (float)350.0 });
						break;
					case 4:
						enemigo[i] = new enemigos({ (float)(720.0), (float)170.0 });
						break;
					case 5:
						enemigo[i] = new enemigos({ (float)(542.0), (float)285.0 });
						inocent = new inocente({ (float)(282.0), (float)347.0 });
						break;
					}
					break;
				}
			}
		}

		ventana1->clear();

		ventana1->draw(spr_fondo);

		for (int i = 0; i < 5; i++)
		{
			if (enemigo[i] != NULL)
			{
				ventana1->draw(enemigo[i]->get_sprite());
			}
		}

		if (inocent != NULL)
		{
			ventana1->draw(inocent->get_sprite());
		}
		

		ventana1->draw(spr_mira);

		procesar_eventos();

		check_personajes();

		check_gameover();

		ventana1->display();


	}
}

void juego::cargar_graficos() {

	txt_pant_inicio.loadFromFile("bienvenida.jpg");
	spr_pant_inicio.setTexture(txt_pant_inicio);
	spr_pant_inicio.setScale((float)ventana1->getSize().x / txt_pant_inicio.getSize().x, (float)ventana1->getSize().y / txt_pant_inicio.getSize().y);

	txt_fondo.loadFromFile("fondo1.jpg");
	spr_fondo.setTexture(txt_fondo);
	spr_fondo.setScale((float)ventana1->getSize().x / txt_fondo.getSize().x, (float)ventana1->getSize().y / txt_fondo.getSize().y);

	txt_mira.loadFromFile("mira1.png");
	spr_mira.setTexture(txt_mira);
	spr_mira.setScale(0.50, 0.50);

	txt_bang.loadFromFile("bang.png");
	spr_bang.setTexture(txt_bang);
	spr_bang.setPosition(100, 100);

	txt_oops.loadFromFile("oops.png");
	spr_oops.setTexture(txt_oops);
	spr_oops.setScale(0.80, 0.80);
	spr_oops.setPosition(100, 100);

	txt_gameover.loadFromFile("gameover.png");
	spr_gameover.setTexture(txt_gameover);
	spr_gameover.setScale((float)ventana1->getSize().x / txt_gameover.getSize().x, (float)ventana1->getSize().y / txt_gameover.getSize().y);

	sbuff_disparo.loadFromFile("disparo.wav");
	sound_disparo.setBuffer(sbuff_disparo);

	sbuff_herida.loadFromFile("herida.wav");
	sound_herida.setBuffer(sbuff_herida);

	sbuff_inocente.loadFromFile("inocente.wav");
	sound_inocente.setBuffer(sbuff_inocente);
	

	sbuff_gameover.loadFromFile("gameover.wav");
	sound_gameover.setBuffer(sbuff_gameover);

	sbuff_inicio.loadFromFile("inicio.wav");
	sound_inicio.setBuffer(sbuff_inicio);

}

void juego::bienvenida() {

	ventana1->clear();

	ventana1->draw(spr_pant_inicio);

	ventana1->display();

	cout << "! BIENVENIDO !" << endl;
	cout << "USTED POSEE 3 VIDAS " << endl;
	cout << "PRESIONE CUALQUIER TECLA PARA COMENZAR A JUGAR" << endl;

	system("PAUSE");

	sound_inicio.play();
}

void juego::procesar_eventos() {

	while (ventana1->pollEvent(*evento1)) {

		switch (evento1->type) {

		case Event::MouseMoved:

			spr_mira.setPosition((Vector2f)Mouse::getPosition(*ventana1));
			
		break;

		case Event::Closed:

			exit(1);
		
		break;

		case Event::MouseButtonPressed:
			
			sound_disparo.play();

			FloatRect ubicacion(spr_mira.getPosition(), (Vector2f)spr_mira.getTexture()->getSize());
			for (int i = 0; i < 5; i++) {

				if (enemigo[i]) {

					if (enemigo[i]->get_sprite().getGlobalBounds().intersects(ubicacion)) {

						enemigo[i] = NULL;
						slots_enemigos[i] = false;
						enemigos_eliminados++;
					}
				}
			}
			if(inocent)
				if (inocent->get_sprite().getGlobalBounds().intersects(ubicacion)) {
					sound_inocente.play();
					inocent = NULL;
					vida--;
					inocentenes_eliminados++;
					cout << "OH NO! MATASTE 1 INOCENTE, PIERDES UNA VIDA" << endl;
					ventana1->draw(spr_oops);
					ventana1->display();
					Sleep(700);
					
				}
		break;


		}
	}
}

void juego::check_personajes() {

	for (int i = 0; i < 2; i++) {

		if (enemigo[i]) {

			if (enemigo[i]->get_seconds() > 5) {

				enemigo[i] = NULL;
				slots_enemigos[i] = false;
				vida--;
				cout << "RECIBISTE UN DISPARO -1 DE VIDA" << endl;
				sound_herida.play();
				ventana1->draw(spr_bang);
				ventana1->display();
				Sleep(700);
			}
		}
	}
	if (inocent) {
		if (inocent->get_seconds() > 5) {
			inocent = NULL;
		}
	}
}

void juego::check_gameover() {

	if (vida == 0) {
		puntaje = (enemigos_eliminados - inocentenes_eliminados) * 10;
		ventana1->clear();
		ventana1->draw(spr_gameover);
		ventana1->display();
		sound_gameover.play();
		cout << "! PERDISTE! Tu puntaje en esta partida es: " <<puntaje<< " puntos"<<endl;
		system("PAUSE");
		exit(1);
	}
}