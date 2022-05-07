#include "Personaje.h"

Personaje::Personaje(int x, int y) {

	enAscenso = false;
	saltoEnProceso = false;
	posicionTerrenoY = x;
	maxAscensoSaltoY = y;

	anim = new Afichmation("images/spritesheet.png", true, 208, 249);
	anim->setScale(0.6f, 0.6f);
	anim->setPosition(50, 500);
	// Añadimos animaciones con metodo add
	/*1. nombre animacion
	2. indicar los frames usados para la animacion
	3. cantidad de frames por segundo
	4. indicar si la animacion se repite en bucle o no*/
	anim->Add("idle", { 0, 1, 2, 0, 1, 2 }, 5, true);
	anim->Add("run", { 3, 4, 5, 6, 7 }, 8, true);
	anim->Add("jump", { 0, 12, 13, 14 }, 8, true);
	//ejecuto una animacion pasandole el nombre que use 
	anim->Play("idle");
	anim->FlipX(true);
}

void Personaje::initializer() {

	//SOUNDS
	sbuffer_jump.loadFromFile("Sounds/jump.wav");
	sound_jump.setBuffer(sbuffer_jump);
	sound_jump.setVolume(20);
}

void Personaje::update_jump(bool teclaSaltoPresionada, float delta_time_seconds) {

	//Se chequea si se presionó la tecla de salto y si el proceso aún no inició
	if (teclaSaltoPresionada && !saltoEnProceso) {
		saltoEnProceso = true;
		enAscenso = true;
	}

	//Bloque que maneja el salto y su descenso a través del eje y.
	if (saltoEnProceso) {

		//Se controla cuando se llega al maximo de altura de salto
		if (anim->getPosition().y <= posicionTerrenoY - maxAscensoSaltoY) {
			enAscenso = false;
		}

		//Se ejecuta el movimiento hacia arriba o abajo en eje y
		if (enAscenso) {
			anim->move(0.0f, -1.0f * SPEED_Y * delta_time_seconds);
		}
		else {
			anim->move(0.0f, SPEED_Y * delta_time_seconds);
		}

		//Se controla cuando el personaje vuelve a tocar la eje y del terreno
		if (anim->getPosition().y >= posicionTerrenoY) {
			saltoEnProceso = false; //Permite que finalize un ciclo de salto y que comienze uno nuevo
			anim->setPosition(anim->getPosition().x, posicionTerrenoY); //Se fuerza la posicion del personaje en la linea de terreno
		}
	}
	anim->Update();

}

void Personaje::movement(float delta_time_seconds) {

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		exit(1);
	}
	//si presiono la tecla A
	if (Keyboard::isKeyPressed(Keyboard::A) && (anim->getPosition().x > 40)) {
		//ejecuto la animacion "run" para correr y desplazarse a la izquierda
		anim->Play("run");
		//metodo flip voltear el sprite en X
		anim->FlipX(false);
	}
	else {
		anim->Play("idle");
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && (anim->getPosition().x < 760)) {
		anim->Play("run");
		anim->FlipX(true);
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		anim->Play("jump");
		sound_jump.play();
	}

}

void Personaje::drawing(RenderWindow* v) {

	v->draw(*anim);

}