#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include "Sphere.h"
#include "Cubesphere.h"

Sphere sphere1(2.0f, 200, 200, true, 2);    
Sphere sphere2(1.0f, 36, 18, true,  2);  

int subdivision = 6;
//Cubesphere sphere;                          // create default sphere(1, 3, true)
// Cubesphere sphere(1.0f, subdivision, true); // radius, subdivision, smooth

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);   // Black and opaque
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
}

// Global variables
GLfloat eyex = 2, eyey = 2, eyez = 2;
GLfloat centerx = 0, centery = 0, centerz = 0;
GLfloat upx = 0, upy = 1, upz = 0;
bool isAxes = true, isCube = true, isPyramid = false;
double pi = 2*acos(0.0);

float scaleFactor=1;
float scaleStep=0.05;

/* Draw axes: X in Red, Y in Green and Z in Blue */
void drawAxes() {
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1,0,0);   // Red
        // X axis
        glVertex3f(0,0,0);
        glVertex3f(100,0,0);

        glColor3f(0,1,0);   // Green
        // Y axis
        glVertex3f(0,0,0);
        glVertex3f(0,100,0);

        glColor3f(0,0,1);   // Blue
        // Z axis
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
    glEnd();
}

// /* Draw a cube centered at the origin */
// void drawCube() {
//     glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
//         // Top face (y = 1.0f)
//         // Define vertices in counter-clockwise (CCW) order with normal pointing out
//         glColor3f(0.0f, 1.0f, 0.0f);     // Green
//         glVertex3f( 1.0f, 1.0f, -1.0f);
//         glVertex3f(-1.0f, 1.0f, -1.0f);
//         glVertex3f(-1.0f, 1.0f,  1.0f);
//         glVertex3f( 1.0f, 1.0f,  1.0f);

//         // Bottom face (y = -1.0f)
//         glColor3f(1.0f, 0.5f, 0.0f);     // Orange
//         glVertex3f( 1.0f, -1.0f,  1.0f);
//         glVertex3f(-1.0f, -1.0f,  1.0f);
//         glVertex3f(-1.0f, -1.0f, -1.0f);
//         glVertex3f( 1.0f, -1.0f, -1.0f);

//         // Front face  (z = 1.0f)
//         glColor3f(1.0f, 0.0f, 0.0f);     // Red
//         glVertex3f( 1.0f,  1.0f, 1.0f);
//         glVertex3f(-1.0f,  1.0f, 1.0f);
//         glVertex3f(-1.0f, -1.0f, 1.0f);
//         glVertex3f( 1.0f, -1.0f, 1.0f);

//         // Back face (z = -1.0f)
//         glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
//         glVertex3f( 1.0f, -1.0f, -1.0f);
//         glVertex3f(-1.0f, -1.0f, -1.0f);
//         glVertex3f(-1.0f,  1.0f, -1.0f);
//         glVertex3f( 1.0f,  1.0f, -1.0f);

//         // Left face (x = -1.0f)
//         glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//         glVertex3f(-1.0f,  1.0f,  1.0f);
//         glVertex3f(-1.0f,  1.0f, -1.0f);
//         glVertex3f(-1.0f, -1.0f, -1.0f);
//         glVertex3f(-1.0f, -1.0f,  1.0f);

//         // Right face (x = 1.0f)
//         glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
//         glVertex3f(1.0f,  1.0f, -1.0f);
//         glVertex3f(1.0f,  1.0f,  1.0f);
//         glVertex3f(1.0f, -1.0f,  1.0f);
//         glVertex3f(1.0f, -1.0f, -1.0f);
//     glEnd();  // End of drawing color-cube
// }

// /* Draw a pyramid centered at the origin */
// void drawPyramid() {
//     glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
//         // Front
//         glColor3f(1.0f, 0.0f, 0.0f);     // Red
//         glVertex3f( 0.0f, 1.0f, 0.0f);
//         glColor3f(0.0f, 1.0f, 0.0f);     // Green
//         glVertex3f(-1.0f, -1.0f, 1.0f);
//         glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//         glVertex3f(1.0f, -1.0f, 1.0f);

