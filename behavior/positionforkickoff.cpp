#include "positionforkickoff.h"

PositionForKickoff::PositionForKickoff(const ParameterList &list)
	: move_skill(nullptr)
{
    UNUSED_PARAM(list);
    gm = GameModel::getModel();
    bp = gm->getBallPoint();
    bp_updated = true;
}

PositionForKickoff::~PositionForKickoff()
{
	delete move_skill;
}

void PositionForKickoff::perform(Robot * robot)
{
    #if TRACE
        cout << endl<<"Performing Behavior::PositionForKickoff" << endl;
    #endif

    gm = GameModel::getModel();

    if(!Measurments::isClose(gm->getBallPoint(),bp))
    {
        bp = gm->getBallPoint();
        bp_updated = true;
    }

    float ball_direction = Measurments::angleBetween(robot->getRobotPosition(),bp);

    float goal_x = gm->getMyGoal().x;

    switch(robot->getID())
    {
        case 0:
            move_point = Point(goal_x*0.1,500);
            orientation= -M_PI/2;
            break;
        case 1:
            move_point = Point(goal_x*0.1,-500);
            orientation= M_PI/2;
            break;
        case 2:
            move_point = Point(goal_x/2,800);
            orientation= ball_direction;
            break;
        case 3:
            move_point = Point(goal_x/2,0);
            orientation= ball_direction;
            break;
        case 4:
            move_point = Point(goal_x/2,-800);
            orientation = ball_direction;
            break;
        case 5:
            move_point = Point(gm->getMyGoal());
            orientation= ball_direction;
    }

    if(bp_updated)
    {
		delete move_skill;
        #if SIMULATED==1
            move_skill = new Movement::GoToPosition(move_point, orientation, true);
        #else
            move_skill = new Movement::GoToPosition(move_point, orientation, true);
        #endif

        bp_updated = false;
        //cout << "BP UPDATED" << endl;
    }

    move_skill->perform(robot);
}
