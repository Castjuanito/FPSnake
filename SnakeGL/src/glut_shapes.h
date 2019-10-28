
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static GLUquadricObj *quadObj;

#define QUAD_OBJ_INIT() { if(!quadObj) initQuadObj(); }

static void __glut2Warning(const char* msg) {}

static void __glut2FatalError(const char* msg) { __glut2Warning(msg); exit(0); }

static void initQuadObj(void)
{
    quadObj = gluNewQuadric();
    if (!quadObj)
        __glut2FatalError("out of memory.");
}


void APIENTRY glut2SolidSphere(GLdouble radius, GLint slices, GLint stacks)
{
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    QUAD_OBJ_INIT();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    /* If we ever changed/used the texture or orientation state
         of quadObj, we'd need to change it to the defaults here
         with gluQuadricTexture and/or gluQuadricOrientation. */
    gluSphere(quadObj, radius, slices, stacks);

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}
static void drawBox(GLfloat size, GLenum type)
{
    static GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--)
    {
        glBegin(type);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0, 0);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1, 0);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1, 1);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(0, 1);
            glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

/* CENTRY */
void APIENTRY glut2WireCube(GLdouble size)
{
    drawBox(size, GL_LINE_LOOP);
}

void APIENTRY glut2SolidCube(GLdouble size)
{
    drawBox(size, GL_QUADS);
}

/* ENDCENTRY */
static void doughnut(GLfloat r, GLfloat R, GLint nsides, GLint rings)
{
    int i, j;
    GLfloat theta, phi, theta1;
    GLfloat cosTheta, sinTheta;
    GLfloat cosTheta1, sinTheta1;
    GLfloat ringDelta, sideDelta;

    ringDelta = 2.0 * M_PI / rings;
    sideDelta = 2.0 * M_PI / nsides;

    theta = 0.0;
    cosTheta = 1.0;
    sinTheta = 0.0;
    for (i = rings - 1; i >= 0; i--) {
        theta1 = theta + ringDelta;
        cosTheta1 = cos(theta1);
        sinTheta1 = sin(theta1);
        glBegin(GL_QUAD_STRIP);
        phi = 0.0;
        for (j = nsides; j >= 0; j--) {
            GLfloat cosPhi, sinPhi, dist;

            phi += sideDelta;
            cosPhi = cos(phi);
            sinPhi = sin(phi);
            dist = R + r * cosPhi;

            glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
            glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, r * sinPhi);
            glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
            glVertex3f(cosTheta * dist, -sinTheta * dist,    r * sinPhi);
        }
        glEnd();
        theta = theta1;
        cosTheta = cosTheta1;
        sinTheta = sinTheta1;
    }
}
void APIENTRY glut2WireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings)
{
    glPushAttrib(GL_POLYGON_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    doughnut(innerRadius, outerRadius, nsides, rings);
    glPopAttrib();
}

