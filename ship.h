#pragma once
#include <QString>
#include <string>


class Ship {
public:
    Ship();
    Ship(int newLength, int newX, int newY, bool direction, bool isPlayerShip, QString newText);
    virtual ~Ship() = default;

    virtual int getLength();
    virtual int getX();
    virtual int getY();
    virtual void setLength(int newLength);
    virtual void setX(int newX);
    virtual void setY(int newY);
    virtual bool getDirection();
    virtual void setDirection(bool newDirection);
    virtual int getHealth();
    virtual void setHealth(int newHealth);
    virtual QString getText();
    virtual void setText(QString newText);

protected:
    int length;
    int xCoord;
    int yCoord;
    bool horizontal; 
    int health;
    QString text;
};

class Carrier : public Ship {
public:
    Carrier(int newX, int newY, bool direction, bool isPlayerShip);
    QString getText() override; 
};
