#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

void init(void)
{
    glClearColor(1.0, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
}

void setPixel(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Circle(int xCenter, int yCenter, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 / 2 - radius;

    while (x <= y) {
        setPixel(xCenter + x, yCenter + y);
        setPixel(xCenter + y, yCenter + x);
        setPixel(xCenter - x, yCenter + y);
        setPixel(xCenter + y, yCenter - x);
        setPixel(xCenter - x, yCenter - y);
        setPixel(xCenter - y, yCenter - x);
        setPixel(xCenter + x, yCenter - y);
        setPixel(xCenter - y, yCenter + x);

        if (d < 0) {
            d += (2 * x) + 3;
        }
        else {
            d += (2 * (x - y)) + 5;
            y -= 1;
        }

        x++;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Bresenham Circle");
    init();

    glutDisplayFunc([]() {
        glClear(GL_COLOR_BUFFER_BIT);
        int x = 400;
        int y = 400;
        int r = 200;

        glColor3f(0, 0, 0);
        Circle(x, y, r);

        for (int i = 1; i < 200; i++) {
            y -= 1;
            r -= 1;
            float col = 1 - 1.0 / (i * 0.5);
            glColor3f(col, col, col);
            Circle(x, y, r);
        }

        glFlush();
    });
    
    glutMainLoop();
    return 0;
}