#pragma once

#include "Tile.h"

Tile::Tile() {
	ship = nullptr;
	x = 0;
	y = 0;
	isHit = false;
	isPlayerShip = true;
}

Tile::Tile(QWidget* parent, bool isPlayerShip, int x, int y) : QPushButton(parent) {
	ship = nullptr;
	this->isPlayerShip = isPlayerShip;
	this->x = x;
	this->y = y;
	isHit = false;
}

bool Tile::shipexist() {
	return ship != nullptr;
}

Ship* Tile::getShip() {
	return ship;
}
void Tile::setShip(Ship* Ship) {
	this->ship = Ship;
}

bool Tile::isPlayer() {
	return isPlayerShip;
}

int Tile::getX() {
	return x;
}

int Tile::getY() {
	return y;
}

bool Tile::beenHit() {
	return isHit;
}

void Tile::setHit(bool hit) {
	isHit = hit;
}