//         // Right
//         glColor3f(1.0f, 0.0f, 0.0f);     // Red
//         glVertex3f(0.0f, 1.0f, 0.0f);
//         glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//         glVertex3f(1.0f, -1.0f, 1.0f);
//         glColor3f(0.0f, 1.0f, 0.0f);     // Green
//         glVertex3f(1.0f, -1.0f, -1.0f);

//         // Back
//         glColor3f(1.0f, 0.0f, 0.0f);     // Red
//         glVertex3f(0.0f, 1.0f, 0.0f);
//         glColor3f(0.0f, 1.0f, 0.0f);     // Green
//         glVertex3f(1.0f, -1.0f, -1.0f);
//         glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//         glVertex3f(-1.0f, -1.0f, -1.0f);

//         // Left
//         glColor3f(1.0f,0.0f,0.0f);       // Red
//         glVertex3f( 0.0f, 1.0f, 0.0f);
//         glColor3f(0.0f,0.0f,1.0f);       // Blue
//         glVertex3f(-1.0f,-1.0f,-1.0f);
//         glColor3f(0.0f,1.0f,0.0f);       // Green
//         glVertex3f(-1.0f,-1.0f, 1.0f);
//     glEnd();   // Done drawing the pyramid
// }

float sides=100.0f;

float scaledPoint(float x){
    return scaleFactor*(x-(1/3.0));
}

void drawCylinderSegment(float radius, float height, float startAngle, float endAngle) {
    float angleStep = (endAngle - startAngle) / sides;

    // Draw the sides of the cylinder

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= sides; i++) {
        float angle = startAngle + i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        glVertex3f(x, y, -height/2);               // Bottom vertex
        glVertex3f(x, y, height/2);              // Top vertex
    }
    glEnd();

    // Draw the top and bottom circles of the cylinder
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, -height/2);            // Center of the bottom circle
    for (int i = 0; i <= sides; i++) {
        float angle = startAngle + i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        glVertex3f(x, y, -height/2);               // Vertex on the bottom circle
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, height/2);           // Center of the top circle
    for (int i = sides; i >= 0; i--) {
        float angle = startAngle + i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        glVertex3f(x, y, height/2);              // Vertex on the top circle
    }
    glEnd();
}

void drawTriangle(){
    glPushMatrix();

    /*
        scaleFactor=>1  radius => 0
        scaleFactor =>0 radius => 1/sqrt(3)
    */

    



    glScalef(scaleFactor ,scaleFactor,scaleFactor);

    glTranslatef(1.0/(3*scaleFactor),1.0/(3*scaleFactor),1.0/(3*scaleFactor));


    glBegin(GL_TRIANGLES);

        
    glVertex3f(scaledPoint(1.0),scaledPoint(0.0),scaledPoint(0.0));
    glVertex3f(scaledPoint(0.0),scaledPoint(1.0),scaledPoint(0.0));
    glVertex3f(scaledPoint(0.0),scaledPoint(0.0),scaledPoint(1.0));

    glEnd();
    
    glPopMatrix();


    glPushMatrix();
    float finalRadius=1.0/sqrt(3);
    float currentRadius=(1.0-scaleFactor*scaleFactor)*finalRadius;


    /*
        scaleFactor=1 centerY =0
        scaleFactor=0 centerY=-1/sqrt(2)

    */

    float finalCenterY=1.0/sqrt(2);
    float currentCenter=(1.0-scaleFactor*scaleFactor)*finalCenterY;

    glColor3f(0.5f,0.0f,0.5f);
    glTranslatef(0,0.5f,0.5f);
    glRotatef(45.0f,1,0,0);
    glTranslatef(0,-currentCenter,0.0f);
    drawCylinderSegment(currentRadius,sqrt(2)*scaleFactor*scaleFactor,0.0f,360.0f);

    glPopMatrix();


    // glPushMatrix();

    // finalRadius=1.0/sqrt(3);
    // currentRadius=(1.0-scaleFactor*scaleFactor)*finalRadius;
    // finalCenterY=1.0/sqrt(2);
    // float currentCenter=(1.0-scaleFactor*scaleFactor)*finalCenterY;
    
    // glColor3f(0.5f,0.0f,0.5f);
    // glTranslatef(0.5,0.0f,0.5f);
    // //glRotatef(90.0f,0,1,0);
    // glRotatef(-45.0f,0,1,0);
    // //glTranslatef(0,-currentCenter,0.0f);
    // //drawAxes();
    // drawCylinderSegment(currentRadius,sqrt(2)*scaleFactor*scaleFactor,0.0f,360.0f);

    // glPopMatrix();


    // glPushMatrix();
    
    // glColor3f(0.5f,0.0f,0.5f);
    // glTranslatef(0.5,0.5f,0.0f);
    // glRotatef(90.0f,1,1,0);
    // //glRotatef(-45.0f,0,0,1);
    // //glTranslatef(0,-currentCenter,0.0f);
    // drawAxes();
    // drawCylinderSegment(currentRadius,sqrt(2)*scaleFactor*scaleFactor,0.0f,360.0f);

    // glPopMatrix();


    

    



}

