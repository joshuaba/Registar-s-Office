#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Simulation.h"

using namespace std;

Simulation::Simulation() //default constructor
{
    studentsQueue = NULL;
    windowArray = NULL;
    sizeOfWindowArray = 0;
    studentCompletedArray = NULL;
    sizeOfStudentCompletedArray = 0;
    currentTimeTick = 0;

}

Simulation::Simulation(string inputFileToBeProcessed)
{
    cout << "Getting here!" << endl;
    processFile(inputFileToBeProcessed);
}

void Simulation::processFile(string fileToProcess)
{
    cout << "Top of method" << endl;
    ifstream inputStream;
    inputStream.open(fileToProcess);
    cout << "Getting here" << endl;
    string valueRead;
    int currentTimeTick = 0; //what is the current time tick we are at
    int fileLineNum = 0; //the current line number of the file
    int nextTimeTickLine = 2; //I need this so I can decipher which lines correspond to time ticks and which lines correspond to students entering the line/time required at the window
    while(!inputStream.eof())
    {
        fileLineNum++; //I want to start off the line number of the file as 1
        getline(inputStream, valueRead);
        int numberRead = stoi(valueRead); //convert the integer (read in as a string) to an int object
        cout << numberRead << endl;

        if(fileLineNum == 1)
        {
            windowArray = new Window[numberRead]; //populate my window array with the number of windows open read from the file
        }

        else if (fileLineNum == nextTimeTickLine)//the line number is not equal to 1, so all other integer values correspond to either a clock tick time, the number of students arriving in line, and the times each student requires at the window
        {
            currentTimeTick = numberRead;
        }

        else if(fileLineNum == nextTimeTickLine + 1)
        {
            nextTimeTickLine = nextTimeTickLine + 1 + fileLineNum;
        }

        else //the value is a student time required at window value
        {
            cout << "Got here A!" << endl;
            addStudent(Students(numberRead, currentTimeTick)); //add a student to the studentsQueue queue, initializing the student object as requiring numberRead minutes at the window and entering the queue at
            cout << "Got here B!" << endl;
        }
    }

    sizeOfStudentCompletedArray = studentsQueue->getSize();

    inputStream.close(); //close the input stream
}

/*
Simulation::Simulation(int numOfWindowsOpen)
{
    windowsOpen = numOfWindowsOpen;
    timePassed = 0;
    studentsQueue = new QueueGeneric<Students>(50);
}
*/

Simulation::~Simulation()
{
    delete studentsQueue;
    delete [] windowArray;
    delete [] studentCompletedArray;
}

void Simulation::addStudent(Students theStudent)
{
cout << "Getting here A!" << endl;
    studentsQueue->insert(theStudent);
cout << "Getting here B!" << endl;
}

void Simulation::processStudents()
{
    studentCompletedArray = new Students[studentsQueue->getSize()]; //initalize the completed student array to be an array of Students with the same size as the size of the student queue
    while(true)
    {
        for (int i = 0; i < sizeOfWindowArray; ++i)
        {
            Students *studentAtWindow = windowArray[i].getStudentAtWindow();
            if(studentAtWindow != NULL)
            {
                if(studentAtWindow->getTimeFinishedAtWindow() <= currentTimeTick)
                {
                    windowArray[i].setStudent(NULL);
                    studentCompletedArray[i] = *studentAtWindow;
                }
            }
        }

        for(int i = 0; i < sizeOfWindowArray; ++i)
        {
            if(windowArray[i].getStudentAtWindow() == NULL)
            {
                if(studentsQueue->getSize() != 0)
                {
                    Students studentAtFront = studentsQueue->front();
                    Students *nextStudentInLine = &studentAtFront;
                    windowArray[i].setStudent(nextStudentInLine);
                    studentsQueue->remove();
                }
                else //no more students are waiting in line
                {
                    windowArray[i].incrementIdleTime();
                }

            }
        }

        if(isAllWorkComplete())
        {
            processAggregates();
            printAggregates();
            break;
        }
    }
}

bool Simulation::isAllWorkComplete()
{
    if(studentsQueue->getSize() > 0)
        return false;
    for (int i = 0; i < sizeOfWindowArray; ++i)
    {
        if (windowArray[i].getStudentAtWindow() != NULL)
            return false;
    }

    return true;
}

void Simulation::processAggregates()
{
    for (int i = 0; i < sizeOfStudentCompletedArray; ++i)
    {
        int studentWaitTime = studentCompletedArray[i].getWaitTime();
        studentWaitTimeSum+=studentWaitTime;

        if(studentWaitTime > longestStudentWaitTime)
            longestStudentWaitTime = studentWaitTime;

        if(studentWaitTime > 10)
            totalStudentsWaitingOver10Minutes++;
    }

    meanStudentWaitTime = studentWaitTimeSum / sizeOfStudentCompletedArray;

    for (int i = 0; i < sizeOfWindowArray; ++i)
    {
        int windowIdleTime = windowArray[i].getIdleTime();
        totalWindowIdleTime += windowIdleTime;

        if(windowIdleTime > longestWindowIdleTime)
            longestWindowIdleTime = windowIdleTime;

        if(windowIdleTime > 5)
            totalWindowsIdleOver5Minutes++;
    }
}

void Simulation::printAggregates()
{
    cout << "Mean student wait time: " << meanStudentWaitTime << endl
         << "Longest student wait time: " << longestStudentWaitTime << endl
         << "The number of students waiting in line for over 10 minutes: " << totalStudentsWaitingOver10Minutes << endl
         << "Mean window idle time: " << meanWindowIdleTime << endl
         << "Longest window idle time: " << longestWindowIdleTime << endl
         << "Number of windows idle for over 5 minutes: " << totalWindowsIdleOver5Minutes << endl;
}
