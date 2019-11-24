#ifndef TABLERO_H
#define TABLERO_H

#include "Utilitarios.h"
#include "Serpiente.h"

class Tablero
{
private:
    Punto item;
    vector<Punto> obstaculos;
    Camera camara;
    void draw_paredes();
    void draw_comida();
    void draw_obstaculos();
    //void draw_background();
public:
    int camera_mode;
    float m;
    float a;
    Serpiente serpiente;
    Tablero();
    void add_obstaculo();
    void mover_item();
    void draw_board();
    void draw_objects();
    void draw_axis();
    void cambiar_camara();
    void set_camera();
    //void reset();
    Objeto estrellado(Punto p);
};

#include "Tablero.cpp"

#endif