void drawOctaHedron(){
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); 
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glColor3f(0.0f, 1.0f, 0.0f); 
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    glColor3f(0.0f, 0.0f, 1.0f); 
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    // glRotatef(270, 1, 0, 0);
    glColor3f(1.0f, 1.0f, 0.0f); 
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glColor3f(0.0f, 1.0f, 1.0f); 
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glColor3f(1.0f, 0.0f, 1.0f); 
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.0f, 1.0f, 1.0f); 
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    glRotatef(270, 0, 1, 0);
    glColor3f(1.0f, 1.0f, 1.0f); 
    drawTriangle();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    glColor3f(0.2f, 0.2f, 0.6f); 
    drawTriangle();
    glPopMatrix();


    glPushMatrix();


    glColor3f(0.5f, 0.5f, 0.0f); 
    
    float finalRadius=1.0/sqrt(3);
    float currentRadius=(1.0-scaleFactor*scaleFactor)*finalRadius;
    float initialCenter=1.0f;
    float currentCenter=scaleFactor*scaleFactor*initialCenter;
    Cubesphere sphere(currentRadius,3, true);
    
    glTranslatef(currentCenter,0,0);
    sphere.drawFace(0);
    
    glTranslatef(-currentCenter,0,0);
    glRotatef(90.0f,0,1,0);
    glTranslatef(currentCenter,0,0);
    sphere.drawFace(0);

    glTranslatef(-currentCenter,0,0);
    glRotatef(90.0f,0,1,0);
    glTranslatef(currentCenter,0,0);
    sphere.drawFace(0);

    glTranslatef(-currentCenter,0,0);
    glRotatef(90.0f,0,1,0);
    glTranslatef(currentCenter,0,0);
    sphere.drawFace(0);

    glTranslatef(-currentCenter,0,0);
    glRotatef(90.0f,0,0,1);
    glTranslatef(currentCenter,0,0);
    sphere.drawFace(0);

    glTranslatef(-currentCenter,0,0);
    glRotatef(180.0f,0,0,1);
    glTranslatef(currentCenter,0,0);
    sphere.drawFace(0);

    // sphere.drawFace(1);
    // sphere.drawFace(2);
    // sphere.drawFace(3);
    // sphere.drawFace(4);
    // sphere.drawFace(5);


    glPopMatrix();
    
}

/*  Handler for window-repaint event. Call back when the window first appears and
    whenever the window needs to be re-painted. */
