#include <gl/glut.h>
#include <GL/glu.h>

float rotationAngle = 0.0;
bool hidden = false;

float cameraX = 0.0, cameraY = 0.0;
float targetX = 0.0, targetY = 0.0;

bool mouseDown = false;

void myKeyboard(unsigned char key, int x, int y);
void myMouseMotion(int x, int y);
void myMouseButton(int button, int state, int x, int y);
void init3DProjection();
void window();
void hiddenCarte();
void drawAngklung();
void setupLighting();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(720, 720);
    glutInitWindowPosition(200, 0);
    init3DProjection();
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouseButton);
    glutMotionFunc(myMouseMotion);
    glutMainLoop();
    return 0;
}


void setupLighting() 
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[] = { 1.0f, 1.0f, 1.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void init3DProjection(void)
{
    glutCreateWindow("Angklung 3D");
    glutDisplayFunc(window);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glRotatef(-15.0, 0, 1, 1);
    setupLighting();
}

void cartecius()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);

    glVertex3f(0.0, -50.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);

    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
}

void window()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(cameraX, 1, 0, 0); 
    glRotatef(cameraY, 0, 1, 0); 
    hiddenCarte();
    drawAngklung();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}

void drawAngklung()
{
    GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat materialShininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
    
    GLUquadric *quadric = gluNewQuadric();

    glColor3ub(222, 184, 135);

    // Bambu Vertikal 1
    glPushMatrix();
    glTranslatef(-2.0, 0.0, 0.0); 
    glRotatef(-90.0, 1, 0, 0);   
    gluCylinder(quadric, 0.2, 0.2, 8.0, 32, 32); 
    glPopMatrix();

    // Bambu Vertikal 2
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-90.0, 1, 0, 0);
    gluCylinder(quadric, 0.2, 0.2, 8.0, 32, 32); 
    glPopMatrix();

    // Bambu Vertikal 3
    glPushMatrix();
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef(-90.0, 1, 0, 0);
    gluCylinder(quadric, 0.2, 0.2, 8.0, 32, 32); 
    glPopMatrix();

    // Bambu Horizontal 1
    glPushMatrix();
    glTranslatef(-2.5, 5.0, 0.0); 
    glRotatef(90.0, 0, 1, 0);     
    gluCylinder(quadric, 0.15, 0.15, 5.0, 32, 32); 
    glPopMatrix();

    // Bambu Horizontal 2
    glPushMatrix();
    glTranslatef(-2.5, 3.0, 0.0); 
    glRotatef(90.0, 0, 1, 0);
    gluCylinder(quadric, 0.15, 0.15, 2.5, 32, 32); 
    glPopMatrix();

    // Bambu Horizontal 3
    glPushMatrix();
    glTranslatef(-2.5, 1.0, 0.0); 
    glRotatef(90.0, 0, 1, 0);
    gluCylinder(quadric, 0.4, 0.4, 5.0, 32, 32); 
    glPopMatrix();

    // Bambu Sela-sela 1
    glColor3ub(139, 69, 19);
    glPushMatrix();
    glTranslatef(-1.0, 1.0, 0.0);
    glRotatef(-90.0, 1, 0, 0);
    gluCylinder(quadric, 0.3, 0.3, 3.0, 32, 32); 
    glPopMatrix();

    // Bambu Sela-sela 2
    glPushMatrix();
    glTranslatef(1.0, 1.0, 0.0);
    glRotatef(-90.0, 1, 0, 0);
    gluCylinder(quadric, 0.3, 0.3, 5.0, 32, 32); 
    glPopMatrix();

    gluDeleteQuadric(quadric);
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'c':
            hidden = !hidden;
            break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void myMouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseDown = true;
            targetX = x;
            targetY = y;
        }
        else if (state == GLUT_UP)
        {
            mouseDown = false;
        }
    }
}

void myMouseMotion(int x, int y)
{
    if (mouseDown)
    {
        cameraX += (y - targetY) * 0.3f;
        cameraY += (x - targetX) * 0.3f;
        targetX = x;
        targetY = y;
        glutPostRedisplay();
    }
}

void hiddenCarte()
{
    if(hidden)
    {
        cartecius();
    }
}
