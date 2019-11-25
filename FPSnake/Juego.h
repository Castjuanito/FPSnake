#ifndef JUEGO_H
#define JUEGO_H


#include "Utilitarios.h"
#include "Tablero.h"
#include <ctime>
#include <cstdio>

class Juego
{
private:
    bool      game_over;
    bool      juego_corriendo;
    bool      pausado;
    bool      comer;
    bool      key_pressed;
    int       m, m2;
    int       frameCount;
    int       currentTime;
    int       previousTime;
    int       puntaje;
    int       tick;
    int       tick2;
    int       nivel;
    float     fps;
    Tablero* tablero;
    bool      wait();
    bool      wait2();
    bool      clock();
    bool      clock2();
    void      calculateFPS();
    void      run();
    void      draw_menu();
public:
    Juego();
    ~Juego();
    void display();
    void pause();
    void start();
    void stop();
    void reset();
    void on_key_pressed(int key);
};


#include "Juego.cpp"

#endif
