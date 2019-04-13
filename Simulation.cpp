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
    processFile(inputFileToBeProcessed);
}

void Simulation::processFile(string fileToProcess)
{
    cout << "processFile" << endl;
    ifstream inputStream;
    inputStream.open(fileToProcess);

    string valueRead;

    int currentTimeTick = 0; //what is the current time tick we are at
    int fileLineNum = 0; //the current line number of the file
    int nextTimeTickLine = 2; //I need this so I can decipher which lines correspond to time ticks and which lines correspond to students entering the line/time required at the window
    while(!inputStream.eof())
    {
        fileLineNum++; //I want to start off the line number of the file as 1
        getline(inputStream, valueRead);
        try
        {
            int numberRead = stoi(valueRead); //convert the integer (read in as a string) to an int object
            if(numberRead < 0)
                throw 0;

            if(fileLineNum == 1)
            {
                windowArray = new Window[numberRead];
            }

            else if (fileLineNum == nextTimeTickLine)//the line number is not equal to 1, so all other integer values correspond to either a clock tick time, the number of students arriving in line, and the times each student requires at the window
            {
                currentTimeTick = numberRead;
            }

            else if(fileLineNum == nextTimeTickLine + 1)
            {
                                    //current line + this line + num of students + one more for next line
                nextTimeTickLine = nextTimeTickLine + 1 + numberRead + 1;
            }

            else //the value is a student time required at window value
            {
                listOfStudents.push_back(Students(numberRead, currentTimeTick));
                //addStudent(Students(numberRead, currentTimeTick)); //add a student to the studentsQueue queue, initializing the student object as requiring numberRead minutes at the window and entering the queue at
            }
        }

        catch(invalid_argument e)
        {
            //do nothing.
        }
        catch(int i)
        {
            cerr << "Value must be non-negative!" << endl;
            exit(1);
        }

    }

    inputStream.close(); //close the input stream

    addStudentsToStudentsQueue();
}

void Simulation::addStudentsToStudentsQueue()
{
    for (int i = 0; i < listOfStudents.size(); ++i)
    {
        Students theStudent = listOfStudents[i];
        addStudent(theStudent);
        listOfStudents.pop_back();
    }
}

Simulation::~Simulation()
{
    delete studentsQueue;
    delete [] windowArray;
    delete [] studentCompletedArray;
}

void Simulation::addStudent(Students theStudent)
{
    studentsQueue->insert(theStudent);
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
                if(studentsQueue->getSize() > 0)
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

        processAggregates();
        printAggregates();
        break;

        /*
        if(isAllWorkComplete())
        {
            processAggregates();
            printAggregates();
            break;
        }
        */
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
