#include "blue_ghost.h"
#include <GL/glu.h>
#include<GL/glut.h>
#include<iostream>
#include "objloader.h"


void blue_ghost::draw(int i,int blue,int dark){
if(i == 0){
glPushMatrix();
     //draw body
     glTranslatef(-12, 0, 0);
     //glRotatef(180,0,1,0);
    glCallList(blue);


glPopMatrix();
}
else {
glPushMatrix();
     //draw body
     glTranslatef(-12, 0, 0);
     //glRotatef(180,0,1,0);
    glCallList(dark);


glPopMatrix();
}

}

void blue_ghost::render(int i,int blue , int dark){
    glPushMatrix();
    draw(i,blue,dark);
    glPopMatrix();

}

blue_ghost::blue_ghost()
{
    //ctor
}

blue_ghost::~blue_ghost()
{
    //dtor
}
