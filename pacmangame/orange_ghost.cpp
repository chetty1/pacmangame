#include "orange_ghost.h"
#include <GL/glu.h>
#include<GL/glut.h>
#include<iostream>
#include"objloader.h"



void orange_ghost::draw(int i,int orange,int dark){
if(i == 0){
glPushMatrix();

     //draw body
     glTranslatef(-12,0,0);
    // glRotatef(angle, 0, 1, 0);

glCallList(orange);

glPopMatrix();
}
else {
glPushMatrix();

     //draw body
     glTranslatef(-12,0,0);
    // glRotatef(angle, 0, 1, 0);

glCallList(dark);

glPopMatrix();
}

}

void orange_ghost::render(int i,int orange,int dark){
    glPushMatrix();

    draw(i,orange, dark);

    glPopMatrix();

}

orange_ghost::orange_ghost()
{
    //ctor
}

orange_ghost::~orange_ghost()
{
    //dtor
}
