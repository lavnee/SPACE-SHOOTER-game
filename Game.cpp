#include "Game.hpp"
using namespace std;

void Game::start(){
	initGame();
	while(true){
		titleScreen();
		while(app.running){
			if(player.enterStatus() == false){
				enterAnimation();
				continue;
			}
			prepareScene();
			drawBackground();
			if(player.getHP() > 0){
				getInput();
			}
			updateEntities();
			updateHUD();
			updateScene();
		}
	}
}
