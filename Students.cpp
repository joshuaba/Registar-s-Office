#include <iostream>
#include <cstdlib>
#include <string>
#include "Students.h"

using namespace std;


Students::Students()
{
    timeReqAtWindow = 0;
}

Students::Students(int windowTimeRequired, int arrivalInLineTime)
{
    timeReqAtWindow = windowTimeRequired; //set the timeReq variable to the argument TR
    //timeArrivedAtWindow = arrivalAtWindowTime; //set the timeArrivedAtWindow variable to the argument arrivalAtWindowTime
    timeArrivedInLine = arrivalInLineTime; //set the timeArrivedInLine variable to the argument arrivalInLineTime
}

Students::~Students()
{
    timeReqAtWindow = 0;
    timeArrivedAtWindow = 0;
    timeArrivedInLine = 0;
}

void Students::setTimeRequiredAtWindow(int windowTimeRequired)
{
    timeReqAtWindow = windowTimeRequired; //set the timeReq variable to the argument TR passed in
}

void Students::setTimeArrivedAtWindow(int arrivalAtWindowTime)
{
    timeArrivedAtWindow = arrivalAtWindowTime;
}

void Students::setTimeArrivedInLine(int arrivalInLineTime)
{
    timeArrivedInLine = arrivalInLineTime;
}

int Students::getTimeReqAtWindow()
{
    return timeReqAtWindow; //return the timeReq member variable
}

int Students::getTimeArrivedAtWindow()
{
    return timeArrivedAtWindow;
}

int Students::getTimeArrivedInLine()
{
    return timeArrivedInLine;
}

int Students::getTimeFinishedAtWindow()
{
    return timeArrivedAtWindow + timeReqAtWindow;
}

int Students::getWaitTime()
{
    return timeArrivedAtWindow - timeArrivedInLine;
}
