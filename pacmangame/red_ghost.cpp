#include "red_ghost.h"
#include <GL/glu.h>
#include<GL/glut.h>
#include<iostream>
#include "objloader.h"



void red_ghost::draw(int i,int red,int dark){
if(i == 0){
glPushMatrix();

     //draw body

     glTranslatef(-12,0,0);
     //glRotatef(angle,0,1,0);
  glCallList(red);

glPopMatrix();
}
else {
glPushMatrix();

     //draw body

     glTranslatef(-12,0,0);
    // glRotatef(angle,0,1,0);
  glCallList(dark);

glPopMatrix();}

}

void red_ghost::render(int i,int red,int dark){
    glPushMatrix();
    draw(i,red,dark);
    glPopMatrix();

}

red_ghost::red_ghost()
{
    //ctor

}

red_ghost::~red_ghost()
{
    //dtor
}
