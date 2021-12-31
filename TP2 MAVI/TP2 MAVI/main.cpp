#include "SFML/Graphics.hpp"
#include <iostream>
#include "game.h"

using namespace sf;
using namespace std;

int main(int argc, char* args[]) {

	srand(time(NULL));

	game  partida1({ 1280, 1024 }, "Asteroids");

	return 0;
}