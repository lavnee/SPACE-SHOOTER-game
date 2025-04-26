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

void Game::titleScreen(){
	SDL_Event e;
	while(true){
		app.music = Mix_LoadMUS(bgSound);
		drawBackground();
		draw(app.titleScreen, 0, 0);
		updateScene();
		while(SDL_PollEvent(&e)){
			switch(e.type){
				case SDL_QUIT:
					exit(0);
					break;
				case SDL_KEYDOWN:
					if(e.key.keysym.scancode == SDL_SCANCODE_SPACE){
						initPlayer();
						app.running = true;
						Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
						return;
					}
					if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
						Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
						exit(0);
					}
					if(e.key.keysym.scancode == SDL_SCANCODE_1){
						Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
						if(Mix_PausedMusic()){
							Mix_ResumeMusic();
						}else{
							Mix_PauseMusic();
						}
					}
					break;
			}
		}
	}
}

void Game::endScreen(){
    SDL_Event e;
    bool input = true;
    scoreText << "Score  : " << score;
    Mix_HaltMusic();
    Mix_PlayChannel(-1, app.sounds[GAMEOVER_SOUND], 0);
    while(true){
        drawBackground();
        draw(app.endScreen, 0, 0);
        SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreText.str().c_str(), {255, 255, 255, 0});
        SDL_Texture *scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSurface);
        draw(scoreTXT, 0, 0);
        updateScene();
        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode == SDL_SCANCODE_SPACE){
                        initPlayer();
                        app.running = true;
                        Mix_HaltMusic();
                        Mix_PlayMusic(app.music, -1);
                        Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
                        return;
                    }
                    if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                        Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
                        Mix_PlayMusic(app.music, -1);
                        return;
                    }
                    break;
            }
        }
    }
}
