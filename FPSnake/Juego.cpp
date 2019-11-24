#include "Juego.h"

static float to_fps(float fps, int value)
{
    if (fps < 1)
        fps = 60;
    return value * fps / 60;
}

Juego::Juego()
{
    fps = 0;
    frameCount = 0;
    currentTime = 0,
    previousTime = 0;

    game_over = false;
    juego_corriendo = false;
    pausado = false;

    nivel = 3;

    m = to_fps(fps, 30);
    m2 = to_fps(fps, 10);

    tick = 30;
    tick2 = 10;

    tablero = new Tablero();
}

Juego::~Juego()
{
    delete tablero;
}

void Juego::pause()
{
    pausado = true;
}

void Juego::start()
{
    pausado = false;
    juego_corriendo = true;
      std::cout << juego_corriendo<< '\n';
}

void Juego::stop()
{
    juego_corriendo = false;
    game_over = false;
    pausado = false;
}




void Juego::display()
{
    int old_cam = tablero->camera_mode;

    tablero->camera_mode = 3;
    tablero->set_camera();

    calculateFPS();
    Punto p;

    char s [50];


    if (juego_corriendo)
    {

        tablero->camera_mode = old_cam;
        tablero->set_camera();

        if (clock2())
        {
            if (tablero->a > 360)
            {
                tablero->a = 0;
            }

            tablero->a += 5;

            if (tablero->m > 0.1f)
            {
                tablero->m = 0.0;
            }

            tablero->m += 0.05;
        }

        tablero->draw_objects();

        glColor3f(0.0f, 0.0f, 0.0f);
        glRectf(0,0, 0.75f, -0.1f);

        tablero->camera_mode = 3;
        tablero->set_camera();

        if (clock())
        {
            run();
        }

        if (game_over)
        {
            if (wait())
            {
                p.x = -1.25f;
                p.y = 0.5f;
                p.z = 0.15f;
                draw_text("GAME OVER", p, 0.0f, 0.0f, 0.0f);
            }
        }

        sprintf(s, "puntaje: %d", puntaje * 10);

        p.x = -1.0f;
        p.y = 0.5f;
        p.z = -7.0f;

        if (comer)
        {
            if (wait2())
            {
                draw_text(s, p, 0.0f, 0.0f, 0.0f);
            }
        }
        else
        {
            draw_text(s, p, 0.0f, 0.0f, 0.0f);
        }

    }


    tablero->camera_mode = old_cam;
}

void Juego::run()
{
    if (pausado || game_over || !juego_corriendo) return;

    Objeto o = tablero->estrellado(tablero->serpiente.get_cabeza());
    comer = false;
    key_pressed = false;
    switch (o)
    {
        case NADA:
            tablero->serpiente.avanzar();
        break;
        case ITEM:

            comer = true;
            puntaje++;
            tablero->serpiente.crecer(true);
            tablero->serpiente.avanzar();
            tablero->mover_item();
            if (tablero->serpiente.tamanio() % 4 == 0)
                    {
                        tablero->add_obstaculo();
                    }

        break;

        case OBSTACULO:
        case PARED:
        case SERPINTE:
            tablero->serpiente.encogerce();
            //game_over = true;
        break;

    }
}

void Juego::on_key_pressed(int key)
{
    switch (key)
    {
        case KEY_CAMERA:
            if (!juego_corriendo) return;
            tablero->cambiar_camara();
        break;
        case KEY_PAUSE:
            if (!juego_corriendo) return;
            pause();
        break;
        case KEY_QUIT:
            exit(0);
        break;
        case 13:
            if (pausado) return;
            start();
        break;
        case KEY_STOP:
            if (!juego_corriendo) return;
            stop();
        break;
        case KEY_LEFT:
            if (!juego_corriendo || key_pressed) return;
            tablero->serpiente.cambiar_direccion(LEFT);
            key_pressed = true;

        break;

        case KEY_RIGHT:
            if (!juego_corriendo || key_pressed) return;
            tablero->serpiente.cambiar_direccion(RIGHT);
            key_pressed = true;
        break;

        default:
            cout << "key = " << key << "\n";
        break;
    }
}

bool Juego::wait()
{
    bool wait = m > 0 && m < to_fps(fps, 30);
    m++;
    if (m > to_fps(fps, 30)) m = -to_fps(fps, 30);
    return wait;
}

bool Juego::wait2()
{
    bool wait = m2 > 0 && m2 < to_fps(fps, 10);
    m2++;
    if (m2 > to_fps(fps, 10)) m2 = -to_fps(fps, 10);
    return wait;
}

void Juego::calculateFPS(void)
{
    //  Increase frame count
    frameCount++;

    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
    int timeInterval = currentTime - previousTime;

    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = frameCount / (timeInterval / 1000.0f);
        //  Set time
        previousTime = currentTime;
        //  Reset frame count
        frameCount = 0;
    }
}

bool Juego::clock()
{
    // Speed up every time grows.
    tick += (nivel + (tablero->serpiente.tamanio() / 10));
    bool wait = tick < to_fps(fps, 30);
    if (tick > to_fps(fps, 30)) tick = 0;
    return !wait;
}

bool Juego::clock2()
{
    tick2++;
    bool wait = tick2 < to_fps(fps, 10);
    if (tick2 > to_fps(fps, 10)) tick2 = 0;
    return !wait;
}
