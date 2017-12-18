#include "pacman.h"
#include<GL/glut.h>

GLfloat yellowDiffuseMaterial[] = {1.0,1.0,0.0, 0.0};
GLfloat pmblackDiffuseMaterial[] = {0.0, 0.0, 0.0, 0.0};
GLfloat pmwhiteDiffuseMaterial[] = {1.0, 1.0, 1.0, 0.0};

void PacMan::draw(float angle)
{
    //draw Body
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,yellowDiffuseMaterial);
     glTranslatef(0.0, 1.1, -30);
     glutSolidSphere(3, 50, 50);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,pmblackDiffuseMaterial);
     glRotatef(angle,0,1,0);

     //draw eyes
     glPushMatrix();
     glTranslatef(-1.2, 1.2, -2.5);
     glutSolidSphere(0.5,50,50);
     glPopMatrix();

     glPushMatrix();
     glTranslatef(1.2, 1.2, -2.5);
     glutSolidSphere(0.5,50,50);
     glPopMatrix();

     GLfloat changeDiffuseMaterial[] = {r,g,b, 0.0};
     //draw mouth
     glPushMatrix();
     glTranslatef(0, -0.7, -1.28);

     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,changeDiffuseMaterial);
     glutSolidSphere(1.8,50,50);
     glPopMatrix();

}

void PacMan::render(float angle){
     glPushMatrix();
     draw(angle);    //draw PacMan
     glPopMatrix();
}

void PacMan::update()
{
    time = glutGet(GLUT_ELAPSED_TIME); // get the elapsed time in milliseconds since glutInit() was executed
if(r ==0.0) //changes the mouth to yellow
    {
    r +=1.0;
    g +=1.0;
    }

else                     //changes the mouth to black
    {
    r -=1.0;
    g -=1.0;
    }

}
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void PacMan::display(float angle)
{
    update();
    render(angle);
}


PacMan::PacMan(float r, float g, float b)
{
    this->b = b;
    this ->r = r;
    this->g = g;
    //ctor
}

PacMan::~PacMan()
{
    //dtor
}
