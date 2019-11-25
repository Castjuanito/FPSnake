#include "Tablero.h"

Tablero::Tablero()
{
    a = 0;
    m = 0.1;
}


void Tablero::add_obstaculo()
{
    Punto p = random_point();
    bool b = false;

    while (b || estrellado(p) != NADA)
    {
        p = random_point();
    }

    obstaculos.push_back(p);
}

void Tablero::mover_item()
{
    Punto p = random_point();

    while (estrellado(p) != NADA)
    {
        p = random_point();
    }

    item = p;
}

void Tablero::draw_axis()
{
    glLineWidth(1.0f);
    glNormal3f(0.0, 1.0, 0.0);
    // eixo X - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();
    // eixo Y - Green
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();
    // eixo Z - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void Tablero::reset()
{
    obstaculos.clear();
    camera_mode = 0;
    serpiente.reset();
    mover_item();
    add_obstaculo();
}

void Tablero::draw_guide()
{
  Punto cab = serpiente.get_cabeza();
  glLineWidth(10.0f);
  glNormal3f(0.0, 1.0, 0.0);
  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
  glVertex3f(cab.x,cab.y+0.5,cab.z);
  glVertex3f(item.x,item.y+0.5,item.z);
  glEnd();
}

void Tablero::draw_paredes()
{
    glLineWidth(1.0f);
    glNormal3f(0.0, 1.0, 0.0);
    // eixo X - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();
    // eixo Y - Green
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();
    // eixo Z - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void Tablero::draw_board()
{
    enable_2D_texture();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[GROUND_TEXTURE]);
        glBegin(GL_POLYGON);
            //glColor3f(0.0f, 1.0f, 0.0f);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(0, 0);
            glVertex3f(-TABLERO_SIZE, 0.0f,  TABLERO_SIZE);
            glTexCoord2f(1, 0);
            glVertex3f( TABLERO_SIZE, 0.0f,  TABLERO_SIZE);
            glTexCoord2f(1, 1);
            glVertex3f( TABLERO_SIZE, 0.0f, -TABLERO_SIZE);
            glTexCoord2f(0, 1);
            glVertex3f(-TABLERO_SIZE, 0.0f, -TABLERO_SIZE);
        glEnd();


        Punto p;
        float size = -TABLERO_SIZE - 0.1f;
        // Draw bordes. TODO: It's better use a rectangle.
        while (size < TABLERO_SIZE + 0.1f)
        {

            p.x = size;
            p.y = 0.125f;
            p.z = TABLERO_SIZE + 0.125;
            glColor3f(1.0f, 0.0f, 0.0f);
            draw_cube(0.25f, p,BRICK_TEXTURE);

            glColor3i(1.0,0,0);
            p.x = -TABLERO_SIZE - 0.125;
            p.y = 0.125f;
            p.z = size;
            glColor3f(0.0f, 1.0f, 0.0f);
            draw_cube(0.25f, p,BRICK_TEXTURE);

            glColor3i(1.0,0,0);
            p.x = TABLERO_SIZE + 0.125;
            p.y = 0.125f;
            p.z = -size;
            glColor3f(0.0f, 5.0f, 0.0f);
            draw_cube(0.25f, p, BRICK_TEXTURE);

            glColor3i(1.0,0,0);
            p.x = -size;
            p.y = 0.125f;
            p.z = -TABLERO_SIZE - 0.125;
            glColor3f(0.0f, 0.0f, 1.0f);
            draw_cube(0.25f, p, BRICK_TEXTURE);

            size += 0.25f;
        }

    glPopMatrix();
    disable_2D_texture();
}

void Tablero::draw_comida()
{
    Punto p = item;
    //draw_sphere(0.25f, p, FOOD_TEXTURE);

    // "leaf"
    glPushMatrix();
        glTranslatef(p.x + 0.05, p.y + m + 0.25, p.z);
        glRotatef(a, 0.0, 1.0, 0.0);

        glColor3f(0.2f, 0.4f, 0.0f);
        glLineWidth(3.5f);
        glBegin(GL_LINE_STRIP);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0.1, -0.01, 0);
            glVertex3f(0.1, -0.01, 0);
            glVertex3f(0.15, -0.02, 0);
            glVertex3f(0.15, -0.02, 0);
            glVertex3f(0.20, -0.03, 0);
            glVertex3f(0.20, -0.03, 0);
            glVertex3f(0.25, -0.04, 0);
            glVertex3f(0.25, -0.04, 0);
        glEnd();
    glPopMatrix();

    enable_2D_texture();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[FOOD_TEXTURE]);
        glTranslatef(p.x, p.y + m, p.z);
        glRotatef(a, 0.0, 1.0, 0.0);
        glut2SolidSphere(0.25f, 100.0f, 100.0f);
    glPopMatrix();

    disable_2D_texture();

}

