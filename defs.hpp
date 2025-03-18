#pragma once
#define WIDTH 1024
#define HEIGHT 500

#define playerTexture "pic/playerShip.png"
#define playerHP 10
#define playerBulletSpeed 30

#define enemyTexture "pic/enemyShip.png"
#define enemyHP 5
#define enemySpeed -5
#define enemyBulletSpeed -15

#define bulletHP 1

#define normalBulletTexture "pic/blueLaser.png"
#define waveBulletTexture "pic/wave.png"
#define enemyBulletTexture "pic/redLaser.png"


#define powerUpSPD 6
#define bonusHPTexture "pic/health.png"
#define enchanceAttackTexture "pic/power.png"

#define explosionTexture "pic/explosion.png"

#define titleScreenTexture "pic/titleScreen.png"
#define endScreenTexture "pic/endScreen.png"
#define icon "pic/icon.png"
#define backgroundTexture "pic/background.jpg"

#define soundChannel 5
#define fireSound "sound/laser.ogg"
#define explosionSound "sound/explosion.ogg"
#define bgSound "sound/background.ogg"
#define btSound "sound/button.ogg"
#define loseSound "sound/lose.ogg"

enum{
	pPlane,
	ePlane,
	ePlane2,
	eBullet,
	shipDebris,
	bonusHP,
	enchanceATK,
};

enum{
	normalBullet,
	waveBullet
};

enum{
	CH_MUSIC,
	CH_MENU,
	CH_PLAYER,
	CH_ENEMY,
	CH_OTHER
};

enum{
	SOUND_FIRE,
	SOUND_EXPLOSION,
	SOUND_BUTTON,
	GAMEOVER_SOUND
};
