#include <iostream>
#include <string>
#include <cstdlib>
#include "Students.h"

using namespace std;

class Window
{
    public:
        Window(); //default constructor
        Window(Students& studentArrived, int timeIdle); //overloaded constructor
        ~Window(); //destructor
        void incrementIdleTime(); //increment the idle time for the window object
        int getIdleTime(); //get the idle time for the window object
        void setStudent(Students* theStudent); //assign a student to a window
        Students* getStudentAtWindow(); //return the student object (the student at the window)

    private:
        Students *studentAtWindow; //the student at the window receiving help
        int idleTime; //the amount of time the window is idle (there are no students at the window)
};
