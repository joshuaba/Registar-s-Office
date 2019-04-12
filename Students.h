#include <iostream>
#include <string>

using namespace std;

class Students
{
    public:
        Students(); //default constructor
        Students(int windowTimeRequired, int arrivalInLineTime); //overloaded constructor
        ~Students();
        void setTimeRequiredAtWindow(int windowTimeRequired); //set the timeReq member variable
        void setTimeArrivedAtWindow(int arrivalAtWindowTime);
        void setTimeArrivedInLine(int arrivalInLineTime);
        int getTimeReqAtWindow(); //get the timeReq member variable
        int getTimeArrivedAtWindow(); //get the time the student arrived at the window
        int getTimeArrivedInLine(); //get the time the student arrived in line
        int getTimeFinishedAtWindow(); //at what time did the student finish at the window?
        int getWaitTime(); //get the amount of time the student waited in line (the queue)

    private:
        int timeReqAtWindow; //time required at the window needed by the student
        int timeArrivedAtWindow; //the time at which the student arrived at the window
        int timeArrivedInLine; //the time at which the student arrived in the line (queue)
};
