#include "pink_ghost.h"
#include <GL/glu.h>
#include<GL/glut.h>
#include<iostream>
#include "objloader.h"



void pink_ghost::draw(int i,int pink,int dark){
if(i == 0){
glPushMatrix();
     //draw body
     glTranslatef(-12,0,0);
    glCallList(pink);

glPopMatrix();
}
else {
glPushMatrix();
     //draw body
     glTranslatef(-12,0,0);
    glCallList(dark);

glPopMatrix();}

}

void pink_ghost::render(int i,int pink,int dark){
    glPushMatrix();
    draw(i,pink,dark);
    glPopMatrix();

}


pink_ghost::pink_ghost()
{
    //ctor
}

pink_ghost::~pink_ghost()
{
    //dtor
}
