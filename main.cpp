#include "Game.h"

int main()
{
												// Initialize random speed
	srand(static_cast<unsigned>(time(0)));

												// Init game object
	Game game;

												// Game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

												// End game
	return 0;
}