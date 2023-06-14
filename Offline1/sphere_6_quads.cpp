#include <GL/glut.h>
#include <cmath>
#include "Sphere.h"

const float PI = 3.14159265359f;

Sphere sphere1(1.0f, 36, 18, true, 2);    
Sphere sphere2(1.0f, 36, 18, true,  2);  

void drawHollowSphereSegment(float radius, float thetaStart, float thetaEnd, float phiStart, float phiEnd, int slices, int stacks) {
    float thetaStep = (thetaEnd - thetaStart) / slices;
    float phiStep = (phiEnd - phiStart) / stacks;

    for (float theta = thetaStart; theta < thetaEnd; theta += thetaStep) {
        for (float phi = phiStart; phi < phiEnd; phi += phiStep) {
            glBegin(GL_QUADS);

            float x1 = radius * sin(theta) * cos(phi);
            float y1 = radius * sin(theta) * sin(phi);
            float z1 = radius * cos(theta);

            float x2 = radius * sin(theta + thetaStep) * cos(phi);
            float y2 = radius * sin(theta + thetaStep) * sin(phi);
            float z2 = radius * cos(theta + thetaStep);

            float x3 = radius * sin(theta + thetaStep) * cos(phi + phiStep);
            float y3 = radius * sin(theta + thetaStep) * sin(phi + phiStep);
            float z3 = radius * cos(theta + thetaStep);

            float x4 = radius * sin(theta) * cos(phi + phiStep);
            float y4 = radius * sin(theta) * sin(phi + phiStep);
            float z4 = radius * cos(theta);

            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);

            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);

            glNormal3f(x3, y3, z3);
            glVertex3f(x3, y3, z3);

            glNormal3f(x4, y4, z4);
            glVertex3f(x4, y4, z4);

            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5.0, -5.0, 5.0,  // Eye position
              0.0, 0.0, 0.0,  // Look-at position
              0.0, 1.0, 0.0); // Up vector

    glColor3f(1.0f, 0.0f, 0.0f); // Red color

    // float radius = 1.0f; // Radius of the hollow sphere
    // int slices = 30; // Number of slices (horizontal divisions)
    // int stacks = 30; // Number of stacks (vertical divisions)

    // float thetaStart = 0.0f; // Starting angle for theta (vertical)
    // float thetaEnd = PI / 2.0f; // Ending angle for theta (vertical)
    // float phiStart = 0.0f; // Starting angle for phi (horizontal)
    // float phiEnd = PI; // Ending angle for phi (horizontal)

    // drawHollowSphereSegment(radius, thetaStart, thetaEnd, phiStart, phiEnd, slices, stacks);

    sphere1.draw();

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Hollow Sphere Segment");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}