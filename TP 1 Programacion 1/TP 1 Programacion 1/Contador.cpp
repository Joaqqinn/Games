#include "Contador.h"

Contador::Contador(float tiempoActual) {

	fuente = new Font();
	fuente->loadFromFile("Font/arial.ttf");

	texto_contador = new Text();
	texto_contador->setFont(*fuente);
	texto_contador->setCharacterSize(60);
	tiempo_inicio = tiempoActual + TIEMPO_JUEGO;
	tiempo_fin = 0.0f;
	fin = false;
}

void Contador::update(float delta_time_seconds) {
	tiempo_fin = delta_time_seconds;

	int seconds = ((int)(tiempo_inicio - tiempo_fin));
	if (seconds >= 0) {
		char buffer[20];
		sprintf_s(buffer, "Tiempo: %i", seconds);
		texto_contador->setString(buffer);
	}
	else {
		texto_contador->setString("El tiempo finalizo...");
		fin = true;
	}
}