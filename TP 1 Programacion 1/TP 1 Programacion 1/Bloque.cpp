#include "Bloque.h"

Bloque::Bloque() {

	initializer();

}

void Bloque::initializer() {

	txt_bloque = new Texture();
	spr_bloque = new Sprite();

	txt_bloque->loadFromFile("images/bloque.png");
	spr_bloque->setTexture(*txt_bloque);
	spr_bloque->setScale(0.35f, 0.35f);
	spr_bloque->setPosition(POS_BLOQUE_X, POS_BLOQUE_Y);
	spr_bloque->setOrigin((spr_bloque->getTexture()->getSize().x) / 2.f, spr_bloque->getTexture()->getSize().y / 2.f);

	fuente = new Font();
	fuente->loadFromFile("Font/comic.ttf");

	texto_bloques = new Text();
	texto_bloques->setFont(*fuente);
	texto_bloques->setString(generate_num());
	texto_bloques->setOrigin(texto_bloques->getGlobalBounds().width / 2, texto_bloques->getGlobalBounds().height / 2);
	texto_bloques->setCharacterSize(25);
	texto_bloques->setPosition(POS_BLOQUE_X, POS_BLOQUE_Y - 5);
	texto_bloques->setFillColor(Color::Yellow);

}

void Bloque::set_position(int pos_x, int pos_y) {

	spr_bloque->setPosition(pos_x, pos_y);
	texto_bloques->setPosition(pos_x, pos_y - 5);

}

String Bloque::generate_num() {

	stringstream ss;
	num_bloques = rand() % 999 + 1;
	ss << num_bloques;
	return ss.str();

}

void Bloque::set_num_bloques(int num_ordenado, int i) {

	stringstream ss;
	ss << num_ordenado;
	texto_bloques->setString(ss.str());

}

void Bloque::set_color(bool color) {

	if (color) {
		texto_bloques->setFillColor(Color::Green);
	}
	else {
		texto_bloques->setFillColor(Color::Yellow);
	}
}