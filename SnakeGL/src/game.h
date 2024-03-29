#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "scenario.cpp"
#include <ctime>
#include <cstdio>

class Game
{
private:
    bool      is_game_over;
    bool      is_running;
    bool      ate;
    bool      key_pressed;
    int       m, m2;
    int       frameCount;
    int       currentTime;
    int       previousTime;
    int       score;
    int       tick;
    int       tick2;
    int       level;
    float     fps;
    Scenario* scenario;
    bool      wait();
    bool      wait2();
    bool      clock();
    bool      clock2();
    void      calculateFPS();
    void      run();
public:
    Game();
    ~Game();
    void display();
    void start();
    void reset();
    void on_key_pressed(int key);
};