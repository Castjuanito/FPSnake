#ifndef SERPIENTE_H
#define SERPIENTE_H


#include "Utilitarios.h"

class Serpiente
{
private:
    deque<Punto> cuerpo;
    int direccion;
public:
    Serpiente();
    void avanzar();
    void cambiar_direccion(int d);
    void draw();
    void crecer(bool cola);
    void encogerce();
    bool estrellado(Punto p);
    int tamanio();
    Punto get_cabeza();
    Punto get_cola();
    int get_direccion();
};
#include"Serpiente.cpp"

#endif
