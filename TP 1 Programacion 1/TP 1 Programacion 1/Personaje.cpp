#include "Personaje.h"

Personaje::Personaje(int x, int y) {

	enAscenso = false;
	saltoEnProceso = false;
	posicionTerrenoY = x;
	maxAscensoSaltoY = y;

	anim = new Afichmation("images/spritesheet.png", true, 104, 125);
	anim->setScale(0.6f, 0.6f);
	anim->setPosition(50, 495);
	//DEFINICION DE ESTADOS DE ANIM
	anim->Add("idle", { 0, 1, 2, 0, 1, 2 }, 5, true);
	anim->Add("run", { 3, 4, 5, 6, 7 }, 8, true);
	anim->Add("jump", { 12 }, 10, true);
	anim->Play("idle");
	anim->FlipX(true);

	initializer();

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
		anim->Play("jump");

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
	if (Keyboard::isKeyPressed(Keyboard::A) && (anim->getPosition().x > 40)) {
		anim->Play("run");
		anim->FlipX(false);
		anim->move(-1.0f * SPEED_X * delta_time_seconds, 0.0f);
	}
	else {
		anim->Play("idle");
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && (anim->getPosition().x < 760)) {
		anim->Play("run");
		anim->FlipX(true);
		anim->move(1.0f * SPEED_X * delta_time_seconds, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		sound_jump.play();
	}

}

void Personaje::drawing(RenderWindow* v) {

	
	v->draw(*anim);

}

FloatRect Personaje::get_bounds() {

	return anim->getGlobalBounds();

}