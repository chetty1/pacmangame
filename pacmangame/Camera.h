#ifndef CAMERA_H
#define CAMERA_H
#include <math.h>
class Camera
{
    public:
        Camera();
        void init();
        void lookAt();
        void lookUp();
        void lookDown();
        void turnLeft();
        void turnRight();
        void moveForward();
        void moveBackward();
        void moveUp();
        void moveDown();
        void miniMap();
        //float getAngleShift();

float eye_x = 0,eye_y = 17,eye_z= -50;
float at_x = 0, at_z = 0, at_y = 0;
float angle = 90;
float shift = 1;
float angleshift = 5;
float radius;
//float M_PI = 3.14;
//float fraction = 0.1;

};
#endif // CAMERA_H
