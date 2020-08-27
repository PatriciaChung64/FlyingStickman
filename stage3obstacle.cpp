#include "stage3obstacle.h"
#include "coordinate.h"

Stage3Obstacle::Stage3Obstacle(Coordinate *position, std::string name,
                               QColor color, int width, int height, EmptyEntity *parent):
    LeafEntity(position, name), parent(parent),
    color(color), width(width), height(height) {
}

void Stage3Obstacle::update(bool paused, double time_since_last_frame) {
    if (!paused) {
        double timestep = time_since_last_frame/1000.0;
        getPosition()->changeInXCoordinate(velocity);
    }
}

void Stage3Obstacle::render(QPainter &painter) {
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    QBrush brush(color);
    painter.setBrush(brush);

    painter.drawRect(getPosition()->getQtRenderingXCoordinate(), getPosition()->getQtRenderingYCoordinate(), width, height);
}
