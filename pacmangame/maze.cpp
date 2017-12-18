#include "maze.h"
#include "pacman.h"
#include<GL/glut.h>
#include<GL/glu.h>
#include "blue_ghost.h"
#include "red_ghost.h"
#include "orange_ghost.h"
#include "pink_ghost.h"
#include "wall.h"
#include "objloader.h"
#include "sound.h"
int id ;
objloader obj7;
GLfloat mblueDiffuseMaterial[] = {0.0, 0.0, 1.0, 0.0};
GLfloat mgreenDiffuseMaterial[] = {1.0, 1.0, 1.0, 0.0};

blue_ghost bg;
red_ghost rg;
orange_ghost og;
pink_ghost pg;
wall w ;
sound RetreatSound;


float re =0;
float gr =0;
float bl =0;
float temp_time;

bool dot1 = false;//for the Power Dots
bool dot2 = false;
bool dot3 = false;
bool dot4 = false;
bool *att;

PacMan pman(re,gr,bl);

maze::maze(float a, float e, float c,bool* attac)
{
//angl = ang;
re=a;
gr=e;
bl=c;
att=attac;

}
//This is the dimension of the Game Matrix. Need to remain constant!
maze::maze(){}

//This draws the Map on openGl. Take note that this function uses local variables. Take account of that when seperating classes.
void maze::drawMap(float angle, float ghost_angle,int blue ,int orange,int pink,int red,int dark,int wall){

if ((mazeMap[1][1] == 'p'&& dot1==false)||(mazeMap[20][1] == 'p'&& dot2==false)||(mazeMap[1][16] == 'p'&& dot3==false)||(mazeMap[20][16] == 'p'&& dot4==false)){
    temp_time = glutGet(GLUT_ELAPSED_TIME);
    //edible=1;
    RetreatSound.RetreatGhost();
    }
else{
if(glutGet(GLUT_ELAPSED_TIME) > (temp_time+(5100))){
    RetreatSound.sound_5.stop();
    edible = 0;
    *att=false;
}
}
if(mazeMap[1][1] == 's'&& dot1==false){
    dot1=true;
}
if(mazeMap[20][1] == 's'&& dot2==false){
    dot2=true;
}
if(mazeMap[1][16] == 's'&& dot3==false){
    dot3=true;
}
if(mazeMap[20][16] == 's'&& dot4==false){
    dot4=true;
}

for(int i=0;i<lengthMap;i++){
        for(int j=0;j<widthMap;j++){
            switch(mazeMap[i][j]){



                case 'd':
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,mgreenDiffuseMaterial);
                    glutSolidSphere(0.2,100,100);
                break;

                case 'D':
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,mgreenDiffuseMaterial);
                    glutSolidSphere(0.4,100,100);
                break;

                case 'p':
                    glShadeModel(GL_SMOOTH);
                    glPushMatrix();
                    glTranslatef(0,0,5);
                    glScalef(0.17,0.17,0.17);
                    pman.display(angle);
                    glPopMatrix();
                    break;
                case 'r':
                    glPushMatrix();
                    glShadeModel(GL_SMOOTH);
                    glTranslatef(3.6,0,0);
                    glScalef(0.3,0.5,0.3);
                    rg.render(edible,red,dark);
                    glPopMatrix();
                break;

                case 'b':
                    glPushMatrix();
                    glShadeModel(GL_SMOOTH);
                    glTranslatef(3.5,0,0);
                    glScalef(0.3,0.5,0.3);
                    bg.render(edible,blue,dark);
                    glPopMatrix();
                break;

                case 'o':
                    glPushMatrix();
                    glShadeModel(GL_SMOOTH);
                    glTranslatef(3.5,0,0);
                    glScalef(0.3,0.5,0.3);
                    og.render(edible,orange,dark);
                    glPopMatrix();
                break;

                case 'i':
                    glPushMatrix();
                    glShadeModel(GL_SMOOTH);
                    glTranslatef(3.6,0,0);
                    glScalef(0.3,0.5,0.3);
                    pg.render(edible,pink,dark);
                    glPopMatrix();
                break;
                case 'w':
              //  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mblueDiffuseMaterial);

                   // glutSolidCube(1);
glPushMatrix();
                    w.draw(wall);
                    glDisable(GL_TEXTURE_2D);
                    glPopMatrix();
                break;

            }
            glTranslatef(1,0,0);
        }
        glTranslatef(-18,0,1);
    }
}

void maze::Score(){
int dots_left=0;
int power_left=0;
for(int i = 0; i < 23;i++){
    for(int j = 0; j < 18; j++){
        if(mazeMap[i][j]== 'd'){
            dots_left++;
        }
        if(mazeMap[i][j]=='D'){
            power_left++;
        }
    }
}
points=((maxdots-dots_left)*10)+((powerDots-power_left)*50);

}

maze::~maze()
{
    //dtor
}
