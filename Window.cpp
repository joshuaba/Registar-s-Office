#include <iostream>
#include <string>
#include <cstdlib>
#include "Window.h"

using namespace std;

Window::Window()
{
    studentAtWindow == NULL;
    idleTime = 0;
}

Window::Window(Students& studentArrived, int timeIdle)
{
    studentAtWindow = &studentArrived;
    idleTime = timeIdle;
}

Window::~Window()
{
    delete studentAtWindow;
    idleTime = 0;
}

void Window::incrementIdleTime()
{
    idleTime++;
}

int Window::getIdleTime()
{
    return idleTime;
}

void Window::setStudent(Students* theStudent)
{
    studentAtWindow = theStudent;
}

Students* Window::getStudentAtWindow()
{
    return studentAtWindow;
}
