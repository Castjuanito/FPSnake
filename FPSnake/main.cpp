#include "Juego.h"

#include <iostream>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glut.h>

using namespace std;

int width  = 640,
    height = 640;

bool game_over = false,
     juego_corriendo   = false;

Juego* juego = NULL;

void keyboard(unsigned char key, int x, int y)
{
    juego->on_key_pressed((int)key);
    glutPostRedisplay();
}

void keyboardSpecial(int key, int x, int y)
{
    juego->on_key_pressed((int)key);
    glutPostRedisplay();
}

void init()
{
    // Init GL before call this. Otherwise don't work.
  //  setVSync(true);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    float pos_light[4] = { 5.0f, 5.0f, 10.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, pos_light);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
#ifdef USE_BUFFERS
    glEnable(GL_LIGHTING);
#else
    glDisable(GL_LIGHTING);
#endif
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    load_resources();

    juego = new Juego();
}

void display()
{
    /*glViewport(width / 4, height / 4, 200, 200);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    juego->display();


#ifdef USE_BUFFERS
    glutSwapBuffers();
#else
    glFlush();
#endif
}

void resize(int w, int h)
{
    /*glViewport(0.0f, 0.0f, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

#ifdef USE_BUFFERS
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
#else
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
#endif

    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("FPSnake");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    init();
    glutMainLoop();

    return 0;
}
