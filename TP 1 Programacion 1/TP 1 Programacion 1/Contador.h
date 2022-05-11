#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;

//DECLARACION CONSTANTE
const int TIEMPO_JUEGO = 60;

class Contador {

private:
	float tiempo_inicio;
	float tiempo_fin;
	Font* fuente;
	Text* texto_contador;
	bool fin;

public:
	Contador(float tiempoActual);
	void update(float delta_time_seconds); //actualizamos
	Text get_text() { return *texto_contador; }
	void decrease_time() { tiempo_inicio -= 10.0f; } //disminuimos el tiempo del contador
	bool get_fin() { return fin; }

};