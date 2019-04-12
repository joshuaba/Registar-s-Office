#include <iostream>
#include <cstdlib>
#include <string>
#include "Simulation.h"


using namespace std;

int main(int argc, char** argv)
{
    if(argc > 1)
    {
        string fileToProcess = argv[1];
        cout << fileToProcess << endl;
        Simulation mySimulation(fileToProcess);
        //mySimulation.processStudents();
    }
    else
    {
        cout << "Error! You need to pass in an input file! Exiting program" << endl;
        exit(1);
    }
}
