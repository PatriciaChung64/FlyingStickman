#ifndef STAGEGOAL_H
#define STAGEGOAL_H

#include "leafentity.h"

//a particular type of leaf entity that signifies the end of a stage
//every stage's root's last child will be stage goal,
//and collision for goal is simply tested for x overlap

class StageGoal : public LeafEntity {
public:
    StageGoal(Coordinate *position, std::string name = "Goal");

    void update(bool paused, double time_since_last_frame);
    void render(QPainter &painter);
};

#endif // STAGEGOAL_H
