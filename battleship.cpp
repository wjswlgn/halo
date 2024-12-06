#pragma once

#include "Battleship.h"

Battleship::Battleship(QWidget* parent)     //constructor
	: QMainWindow(parent)
{
	std::srand(std::time(nullptr));
	ui.setupUi(this);
	this->setGeometry(0, 0, 1100, 650);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Tile* button = new Tile(this, true, i, j);
			button->setText("-");
			button->setGeometry(50 * i, 10 + 50 * j, 55, 55);
			connect(button, &QPushButton::released, this, &Battleship::handleButton);
			playerBoard[i][j] = button;
			Tile* button2 = new Tile(this, false, i, j);
			button2->setText("-");
			button2->setGeometry(550 + 50 * i, 10 + 50 * j, 55, 55);
			connect(button2, &QPushButton::released, this, &Battleship::handleButton);
			enemyBoard[i][j] = button2;
		}
	}
	placeEnemyShips();
	isPlayerTurn = true;
	text = new QLineEdit(this);
	text->setText("Choose a player square");
	text->setReadOnly(true);
	text->move(550, 550);
	text->setFixedWidth(500);
	text->setFont(QFont("Arial", 20));
	shipsAdded = 0;
	playerShips[0] = new Ship(5, 0, 0, true, true, "C");
	playerShips[1] = new Ship(4, 0, 0, true, true, "B");
	playerShips[2] = new Ship(3, 0, 0, true, true, "D");
	playerShips[3] = new Ship(3, 0, 0, true, true, "S");
	playerShips[4] = new Ship(2, 0, 0, true, true, "P");
	enemyShips[0] = new Ship(5, 0, 0, true, false, "C");
	enemyShips[1] = new Ship(4, 0, 0, true, false, "B");
	enemyShips[2] = new Ship(3, 0, 0, true, false, "D");
	enemyShips[3] = new Ship(3, 0, 0, true, false, "S");
	enemyShips[4] = new Ship(2, 0, 0, true, false, "P");
}

Battleship::~Battleship()       //destructor
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			delete playerBoard[i][j];
			delete enemyBoard[i][j];
		}
	}
}

// Fire at tile
void Battleship::fire(Tile* board[10][10], int x, int y) {
	if (board[x][y]->shipexist()) {
		board[x][y]->setText("X"); // Hit
	}
	else {
		board[x][y]->setText("O"); // Miss
	}
}

// Check game over
bool Battleship::isGameOver(Tile* board[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j]->shipexist() && board[i][j]->text() != "X") {
				return false;
			}
		}
	}
	return true;

}

bool Battleship::isHit(Tile* click) {
	QString tileText = click->text();
	return (tileText == "X" || tileText == "O");
}


