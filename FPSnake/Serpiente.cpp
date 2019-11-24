#include "Serpiente.h"



Serpiente::Serpiente()
{
  direccion=LEFT;
}


void Serpiente::avanzar()
{
    cuerpo.pop_back();
    crecer(false);
}

void Serpiente::cambiar_direccion(int d)
{

    switch (direccion) {
      case UP:
        if (d==LEFT) {
          direccion=LEFT;
        }
        else
        direccion=RIGHT;

      break;
      case LEFT:
      if (d==LEFT) {
        direccion=DOWN;
      }
      else
      direccion=UP;
      break;
      case DOWN:
      if (d==LEFT) {
        direccion=RIGHT;
      }
      else
      direccion=LEFT;
      break;
      case RIGHT:
      if (d==LEFT) {
        direccion=UP;
      }
      else
      direccion=DOWN;
      break;

    }

}

void Serpiente::draw()
{

    Punto h = cuerpo[0];

    glColor3f(1.0, 1.0, 0.6);
    glPushMatrix();
        glTranslatef(h.x, h.y, h.z);
        glutSolidCube(0.5f);
    glPopMatrix();

    enable_2D_texture();



    for (size_t i = 1; i < cuerpo.size(); ++i)
    {
        Punto p = cuerpo.at(i);

        glPushMatrix();
            glTranslatef(p.x, p.y, p.z);
            glutSolidCube(0.5f);
        glPopMatrix();
    }

    disable_2D_texture();
}

Punto Serpiente::get_cabeza()
{
    return cuerpo[0];
}

Punto Serpiente::get_cola()
{
    return cuerpo[cuerpo.size() - 1];
}

int Serpiente::get_direccion()
{
  return direccion;
}

void Serpiente::crecer(bool cola)
{
    Punto p;
    p.x = cuerpo[0].x;
    p.y = cuerpo[0].y;
    p.z = cuerpo[0].z;

    switch (direccion)
    {
        case DOWN:

            p.z += 0.5f;
        break;
        case UP:

            p.z -= 0.5f;
        break;
        case LEFT:

            p.x -= 0.5f;
        break;
        case RIGHT:
    
            p.x += 0.5f;
        break;
    }

    if (cola)
    {
        cuerpo.push_back(p);
    }
    else
    {
        cuerpo.push_front(p);
    }


}

void Serpiente::encogerce()
{
  if(cuerpo.size()>2)
  {
    int tam = cuerpo.size()/2;

    for (int i = 0; i < tam; i++) {
      cuerpo.pop_back();
    }
  }

}

bool Serpiente::estrellado(Punto p)
{

    for (int i = 1; i < cuerpo.size(); ++i)
    {
        Punto b = cuerpo.at(i);

        if (p.x == b.x && p.z == b.z)
        {
            return true;
        }
    }

    return false;
}

int Serpiente::tamanio()
{
    return cuerpo.size();
}
