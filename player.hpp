#pragma once
#include <SDL.h>
#include "Entity.hpp"

class Player:public Entity{
	private:
	    int invincibleTimer;
		int speed, reload;
		bool up, down, left, right, fire;
		bool bulletType;
		bool enterGame;
		bool die;
		int ammo;
	public:
		Player();
		void move();
		void keyDown(SDL_KeyboardEvent*);
		void keyUp(SDL_KeyboardEvent*);
		void updateAmmo(int);
		void setReload(int);
		void setBulletType(int);
		void setEnterStatus(bool);
		void setDieStatus(bool);
		int getAmmo();
		int getReload();
		int getBulletType();
		bool fireStatus();
		bool enterStatus();
		bool died();
		void resetInput();
		void setInvincible(int time);
        bool isInvincible() const;
        void updateInvincible();
};
