//
// Created by ollie on 14/01/2022.
//

#ifndef CUBIC_TIME_H
#define CUBIC_TIME_H

class Time
{
private:
    static double _lastTime;
    static double _deltaTime;
    Time();

public:
    static float DeltaTime();

    static void Start();
    static void Update(double time);
};


#endif //CUBIC_TIME_H
