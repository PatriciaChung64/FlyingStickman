#pragma once

#include <iostream>
#include <string>
#include <QPixmap>

class Stickman {

public:

    Stickman(std::string size = "small",
            int position = 0,
            double starting_velocity = 0.0);

    virtual ~Stickman();

    //Getter functions
    std::string getSize() { return size; }
    int getXPosition() { return startingXPosition; }
    double getXVelocity() { return xVelocity; }
    double getMovementVelocity() {return movementVelocity; }
    double getWidth() { return width; }
    double getHeight() { return height; }
    virtual QPixmap getPixmap(unsigned int frame);

    //Change and set functions
    void changeSize(std::string new_size) { size = new_size; updateStickman(); }
    void changeXPosition(int new_position) { startingXPosition = new_position; }
    void changeXVelocity(int new_velocity) { xVelocity = new_velocity; }
    virtual void setDimensions();
    virtual void updateStickman();


protected:

    std::string size;
    int startingXPosition;
    double xVelocity;
    double movementVelocity;
    int width;
    int height;

};

