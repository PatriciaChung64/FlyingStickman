#ifndef STAGE3OBSTACLE_H
#define STAGE3OBSTACLE_H

#include <memory>
#include "emptyentity.h"
#include "leafentity.h"

//new leaf entity stage 3 obstacle, has additional parameters width, height and color
//keeps a copy of parent to notify parent when child needs to be removed

class Stage3Obstacle : public LeafEntity {
    friend class StageMemento;
    friend class Stage3Tester;
public:
    Stage3Obstacle(Coordinate *position, std::string name,
                   QColor color, int width, int height, EmptyEntity *parent);

    int getWidth() { return width; }
    int getHeight() { return height; }
    void deleteSelf() { parent->removeChild(this); }

    void update(bool paused, double time_since_last_frame);
    void render(QPainter &painter);

protected:
    EmptyEntity *parent;
    QColor color;
    int width;
    int height;
};

#endif // STAGE3OBSTACLE_H