void display() {
    // glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);             // To operate on Model-View matrix
    glLoadIdentity();                       // Reset the model-view matrix

    // default arguments of gluLookAt
    // gluLookAt(0,0,0, 0,0,-100, 0,1,0);

    // control viewing (or camera)
    gluLookAt(eyex,eyey,eyez,
              centerx,centery,centerz,
              upx,upy,upz);
    // draw


    drawAxes();
    
    //sphere1.draw();
    
    // glColor3f(1.0f, 0.0f, 0.0f); 
    // sphere.drawFace(0);
    // glColor3f(0.0f, 1.0f, 0.0f);
    // sphere.drawFace(1);
    // glColor3f(0.0f, 0.0f, 1.0f); 
    // sphere.drawFace(2);
    // glColor3f(1.0f, 1.0f, 0.0f); 
    // sphere.drawFace(3);
    // glColor3f(0.0f, 1.0f, 1.0f); 
    // sphere.drawFace(4);
    // glColor3f(1.0f, 0.0f, 1.0f); 
    // sphere.drawFace(5);

    drawOctaHedron();

    glutSwapBuffers();  // Render now
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshapeListener(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    /*if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }*/
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Callback handler for normal-key event */
void keyboardListener(unsigned char key, int x, int y) {
    float v = 0.1;
    switch (key) {
    // Control eye (location of the eye)
    // control eyex
    case '1':
        eyex += v;
        break;
    case '2':
        eyex -= v;
        break;
    // control eyey
    case '3':
        eyey += v;
        break;
    case '4':
        eyey -= v;
        break;
    // control eyez
    case '5':
        eyez += v;
        break;
    case '6':
        eyez -= v;
        break;

    case ',':
        if(scaleFactor>=scaleStep) scaleFactor-=scaleStep;
        break;
    case '.':
        if(scaleFactor<=1-scaleStep) scaleFactor+=scaleStep;
        break;

    // Control center (location where the eye is looking at)
    // control centerx
    case 'q':
        centerx += v;
        break;
    case 'w':
        centerx -= v;
        break;
    // control centery
    case 'e':
        centery += v;
        break;
    case 'r':
        centery -= v;
        break;
    // control centerz
    case 't':
        centerz += v;
        break;
    case 'y':
        centerz -= v;
        break;

    // Control what is shown
    case 'a':
        isAxes = !isAxes;   // show/hide Axes if 'a' is pressed
        break;
    case 'c':
        isCube = !isCube;   // show/hide Cube if 'c' is pressed
        break;
    case 'p':
        isPyramid = !isPyramid; // show/hide Pyramid if 'p' is pressed
        break;

    // Control exit
    case 27:    // ESC key
        exit(0);    // Exit window
        break;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}

/* Callback handler for special-key event */
void specialKeyListener(int key, int x,int y) {
    double v = 0.25;
    double lx = centerx - eyex;
    double lz = centerz - eyez;
    double s;
    switch (key) {
    case GLUT_KEY_LEFT:
        eyex += v * (upy*lz);
        eyez += v * (-lx*upy);
        s = sqrt(eyex*eyex + eyez*eyez) / (4 * sqrt(2));
        eyex /= s;
        eyez /= s;
        break;
    case GLUT_KEY_RIGHT:
        eyex += v * (-upy*lz);
        eyez += v * (lx*upy);
        s = sqrt(eyex*eyex + eyez*eyez) / (4 * sqrt(2));
        eyex /= s;
        eyez /= s;
        break;
    case GLUT_KEY_UP:
        eyey += v;
        break;
    case GLUT_KEY_DOWN:
        eyey -= v;
        break;
    
    default:
        return;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitWindowSize(640, 640);               // Set the window's initial width & height
    glutInitWindowPosition(50, 50);             // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("OpenGL 3D Drawing");      // Create a window with the given title
    glutDisplayFunc(display);                   // Register display callback handler for window re-paint
    glutReshapeFunc(reshapeListener);           // Register callback handler for window re-shape
    glutKeyboardFunc(keyboardListener);         // Register callback handler for normal-key event
    glutSpecialFunc(specialKeyListener);        // Register callback handler for special-key event
    initGL();                                   // Our own OpenGL initialization
    glutMainLoop();                             // Enter the event-processing loop
    return 0;
}