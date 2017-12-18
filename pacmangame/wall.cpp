#include "wall.h"
#include"objloader.h"


void wall::draw(int id1){

glPushMatrix();


     //draw body
    //
     //glTranslatef(-12,0,0);
    // glRotatef(angle, 0, 1, 0);
glScalef(0.5,0.5,0.5);
glCallList(id1);

glPopMatrix();
}

void wall::render(){
    glPushMatrix();

  // wall::draw();

    glPopMatrix();

}
 wall::wall(){


}
wall::~wall(){
}
