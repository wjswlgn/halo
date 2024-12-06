#pragma once

#include "Ship.h"
#include <QPushButton>
#include <QWidget>

class Tile : public QPushButton {
	public:
		Tile();
		Tile(QWidget* parent, bool isPlayerShip, int x, int y);
		Ship* getShip();
		void setShip(Ship* ship);
		bool shipexist(); //check if there is ship at that place
		bool isPlayer();
		void validate();
		int getX();
		int getY();
		bool beenHit();
		void setHit(bool hit);
	private:
		Ship* ship;
		bool isPlayerShip;
		int x;
		int y;
		bool isHit;
};
