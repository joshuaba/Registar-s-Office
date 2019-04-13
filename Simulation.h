#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "Window.h"
#include "QueueGeneric.h"

using namespace std;

class Simulation
{
    public:
        Simulation(); //default constructor
        Simulation(string inputFileToBeProcessed); //overloaded constructor
        ~Simulation(); //destructor
        void processFile(string fileToProcess); //process the input file and initialize appropriate member variables
        void addStudent(Students theStudent); //populate the studentsQueue with the Student object passed in as the argument
        void processStudents(); //contains much of the higher-level implementation of the Simulation. Processes student from the line and saves the information needed to compute the statistics
        bool isAllWorkComplete(); //checks to see if all work is complete (i.e. all students have been processed) before computing the statistics
        Students* getStudentCompletedArray(); //get access to the studentCompletedArray
        void processAggregates(); //process the aggregate member variables/compute the stats
        void printAggregates(); //print out the aggregates once they are computed
        void addStudentsToStudentsQueue(); //add the students in the listOfStudents to the studentsQueue

    private:
        QueueGeneric<Students> *studentsQueue = new QueueGeneric<Students>(); //initialize the queue to hold 10 students. It will resize if needed
        vector<Students> listOfStudents;
        Window* windowArray;
        int sizeOfWindowArray; //the size of the window array. Basically the number of windows open
        Students* studentCompletedArray; //once the students have been helped at the window, they will be passed into this studentCompletedArray, which we need to compute the statistics
        int sizeOfStudentCompletedArray; //the size of the student completed array
        int currentTimeTick = 0; //record the current time tick we are at

        //following variables are needed to compute the statistics
        int meanStudentWaitTime = 0;
        int studentWaitTimeSum = 0;
        int medianStudentWaitTime = 0;
        int longestStudentWaitTime = 0;
        int totalStudentsWaitingOver10Minutes = 0;
        int meanWindowIdleTime = 0;
        int longestWindowIdleTime = 0;
        int totalWindowsIdleOver5Minutes = 0;
        int counter = 0;
        int totalWindowIdleTime = 0;

        //int windowsOpen; //number of windows open
        //int timePassed; //the time passed (clock ticks)
};
