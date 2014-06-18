#include "driveball.h"
#include "communication/robcomm.h"
#include "model/gamemodel.h"
#include "skill/gotopositionwithorientation.h"
#include "skill/gotoposition.h"
#include "skill/basic_movement.h"
//#include "skill/rotate.h"
#include "include/globals.h"

namespace Skill
{
    DriveBall::DriveBall(Point targetPoint, double movingDirection)
    {
        targetPosition = targetPoint;
        direction = movingDirection;
        state = moveTowardBall;
    }

    void DriveBall::perform(Robot* robot)
    {
        cout<< "driving ball"<<endl;
        Point ballPosition = GameModel::getModel()->getBallPoint();
        Point goal(-3000, 0);
        double movingDirectionWithoutBall = Measurments::angleBetween(robot->getRobotPosition(), targetPosition);
        double movingDirectionWithBall = Measurments::angleBetween(robot->getRobotPosition(), goal);

        GoToPositionWithOrientation gotoBall(ballPosition, movingDirectionWithBall);
//        GoToPosition driveTheBall(targetPosition);

        GoToPositionWithOrientation driveTheBall(targetPosition, movingDirectionWithBall);
        Stop stop;
//        Rotate rotate(M_PI);

        switch(state)
        {
        case moveTowardBall:
            cout <<"Move toward the ball"<<endl;
            gotoBall.perform(robot);
            if(Measurments::isClose(robot->getRobotPosition(), ballPosition, 110)) {
                state = driveBall;
            }
            break;
        case driveBall:
            cout <<"drive the ball"<<endl;
            driveTheBall.perform(robot);
            if(Measurments::isClose(robot->getRobotPosition(), targetPosition, 110)) {
                state = idiling;
            }
            else if(!Measurments::isClose(robot->getRobotPosition(), targetPosition, 110)) {
                state = driveBall;
            }
            break;
        case idiling:
            cout<<"stoping"<<endl;
            stop.perform(robot);
//            if(!Measurments::isClose(robot->getRobotPosition(), ballPosition, 110)) {
//                state = moveTowardBall;
//            }
            break;
        }
    }
}