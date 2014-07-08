#include "driveball.h"
#include "communication/robcomm.h"
#include "model/gamemodel.h"
#include "skill/gotopositionwithorientation.h"
#include "skill/basic_movement.h"
#include "include/globals.h"
#include "skill/skill.h"
#include "utilities/skillsequence.h"
#include "skill/differential_control/closedloopcontrol.h"

namespace Skill
{
//    static int gotoBallUpdateFn(Skill::Skill& s, Robot* rob)
//	{
//		s = GoToPosition(GameModel::getModel()->getBallPoint(), DriveBall::direction);
//		return -1;
//	}

//	DriveBall::DriveBall(Point targetPoint, double movingDirection)
//	{
//		Point ballPosition = GameModel::getModel()->getBallPoint();
//		direction = movingDirection;

//		mySkillSequence.addSkill( new GoToPosition(ballPosition,direction), gotoBallUpdateFn);
//		mySkillSequence.addSkill( new GoToPosition(targetPoint,direction) );
//		mySkillSequence.addSkill( new Stop() );
//	}

//	void DriveBall::perform(Robot* robot)
//	{
//		cout << "driving ball" <<endl;

//		mySkillSequence.executeOn(robot);
//	}
    DriveBall::DriveBall(Point targetPoint, double finalDirection)
    {
        targetPosition = targetPoint;
        direction = finalDirection;
        state = initial;
    }

    bool DriveBall::perform(Robot* robot)
    {
//        Point goal(-3000, 0);
        GameModel *gm = GameModel::getModel();

        switch(state)
        {
        case initial:
            cout<<"Drive ball initial state"<<endl;
            state = moveTowardBall;
            skill = new GoToPositionWithOrientation (gm->getBallPoint(), Measurments::angleBetween(gm->getBallPoint(), targetPosition));
            break;
        case moveTowardBall:
            cout <<"Move toward the ball"<<endl;
            if(Measurments::isClose(robot->getRobotPosition(), gm->getBallPoint(), 110)) {
                state = driveBall;
                skill = new GoToPositionWithOrientation (targetPosition, direction);
            }
            else if(!Measurments::isClose(robot->getRobotPosition(), gm->getBallPoint(), 400)) {
                state = moveTowardBall;
                skill = new GoToPositionWithOrientation (gm->getBallPoint(), Measurments::angleBetween(gm->getBallPoint(), targetPosition));
            }
            break;
        case driveBall:
            cout <<"drive the ball"<<endl;
            if(Measurments::isClose(robot->getRobotPosition(), targetPosition, 110)) {
                state = idiling;
                skill = new Stop();
            }
            else if(!Measurments::isClose(robot->getRobotPosition(), gm->getBallPoint(), 400)) {
                state = moveTowardBall;
                skill = new GoToPositionWithOrientation (gm->getBallPoint(), Measurments::angleBetween(gm->getBallPoint(), targetPosition));
            }
            break;
        case idiling:
            cout<<"stoping"<<endl;
            if(!Measurments::isClose(robot->getRobotPosition(), gm->getBallPoint(), 110)) {
                state = moveTowardBall;
                skill = new GoToPositionWithOrientation (gm->getBallPoint(), Measurments::angleBetween(gm->getBallPoint(), targetPosition));
            }
            else if(Measurments::isClose(robot->getRobotPosition(), gm->getBallPoint(), 400) && !Measurments::isClose(robot->getRobotPosition(), targetPosition, 110))
            {
                state = driveBall;
                skill = new GoToPositionWithOrientation (targetPosition, direction);
            }
            break;
        }

        skill->perform(robot);

		
        return false;
    }
}
