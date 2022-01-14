//
// Created by ollie on 14/01/2022.
//

#include "../include/Time.h"

double Time::_lastTime;
double Time::_deltaTime;

Time::Time()
= default;

float Time::DeltaTime()
{
    return (float) _deltaTime;
}

void Time::Start()
{
    _lastTime = 0;
    _deltaTime = 0;
}

void Time::Update(double time)
{
    _deltaTime = time - _lastTime;
    _lastTime = time;
}