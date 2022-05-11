#pragma once
#include <sstream>
#include "SFML/Graphics.hpp"

//DECLARACION DE CONSTANTES
const int POS_BLOQUE_X = 60;
const int POS_BLOQUE_Y = 360;

using namespace sf;
using namespace std;

class Bloque {

private:
	Texture* txt_bloque;
	Sprite* spr_bloque;
	Font* fuente;
	Text* texto_bloques;
	int num_bloques;

public:
	Bloque();
	void initializer(); //iniciamos las variables
	String generate_num(); //generamos los numeros y los transformamos para pasarlos al texto
	Sprite get_sprite() { return *spr_bloque; }
	Text get_text() { return *texto_bloques; }
	int get_num_bloques() { return num_bloques; } //obtenemos los numeros que generamos
	void set_num_bloques(int num_ordenado, int i); //modificamos los numeros para pasarlos en orden
	void set_position(int pos_x, int pos_y); //definimos la posicion de los  bloques y el texto que aparece encima
	void set_color(bool color); //modificamos el color del texto

};