void Battleship::handleButton() {
	if (shipsAdded < 5) {
		if (dynamic_cast<Tile*>(QObject::sender())->isPlayer()) {
			if (click1 == nullptr) {
				click1 = dynamic_cast<Tile*>(QObject::sender());
				text->setText("Ship starting at " + QString::number(click1->getX()) + ", " + QString::number(click1->getY()));
			}
			else {
				click2 = dynamic_cast<Tile*>(QObject::sender());
				if (click1->getX() == click2->getX() && click1->getY() > click2->getY()) {
					if (click1->getY() - playerShips[shipsAdded]->getLength() >= -1) {
						bool validPlace = true;
						for (int i = 0; i < playerShips[shipsAdded]->getLength(); i++) {
							if (playerBoard[click1->getX()][click1->getY() - i]->getShip() != nullptr) {
								validPlace = false;
							}
						}
						if (validPlace) {
							for (int i = 0; i < playerShips[shipsAdded]->getLength(); i++) {
								playerBoard[click1->getX()][click1->getY() - i]->setShip(playerShips[shipsAdded]);
								playerBoard[click1->getX()][click1->getY() - i]->setText(playerShips[shipsAdded]->getText());
							}
							shipsAdded++;
							text->setText("Ship placed");
							if (shipsAdded >= 5) {
								text->setText("All ships placed, player turn");
							}
						}
						else {
							text->setText("Invalid placement, try again");
						}
					}
					else {
						text->setText("Invalid placement, try again");
					}
				}
				else if (click1->getX() == click2->getX() && click1->getY() < click2->getY()) {
					if (click1->getY() + playerShips[shipsAdded]->getLength() < 11) {
						bool validPlace = true;
						for (int i = 0; i < playerShips[shipsAdded]->getLength(); i++) {
							if (playerBoard[click1->getX()][click1->getY() + i]->getShip() != nullptr) {
								validPlace = false;
							}
						}
						if (validPlace) {
							for (int i = 0; i < playerShips[shipsAdded]->getLength(); i++) {
								playerBoard[click1->getX()][click1->getY() + i]->setShip(playerShips[shipsAdded]);
								playerBoard[click1->getX()][click1->getY() + i]->setText(playerShips[shipsAdded]->getText());
							}
							shipsAdded++;
							text->setText("Ship placed");
							if (shipsAdded >= 5) {
								text->setText("All ships placed, player turn");
							}
						}
						else {
							text->setText("Invalid placement, try again");
						}
					}
					else {
						text->setText("Invalid placement, try again");
					}
				}
				else if (click1->getY() == click2->getY() && click1->getX() > click2->getX()) {
					if (click1->getX() - playerShips[shipsAdded]->getLength() >= -1) {
						bool validPlace = true;
						for (int i = 0; i < playerShips[shipsAdded]->getLength(); i++) {
							if (playerBoard[click1->getX() - i][click1->getY()]->getShip() != nullptr) {
								validPlace = false;
							}
						}
						if (validPlace) {
							for (int i = 0; i < playerShips[shipsAdded]->getLength(); i++) {
								playerBoard[click1->getX() - i][click1->getY()]->setShip(playerShips[shipsAdded]);
								playerBoard[click1->getX() - i][click1->getY()]->setText(playerShips[shipsAdded]->getText());
							}
							shipsAdded++;
							text->setText("Ship placed");
							if (shipsAdded >= 5) {
								text->setText("All ships placed, player turn");
							}
						}
						else {
							text->setText("Invalid placement, try again");
						}
					}
					else {
						text->setText("Invalid placement, try again");
					}
				}
				else if (click1->getY() == click2->getY() && click1->getX() < click2->getX()) {
					if (click1->getX() + playerShips[shipsAdded]->getLength() < 11) {
						bool validPlace = true;
						for (int i = 0; i < playerShips[shipsAdded]->getLength(); i++) {
							if (playerBoard[click1->getX() + i][click1->getY()]->getShip() != nullptr) {
								validPlace = false;
							}
						}
						if (validPlace) {
							for (int i = 0; i < playerShips[shipsAdded]->getLength(); i++) {
								playerBoard[click1->getX() + i][click1->getY()]->setShip(playerShips[shipsAdded]);
								playerBoard[click1->getX() + i][click1->getY()]->setText(playerShips[shipsAdded]->getText());
							}
							shipsAdded++;
							text->setText("Ship placed");
							if (shipsAdded >= 5) {
								text->setText("All ships placed, player turn");
							}
						}
						else {
							text->setText("Invalid placement, try again");
						}
					}
					else {
						text->setText("Invalid placement, try again");
					}
				}
				else {
					text->setText("Invalid placement, try again");
				}
				click1 = nullptr;
				click2 = nullptr;
			}
		}
		else {
			text->setText("Choose your own tile");
		}

	}

	Tile* tile = dynamic_cast<Tile*>(QObject::sender());
	if (!tile->isPlayer() && isPlayerTurn) {
		if (isHit(tile)) {
			text->setText("Choose another tile.");
			return;
		}
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				if (enemyBoard[i][j] == tile) {
					fire(enemyBoard, i, j);
					break;
				}
			}
		}
		if (isGameOver(enemyBoard)) {
			text->setText("Player Wins!");
			return;
		}
		isPlayerTurn = false;
		text->setText("Enemy Turn");
	}
	else if (tile->isPlayer() && !isPlayerTurn) {
		int x, y;
		do {
			x = rand() % 10;
			y = rand() % 10;
		} while (playerBoard[x][y]->text() != "-");

		fire(playerBoard, x, y);

		if (isGameOver(playerBoard)) {
			text->setText("You Lose");
			return;
		}
		isPlayerTurn = true;
		text->setText("Player Turn");
	}

}




void Battleship::placeEnemyShips() {
	for (int i = 0; i < 5; i++) {
		Ship* ship = new Ship();
		if (i == 0) {
			ship->setLength(5);
			ship->setHealth(5);
			ship->setText("C");
		}
		else if (i == 1) {
			ship->setLength(4);
			ship->setHealth(4);
			ship->setText("B");
		}
		else if (i == 2) {
			ship->setLength(3);
			ship->setHealth(3);
			ship->setText("D");
		}
		else if (i == 3) {
			ship->setLength(3);
			ship->setHealth(3);
			ship->setText("S");
		}
		else {
			ship->setLength(2);
			ship->setHealth(2);
			ship->setText("P");
		}
		while (true) {
			int x = rand() % 10;
			int y = rand() % 10;
			bool horizontal = (rand() % 2 == 0);
			bool isValid = true;
			if (horizontal) {
				if (x + ship->getLength() - 1 < 10) {
					for (int j = 0; j < ship->getLength(); j++) {
						if (enemyBoard[x + j][y]->getShip() != nullptr) {
							isValid = false;
						}
					}
					if (isValid) {
						enemyShips[i] = ship;
						for (int j = 0; j < ship->getLength(); j++) {
							enemyBoard[x + j][y]->setText(ship->getText());
							enemyBoard[x + j][y]->setShip(ship);
						}
						break;
					}
				}
			}
			else {
				if (y + ship->getLength() - 1 < 10) {
					for (int j = 0; j < ship->getLength(); j++) {
						if (enemyBoard[x][y + j]->getShip() != nullptr) {
							isValid = false;
						}
					}
					if (isValid) {
						for (int j = 0; j < ship->getLength(); j++) {
							enemyBoard[x][y + j]->setText(ship->getText());
							enemyBoard[x][y + j]->setShip(ship);
						}
						break;
					}
				}
			}
		}
	}
}