void Tablero::draw_obstaculos()
{
    for (int i = 0; i < obstaculos.size(); ++i)
    {
        Punto p = obstaculos.at(i);
        draw_cube(0.5f, p,BARRIER_TEXTURE);
    }
}

void Tablero::draw_objects()
{
    draw_board();
    draw_comida();
    draw_obstaculos();
    draw_axis();
    draw_guide();
    serpiente.draw();
}

Objeto Tablero::estrellado(Punto p)
{
    if (p.x >  5.0f ||
        p.x < -5.0f ||
        p.z >  5.0f ||
        p.z < -5.0f)
    {
        return PARED;
    }

    if (p.x == item.x && p.z == item.z)
    {
        return ITEM;
    }

    for (int i = 0; i < obstaculos.size(); ++i)
    {
        Punto b = obstaculos.at(i);

        if (p.x == b.x && p.z == b.z)
        {
            return OBSTACULO;
        }
    }

    if (serpiente.estrellado(p))
    {
        return SERPINTE;
    }

    return NADA;
}

void Tablero::cambiar_camara()
{
    camera_mode += 1;

    if (camera_mode > 1)
    {
        camera_mode = 0;
    }
}

void Tablero::set_camera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    camara.upX    = 0.0f;
    camara.upY    = 1.0f;
    camara.upZ    = 0.0f;
    camara.aspect = 1;
  //  glRotatef(180,0.0,0.0,1.0);

    if (camera_mode == 4)
    {
        camara.eyeX    = 0.0f;
        camara.eyeY    = 10.0f;
        camara.eyeZ    = 15.0f;
        camara.centerX = 0.0f;
        camara.centerY = 0.0f;
        camara.centerZ = 0.0f;
        camara.fovy    = 45;
        camara.zNear   = 0.1f;
        camara.zFar    = 50;
    }
    else if (camera_mode == 3)
    {
        camara.eyeX    = 0.0f;
        camara.eyeY    = 1.0f;
        camara.eyeZ    = 20.0f;
        camara.centerX = 0.0f;
        camara.centerY = 0.0f;
        camara.centerZ = 0.0f;
        camara.fovy    = 45;
        camara.zNear   = 0.1f;
        camara.zFar    = 50;
    }
    else if (camera_mode == 2)
    {
        #ifdef DEBUG
            camara.eyeX    = 0.0f;
            camara.eyeY    = -10.0f;
            camara.eyeZ    = 15.0f;
            camara.centerX = 0.0f;
            camara.centerY = 0.0f;
            camara.centerZ = 0.0f;
            camara.fovy    = 45;
            camara.zNear   = 0.1f;
            camara.zFar    = 50;
        #else
            camara.eyeX    = -2.0f;
            camara.eyeY    = 5.0f;
            camara.eyeZ    = 20.0f;
            camara.centerX = 0.0f;
            camara.centerY = 0.0f;
            camara.centerZ = 0.0f;
            camara.fovy    = 45;
            camara.zNear   = 1.0f;
            camara.zFar    = 50;
        #endif
    }
    else if (camera_mode == 1)
    {
        camara.eyeX    = 0.0f;
        camara.eyeY    = 45.0f;
        camara.eyeZ    = 1.0f;
        camara.centerX = 0.0f;
        camara.centerY = 0.0f;
        camara.centerZ = 0.0f;
        camara.fovy    = 20;
        camara.zNear   = 1.0f;
        camara.zFar    = 100;

    }

    else if (camera_mode == 0)
    {

        Punto cab = serpiente.get_cabeza();
        int dir = serpiente.get_direccion();

        switch (dir) {
          case UP:
          camara.centerZ = -180.0f;
          camara.centerX = 0.0f;
          break;
          case LEFT:
          camara.centerX = -180.0f;
          camara.centerZ = 0.0f;
          break;
          case DOWN:
          camara.centerZ = 180.0f;
          camara.centerX = 0.0f;
          break;
          case RIGHT:
          camara.centerX = 180.0f;
          camara.centerZ = 0.0f;
          break;
        }

        camara.eyeX    = cab.x;
        camara.eyeY    = cab.y;
        camara.eyeZ    = cab.z;
        camara.centerY = 10.0f;
        camara.fovy    = 50;
        camara.zNear   = 1.0f;
        camara.zFar    = 100;
        //glRotatef(-180,0.0,1.0,0.0);
    }



    gluPerspective(camara.fovy, camara.aspect, camara.zNear, camara.zFar);
    gluLookAt(camara.eyeX, camara.eyeY, camara.eyeZ, camara.centerX, camara.centerY, camara.centerZ, camara.upX, camara.upY, camara.upZ);
    glMatrixMode(GL_MODELVIEW);
}
