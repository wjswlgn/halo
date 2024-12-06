#pragma once

#include "Ship.h"

Ship::Ship() {
    length = 0;
    xCoord = 0;
    yCoord = 0;
    horizontal = false;
    health = 0;
    text = "-";
}

Ship::Ship(int newLength, int newX, int newY, bool direction, bool isPlayerShip, QString newText) {
    length = newLength;
    xCoord = newX;
    yCoord = newY;
    horizontal = direction;
    health = newLength;
    text = newText;
}

int Ship::getLength() { return length; }
int Ship::getX() { return xCoord; }
int Ship::getY() { return yCoord; }
void Ship::setLength(int newLength) { length = newLength; }
void Ship::setX(int newX) { xCoord = newX; }
void Ship::setY(int newY) { yCoord = newY; }
bool Ship::getDirection() { return horizontal; }
void Ship::setDirection(bool newDirection) { horizontal = newDirection; }
void Ship::setHealth(int newHealth) { health = newHealth; }
int Ship::getHealth() { return health; }
QString Ship::getText() { return text; }
void Ship::setText(QString newText) { text = newText; }

Carrier::Carrier(int newX, int newY, bool direction, bool isPlayerShip)
    : Ship(5, newX, newY, direction, isPlayerShip, "C") {
}

QString Carrier::getText() {
    return "Carrier - " + text; 
}
