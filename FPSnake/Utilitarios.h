#ifndef UTILITARIOS_H
#define UTILITARIOS_H


#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glut.h>

#include <deque>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <SOIL/SOIL.h>

using namespace std;

// Objects can navigate from -5.0f to 5.0f.
#define TABLERO_SIZE      5.25f
// Y axis difference. Ground to Objects.
#define GROUND_DIFF     0.25f

#define GROUND_TEXTURE  0
#define FOOD_TEXTURE    1
#define BARRIER_TEXTURE 2
#define SNAKE_TEXTURE   3
#define MENU_TEXTURE    4
#define BRICK_TEXTURE   5

#define TEXTURE_COUNT   6

/* Key mappings. */
#define KEY_CAMERA      32  // space
#define KEY_PAUSE       112 // p
#define KEY_QUIT        27  // esc
//#define KEY_SELECT      13  // enter
#define KEY_START       13 // s
#define KEY_STOP        113 // q
#define KEY_RESET       114 // r
#define KEY_UP          GLUT_KEY_UP
#define KEY_DOWN        GLUT_KEY_DOWN
#define KEY_RIGHT       GLUT_KEY_RIGHT
#define KEY_LEFT        GLUT_KEY_LEFT

struct Punto
{
    float x, y, z;
};

enum Objeto
{
    NADA    = 0,
    SERPINTE   = 1,
    ITEM    = 2,
    OBSTACULO = 3,
    PARED   = 4,
};

enum Direccion
{
    DOWN  = 1,
    UP    = 2,
    LEFT  = 3,
    RIGHT = 4,
};

struct Camera
{
    GLdouble eyeX, /* gluLookAt */
             eyeY,
             eyeZ,
             centerX,
             centerY,
             centerZ,
             upX,
             upY,
             upZ,
             fovy,
             aspect,
             zNear,
             zFar;
};

inline int random_range(int min, int max)
{
    return (rand() % (max + min)) + min;
}

inline float random_pos()
{
    return (rand() % 20 / 2.0f) - 5.0f;
}

inline Punto random_point()
{
    Punto p;
    p.x = random_pos();
    p.y = GROUND_DIFF;
    p.z = random_pos();

    return p;
}

inline void load_image(const char* filename)
{
    int width, height;
    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
}

inline void enable_2D_texture()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);

    glEnable(GL_TEXTURE_2D);
}

inline void disable_2D_texture()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 100.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);

    glDisable(GL_TEXTURE_2D);
}

inline void draw_cube(float size, Punto p)
{
     enable_2D_texture();

    glPushMatrix();
      //  glBindTexture(GL_TEXTURE_2D, textures[res_id]);
        glTranslatef(p.x, p.y, p.z);
        glutSolidCube(size);
    glPopMatrix();

    disable_2D_texture();
}

inline void draw_sphere(float size, Punto p, int res_id)
{
    enable_2D_texture();

    glPushMatrix();
        glTranslatef(p.x, p.y, p.z);

        glutSolidSphere(size, 100.0f, 100.0f);
    glPopMatrix();

    disable_2D_texture();
}

inline void draw_text(string s, Punto p, float r, float g, float b)
{
    glDisable(GL_LIGHTING);

    int len, i;
    glColor3f(r, g, b);
    glRasterPos3f(p.x, p.y,p.z);
    len = (int) s.length();

    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }

    glEnable(GL_LIGHTING);
}


#endif
