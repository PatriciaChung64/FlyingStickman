#include "stagegoal.h"
#include "coordinate.h"

StageGoal::StageGoal(Coordinate *position, std::string name):
    LeafEntity (position, name) {
}

void StageGoal::update(bool paused, double time_since_last_frame) {
    if (!paused) {
        double timestep = time_since_last_frame/1000.0;
        getPosition()->changeInXCoordinate(velocity);
    }
}

void StageGoal::render(QPainter &painter) {
    //goal is an invisible wall, nothing to render
}
