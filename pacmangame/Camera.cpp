
#include "Camera.h"
#include <math.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;
Camera::Camera(){
    init();
}

float distance(float x1, float x2, float z1, float z2)
{
    float d1 = pow(x2 - x1, 2);
    float d2 = pow(z2 - z1, 2);
    float sum = d1 + d2;
    return sqrt(sum);
}

void Camera::init(){
    angle = 90;
    eye_x = 0;
    eye_y = 17;
    eye_z = -50;
    at_x = 0;
    at_z = 0;
    at_y = 0;
    radius = distance(eye_x,at_x,eye_z,at_z);
}
void Camera::miniMap(){
gluLookAt(0,50,-20,at_x,at_y,at_z,0,1,0);
glutPostRedisplay();
}



void Camera::lookAt(){
        gluLookAt(eye_x, eye_y, eye_z, // camera position
                  at_x, at_y, at_z, // look at position, line of sight
                  0, 1, 0); // up direction (vector) for camera tilt
        glutPostRedisplay();
}

void Camera::lookUp(){
    at_y += shift;
}

void Camera::lookDown(){
     at_y -= shift;
}

void Camera::turnRight(){
   angle+=angleshift;
         at_x = eye_x+(radius*cos(angle*M_PI/180));
        at_z = eye_z-(radius*-sin(angle*M_PI/180));
}

void Camera::turnLeft(){
      angle-=angleshift;
       at_x = eye_x+(radius*cos(angle*M_PI/180));
        at_z = eye_z-(radius*-sin(angle*M_PI/180));
}

void Camera::moveForward(){
   eye_x += cos(angle*M_PI/180);
        eye_z -= -sin(angle*M_PI/180);
        at_x = eye_x+(radius*cos(angle*M_PI/180));
        at_z = eye_z-(radius*-sin(angle*M_PI/180));
        }

void Camera::moveBackward(){
   eye_x -= cos(angle*M_PI/180);
        eye_z += -sin(angle*M_PI/180);
        at_x = eye_x+(radius*cos(angle*M_PI/180));
        at_z = eye_z-(radius*-sin(angle*M_PI/180));
}

void Camera::moveUp(){
    eye_y++;
    }

void Camera::moveDown(){
    eye_y--;
}



