#include "game.h"

static float to_fps(float fps, int value)
{
    if (fps < 1)
        fps = 60;
    return value * fps / 60;
}

Game::Game()
{
    fps = 0;
    frameCount = 0;
    currentTime = 0,
    previousTime = 0;

    is_game_over = false;
    is_running = false;
    paused = false;

    level = 1;

    m = to_fps(fps, 30);
    m2 = to_fps(fps, 10);

    tick = 30;
    tick2 = 10;

    scenario = new Scenario();
}

Game::~Game()
{
    delete scenario;
}

void Game::start()
{
    paused = false;
}

void Game::reset()
{
    m = to_fps(fps, 30);
    m2 = to_fps(fps, 10);

    score = 0;
    ate = false;
    is_game_over = false;
    paused = false;

    tick = 30;
    tick2 = 10;

    scenario->reset();
    is_running = true;
}

void Game::display()
{
    int old_cam = scenario->camera_mode;

    scenario->camera_mode = 1;
    scenario->set_camera();

    calculateFPS();
    Point p;

    char s [50];

#ifdef DEBUG
    sprintf(s, "FPS: %.2f", fps);

    p.x = -7.0f;
    p.y = 0.5f;
    p.z = 7.0f;
    draw_text(s, p, 0.0f, 0.0f, 0.0f);
#endif

    if (is_running)
    {

        scenario->camera_mode = old_cam;
        scenario->set_camera();

        if (clock2())
        {
            if (scenario->a > 360)
            {
                scenario->a = 0;
            }

            scenario->a += 5;

            if (scenario->m > 0.1f)
            {
                scenario->m = 0.0;
            }

            scenario->m += 0.05;
        }

        scenario->draw_objects();

        glColor3f(0.0f, 0.0f, 0.0f);
        glRectf(0,0, 0.75f, -0.1f);

        scenario->camera_mode = 1;
        scenario->set_camera();

        if (clock())
        {
            run();
        }

        if (is_game_over)
        {
            if (wait())
            {
                p.x = -1.25f;
                p.y = 0.5f;
                p.z = 0.15f;
                draw_text("Perdiste", p, 0.0f, 0.0f, 0.0f);
            }
        }

        sprintf(s, "PUNTAJE: %d", score * 2);

        p.x = -1.0f;
        p.y = 0.5f;
        p.z = -7.0f;

        if (ate)
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

    scenario->camera_mode = old_cam;
}

void Game::run()
{
    if (paused || is_game_over || !is_running) return;

    ObjectType o = scenario->has_collision(scenario->snake.head());
    ate = false;
    key_pressed = false;

    switch (o)
    {
        case NONE:
            scenario->snake.move();
        break;
        case FOOD:
            ate = true;
            score++;
            scenario->snake.grow(true);
            scenario->snake.move();
            scenario->change_food_pos();
        break;
        case BARRIER:
        case BOARD:
        case SNAKE:
            is_game_over = true;
        break;
        default:
        break;
    }
}

void Game::on_key_pressed(int key)
{
    switch (key)
    {
        case KEY_SELECT:
            reset();
        break;
        case KEY_LEFT:
            if (!is_running || key_pressed) return;
            scenario->snake.set_direction(LEFT);
            key_pressed = true;
        break;
        case KEY_RIGHT:
            if (!is_running || key_pressed) return;
            scenario->snake.set_direction(RIGHT);
            key_pressed = true;
        break;
        default:
        break;
    }
}

bool Game::wait()
{
    bool wait = m > 0 && m < to_fps(fps, 30);
    m++;
    if (m > to_fps(fps, 30)) m = -to_fps(fps, 30);
    return wait;
}

bool Game::wait2()
{
    bool wait = m2 > 0 && m2 < to_fps(fps, 10);
    m2++;
    if (m2 > to_fps(fps, 10)) m2 = -to_fps(fps, 10);
    return wait;
}

void Game::calculateFPS(void)
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

bool Game::clock()
{
    // Speed up every time grows.
    tick += (level + (scenario->snake.size() / 10));
    bool wait = tick < to_fps(fps, 30);
    if (tick > to_fps(fps, 30)) tick = 0;
    return !wait;
}

bool Game::clock2()
{
    tick2++;
    bool wait = tick2 < to_fps(fps, 10);
    if (tick2 > to_fps(fps, 10)) tick2 = 0;
    return !wait;
}