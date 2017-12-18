#include "score.h"
#include<GL/glut.h>
#include<GL/glu.h>
#include <string.h>
#include <strstream>
#include<sstream>
#include<stdio.h>

score::score()
{
    //ctor
}
GLfloat nmyellowDiffuseMaterial[] = {1.0, 1.0, 0.0, 0.0};
GLfloat ScoreRedDiffuseMaterial[] = {1.0, 0.0, 0.0, 0.0};

void score::writing(int lives,int points){

glPushMatrix();

    glPushMatrix();
    glTranslatef(28,19.5,0);
    glScalef(0.015,0.015,0.015);
    glRotatef(180,0,1,0);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,ScoreRedDiffuseMaterial);

    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'C');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'O');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'R');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'E');
    glPopMatrix();

    std::ostringstream strm;
    strm<<points;
    std::string numstr = strm.str();
    char meh[numstr.length()-1];
    strcpy(meh,numstr.c_str());

    glPushMatrix();
    glTranslatef(20,19.5,0);
    glScalef(0.015,0.015,0.015);
    glRotatef(180,0,1,0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, meh[0]);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, meh[1]);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, meh[2]);
    if(points>99){
    glutStrokeCharacter(GLUT_STROKE_ROMAN, meh[3]);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(28,16.5,0);
    glScalef(0.015,0.015,0.015);
    glRotatef(180,0,1,0);

    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'I');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'V');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'E');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S');
    glPopMatrix();

glPopMatrix();

int xl = 21;

glPushMatrix();
for(int i = 1; i <= lives;i++,xl-=3){
    glPushMatrix();
    glTranslatef(xl,17,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,nmyellowDiffuseMaterial);
    glutSolidSphere(1,50,50);
    glPopMatrix();
}

glPopMatrix();

}

score::~score()
{
    //dtor
}
