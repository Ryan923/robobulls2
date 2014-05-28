#include "goforward.h"
#include "communication/robcomm.h"
#include "Model/gamemodel.h"
#include "Model/robot.h"
#include "skill/closedloopcontrol.h"

GoForward::GoForward()
{

}

void GoForward::perform(Robot *robot)
{
    robComm *nxtbee = robComm::getnxtbee();

    nxtbee->sendVels(30, 30, robot->getID());
}
