#include "SFML/Graphics.hpp"
#include <iostream>
#include "juego.h"

using namespace sf;
using namespace std;

int main(int argc, char* args[]) {

	srand(time(NULL));

	juego  partida1({800, 600}, "Juego Tiros");

	return 0;
}
