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

void Game::enterAnimation(){
	prepareScene();
	drawBackground();
	player.setX(player.getX() - 15);
	draw(player.getTexture(), player.getX(), player.getY());
	if(player.getX() < 150){
		player.setEnterStatus(true);
	}
	updateScene();
}

void Game::initGame(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		exit(-1);
	}
	app.window = SDL_CreateWindow("Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if(!app.window){
		cout << "Could not create window : " << SDL_GetError() << endl;
		exit(-1);
	}
	SDL_Surface *sf = IMG_Load(icon);
	SDL_SetWindowIcon(app.window, sf);
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	if(!app.renderer){
		cout << "Could not create renderer : " << SDL_GetError() << endl;
		exit(-1);
	}
	if(!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))){
		cout << "Could not initialize SDL Image : " << SDL_GetError() << endl;
		exit(-1);
	}
	if(TTF_Init() != 0){
		cout << "Could not initialize TTF : " << TTF_GetError() << endl;
		exit(-1);
	}
	font = TTF_OpenFont("fonts/myriadProRegular.ttf", 22);
	score = 0;
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0){
		cout << "Could not initialize SDL Mixer : " << Mix_GetError() << endl;
		exit(-1);
	}
	app.sounds[GAMEOVER_SOUND] = Mix_LoadWAV(loseSound);
    if (app.sounds[GAMEOVER_SOUND] == NULL) {
    std::cerr << "Failed to load gameover sound: " << Mix_GetError() << std::endl;
    exit(-1);
    }
	Mix_AllocateChannels(soundChannel);
	app.music = Mix_LoadMUS(bgSound);
	app.sounds[SOUND_FIRE] = Mix_LoadWAV(fireSound);
	app.sounds[SOUND_EXPLOSION] = Mix_LoadWAV(explosionSound);
	app.sounds[SOUND_BUTTON] = Mix_LoadWAV(btSound);

	app.background = loadTexture(backgroundTexture);
	backgroundX = 0;
	app.titleScreen = loadTexture(titleScreenTexture);
	app.endScreen = loadTexture(endScreenTexture);
	app.running = false;

	file.open("scores.txt", ios::in);
	file >> highScore;

	enemySpawnTimer = 60;

	player.setIdentity(pPlane);
	player.setTexture(loadTexture(playerTexture));

	playerBullet.setDX(playerBulletSpeed);
	playerBullet.updateHP(bulletHP);
	playerBullet.setIdentity(normalBullet);
	playerBullet.setTexture(loadTexture(waveBulletTexture));

	enemyBullet.setDX(enemyBulletSpeed);
	enemyBullet.setHP(1);
	enemyBullet.setIdentity(eBullet);
	enemyBullet.setTexture(loadTexture(enemyBulletTexture));
	enemyFire = 0;

	debris.setHP(1);
	debris.setIdentity(shipDebris);
	debrisTexture[0] = loadTexture("sprites/debris1.png");
	debrisTexture[1] = loadTexture("sprites/debris2.png");
	debrisTexture[2] = loadTexture("sprites/debris3.png");
	debrisTexture[3] = loadTexture("sprites/debris4.png");

	explosion.setTexture(loadTexture(explosionTexture));

	Mix_PlayMusic(app.music, -1);
	gameTicks = 0;
}

void Game::initPlayer(){
	player.setX(WIDTH / 2);
	player.setY(HEIGHT / 2 - 50);
	player.setHP(10);
	player.setDieStatus(false);
	player.setEnterStatus(false);
	player.setBulletType(normalBullet);
	player.resetInput();
}

void Game::getInput(){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYUP:
				player.keyUp(&e.key);
				break;
			case SDL_KEYDOWN:
				player.keyDown(&e.key);
				break;
		}
	}
}
