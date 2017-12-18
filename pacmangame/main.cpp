#include <iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include "Camera.h"
#include "maze.h"
#include "pathtraversal.h"
#include "score.h"
#include "sound.h"
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include <ctime>
#include <cerrno>
#include <unistd.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "objloader.h"
#define MAX_ITEMS 4

using namespace std;

void manualGhostMovement(int i);
// Global variables
GLfloat DiffuseMaterial[] = {0.0, 1.0, 0.0, 0.0};
objloader obj;
float tx =1.5;
float ty =0.0;
float tz =40;
float angle1;
float gangle=0;
float r = 0.0;
float g = 0.0;
float b = 0.0;

int oldI=0;
int oldJ=0;

int speed=200;

bool attack=false;

Camera cam;
maze m(r,g,b,&attack);
pathTraversal p;
score s;
sound Sound;

int * last_x=&m.x_posPacman;
int* last_y=&m.y_posPacman;

int recul = 5;

int timing;
int moving;
int key1;
int lives = 5;
int Red_iter = 0;
int Blue_iter = 0;
int Purple_iter = 0;
int Yellow_iter = 0;
int Red_x_posGhost = 9;
int Red_y_posGhost = 8;
int Blue_x_posGhost = 9;
int Blue_y_posGhost = 9;
int Purple_x_posGhost = 10;
int Purple_y_posGhost = 8;
int Yellow_x_posGhost = 10;
int Yellow_y_posGhost = 9;
int oldx_posPacman =m.x_posPacman;
int oldy_posPacman =m.y_posPacman;
int iterat = 0;
int blue;
int red1;
int orange;
int pink;
int dark;
int wall;
int width;
int height;

bool fullOn = false;
bool searchRedPacMan=true;
bool onsearchRedPacMan=false;
bool searchBluePacMan=true;
bool onsearchBluePacMan=true;
bool searchPurplePacMan=true;
bool onsearchPurplePacMan=true;
bool searchYellowPacMan=true;
bool onsearchYellowPacMan=true;

char temp;//not used
static char Red_previousState='s';
static char Blue_previousState='s';
static char Purple_previousState='s';
static char Yellow_previousState='s';

char currentGhost='r';
int* currentx_posGhost = &Red_x_posGhost;
int* currenty_posGhost = &Red_y_posGhost;
char* currentpreviousState = &Red_previousState;
int motion = 0;
int previousmotion = 0;

sf::Text menu[MAX_ITEMS];
sf::Text gameOver;
sf::Text gameOver2;
sf::Text menu4;
sf::Font font;
sf::Font font2;
sf::Event event;
sf::Texture texture;
sf::Sprite pacmanImage;
sf::Texture texture2;
sf::Sprite pacmanImage2;

int selectedItemIndex;

string Score="0";
vector <string> Pacman_path;
vector<string> Red_path=(p.pathDirections(m.mazeMap,Red_y_posGhost,Red_x_posGhost,m.y_posPacman,m.x_posPacman,true));
vector<string> Blue_path=p.pathDirections(m.mazeMap,Blue_y_posGhost,Blue_x_posGhost,m.y_posPacman,m.x_posPacman,true);
vector<string> Purple_path=p.pathDirections(m.mazeMap,Purple_y_posGhost,Purple_x_posGhost,m.y_posPacman,m.x_posPacman,true);
vector<string> Yellow_path=p.pathDirections(m.mazeMap,Yellow_y_posGhost,Yellow_x_posGhost,m.y_posPacman,m.x_posPacman,true);
vector<string> tempPacman_path;
//vector<string> path=p.pathDirections(m.mazeMap,Blur_y_posGhost,Blue_x_posGhost,m.y_posPacman,m.x_posPacman);
/* Initialize OpenGL Graphics */
void initGL()
{
    // Set "clearing" or background color
    glClearColor(0.53,0.53, 0.53, 1); // White and opaque
    angle1=0.0;
    moving=0;
    gangle=0;

    glEnable(GL_DEPTH_TEST); // turns on hidden surface removal so that objects behind other objects do not get displayed
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
}

void win(){
bool endit;
for(int i = 0; i <m.lengthMap;i++){
    for(int j = 0;j<m.widthMap;j++){
        if (m.mazeMap[i][j]=='d'||m.mazeMap[i][j]=='D'){
            endit = false;
        break;
        }
        else{
            endit = true;
        }
    }
    if(endit==false){
        break;
    }
}
if(endit==true){
    exit(0);
}
}

void GameOver(){

if(!font2.loadFromFile("COOPBL.TTF")){


    cout<<"Error";

}

if(!font.loadFromFile("SHOWG.TTF")){


    cout<<"Error";

}

gameOver.setFont(font);
gameOver.setColor(sf::Color::White);
gameOver.setPosition(sf::Vector2f(260,250));
gameOver.setScale(5.f,5.f);
gameOver.setString("GAME OVER");

gameOver2.setFont(font2);
gameOver2.setColor(sf::Color::Red);
gameOver2.setPosition(sf::Vector2f(480,580));
gameOver2.setScale(1.f,1.f);
gameOver2.setString("[Press Space Bar TO Exit]");


}

void End(){

GameOver();

 sf::RenderWindow window2 (sf::VideoMode(600,600), "Pacman Menu",sf::Style::Fullscreen);
Sound.sound_4.stop();


    while(window2.isOpen()){

    while(window2.pollEvent(event)){

            switch(event.type){

            case sf::Event::Closed:
            window2.close();
            break;


             case sf::Event::KeyReleased:

                switch(event.key.code){

                case sf::Keyboard::Space:


                    exit(0);
                    break;

                }

    }
    }

    window2.clear();
    window2.draw(gameOver);
    window2.draw(gameOver2);
    window2.display();
    }
    }

void die(){
bool endit;
for(int i = 0; i <m.lengthMap;i++){
    for(int j = 0;j<m.widthMap;j++){
      //  if (!((m.x_posPacman==Red_x_posGhost&&m.y_posPacman==Red_y_posGhost)||(m.x_posPacman==Blue_x_posGhost&&m.y_posPacman==Blue_y_posGhost)||(m.x_posPacman==Purple_x_posGhost&&m.y_posPacman==Purple_y_posGhost)
       // ||(m.x_posPacman==Yellow_x_posGhost&&m.y_posPacman==Yellow_y_posGhost))){
            if(m.mazeMap[i][j]=='p'){
            endit = false;
        break;
        }
        else{
            endit = true;
        }
    }
    if(endit==false){
        break;
    }
}
if(endit==true && lives == 1){
    End();
glutHideWindow();
}
else if(endit==true && lives != 1){
    lives--;
    m.y_posPacman=8;
    m.x_posPacman = 16;
    m.mazeMap[Red_x_posGhost][Red_y_posGhost]=Red_previousState;
    m.mazeMap[Blue_x_posGhost][Blue_y_posGhost]=Blue_previousState;
    m.mazeMap[Purple_x_posGhost][Purple_y_posGhost]=Purple_previousState;
    m.mazeMap[Yellow_x_posGhost][Yellow_y_posGhost]=Yellow_previousState;
    Red_y_posGhost=8;
    Red_x_posGhost=9;
    Blue_y_posGhost=9;
    Blue_x_posGhost=9;

    Purple_x_posGhost = 10;
    Purple_y_posGhost = 8;
    Yellow_x_posGhost = 10;
    Yellow_y_posGhost = 9;
    Red_iter =0;
    Blue_iter =0;
    Purple_iter = 0;
    Yellow_iter = 0;
    Red_path=p.pathDirections(m.mazeMap,Red_y_posGhost,Red_x_posGhost,m.y_posPacman,m.x_posPacman,true);
    Blue_path=p.pathDirections(m.mazeMap,Blue_y_posGhost,Blue_x_posGhost,m.y_posPacman,m.x_posPacman,true);
    Purple_path=p.pathDirections(m.mazeMap,Purple_y_posGhost,Purple_x_posGhost,m.y_posPacman,m.x_posPacman,true);
    Yellow_path=p.pathDirections(m.mazeMap,Yellow_y_posGhost,Yellow_x_posGhost,m.y_posPacman,m.x_posPacman,true);
    Red_previousState = 's';
    Blue_previousState = 's';
    Purple_previousState = 's';
    Yellow_previousState = 's';
    m.mazeMap[16][8]='p';
    m.mazeMap[9][8]='r';
    if(onsearchBluePacMan)
    m.mazeMap[9][9]='b';
    m.mazeMap[10][8]='i';
    m.mazeMap[10][9]='o';
    if(onsearchRedPacMan)
    searchRedPacMan=true;
    if(onsearchBluePacMan)
    searchBluePacMan=true;
    if(onsearchPurplePacMan)
    searchPurplePacMan=true;
    if(onsearchYellowPacMan)
    searchYellowPacMan=true;
    m.motion=0;
    Sound.PacmanDieSound();
}
}


//This prints the Game Matrix on the console. Essential for debugging!
void printmazeMap(){
    for(int i=0;i<m.lengthMap;i++){
        for(int j=0;j<m.widthMap;j++){

            cout<<m.mazeMap[i][j]<<" ";

        }
            cout<<endl;
        }
        cout<<endl;
        m.Score();
        //cout<<m.points<<endl;
}

//Given the position of pacman, the move and the current matrix, pacman takes a move. (Collision detection engine inside!)
void movePacman(char mapp[22][18],int move,int* i,int* j){

    oldx_posPacman =m.x_posPacman;
    oldy_posPacman =m.y_posPacman;

    switch(move){

        case GLUT_KEY_LEFT:
            if((*j-1>=0)&&!(mapp[*i][*j-1]=='w')){
                mapp[*i][*j]='s';
                if(mapp[*i][*j-1]=='d'||mapp[*i][*j-1]=='D'){
                Sound.PacmanSound();}
                if((mapp[*i][*j-1]=='d')||(mapp[*i][*j-1]=='s')||(mapp[*i][*j-1]=='D'))
                mapp[*i][*j-1]='p';
                if(attack){
                if(mapp[*i][*j-1]=='b'){
                    searchBluePacMan=false;
                    onsearchBluePacMan=false;
                    }
                mapp[*i][*j-1]='p';
                }
                *j=*j-1;
                angle1= 90;
                if(mapp[*i][*j-1] == 't'){
                    mapp[*i][*j]='s';
                    *i=10;
                    *j=16;
                    mapp[*i][*j] ='p';
                }
                }
            break;

        case GLUT_KEY_RIGHT:
            if((*j+1<m.widthMap)&&!(mapp[*i][*j+1]=='w')){
                mapp[*i][*j]='s';
                if(mapp[*i][*j+1]=='d'||mapp[*i][*j+1]=='D'){
                Sound.PacmanSound();}
                if((mapp[*i][*j+1]=='d')||(mapp[*i][*j+1]=='s')||(mapp[*i][*j+1]=='D'))
                mapp[*i][*j+1]='p';
                if(attack){
                if(mapp[*i][*j+1]=='b'){
                    searchBluePacMan=false;
                    onsearchBluePacMan=false;
                    }
                mapp[*i][*j+1]='p';
                    }
                *j=*j+1;
                angle1= -90;
                if(mapp[*i][*j+1] == 't'){
                    mapp[*i][*j]='s';
                    *i=10;
                    *j=1;

                    mapp[*i][*j] ='p';

                }
                }
            break;

        case GLUT_KEY_DOWN:
            if((*i+1<m.lengthMap)&&!(mapp[*i+1][*j]=='w')){
                mapp[*i][*j]='s';
                if(mapp[*i+1][*j]=='d'||mapp[*i+1][*j]=='D'){
                Sound.PacmanSound();}
                if((mapp[*i+1][*j]=='d')||(mapp[*i+1][*j]=='s')||(mapp[*i+1][*j]=='D'))
                mapp[*i+1][*j]='p';
                if(attack){
                if(mapp[*i+1][*j]=='b'){
                    searchBluePacMan=false;
                    onsearchBluePacMan=false;
                    }
                mapp[*i+1][*j]='p';
                    }
                *i=*i+1;
                angle1 =180;
                }
            break;

        case GLUT_KEY_UP:
            if((*i-1>=0)&&!(mapp[*i-1][*j]=='w')){
                mapp[*i][*j]='s';
                if(mapp[*i-1][*j]=='d'||mapp[*i-1][*j]=='D'){
                Sound.PacmanSound();}
                if((mapp[*i-1][*j]=='d')||(mapp[*i-1][*j]=='s')||(mapp[*i-1][*j]=='D'))
                mapp[*i-1][*j]='p';
                if(attack){
                if(mapp[*i-1][*j]=='b'){
                    searchBluePacMan=false;
                    onsearchBluePacMan=false;
                    }
                mapp[*i-1][*j]='p';
                    }
                *i=*i-1;
                angle1 =0;
                }
            break;




}
    die();
    win();

}

void moveGhost(char mapp[22][18],int move,int* i,int* j,char ghost,char *previousState){

/*
    if(move==GLUT_KEY_LEFT){
        if(mapp[*i][*j-1]=='w'){
            move = previousmotion;
            motion=previousmotion;
            }
            }
    else if(move==GLUT_KEY_RIGHT){
        if(mapp[*i][*j+1]=='w'){
            move = previousmotion;
            motion=previousmotion;
            }}

    else if(move==GLUT_KEY_UP){
        if(mapp[*i-1][*j]=='w'){
            move = previousmotion;
            motion=previousmotion;
            }}
    else if(move==GLUT_KEY_DOWN){
        if(mapp[*i+1][*j]=='w'){
            move = previousmotion;
            motion=previousmotion;
            }}*/


    switch(move){

        case GLUT_KEY_LEFT:
            if((*j-1>=0)&&!(mapp[*i][*j-1]=='w')&&!(mapp[*i][*j-1]=='r')&&!(mapp[*i][*j-1]=='b')&&!(mapp[*i][*j-1]=='i')&&!(mapp[*i][*j-1]=='o')){
                if(ghost!=currentGhost&&!fullOn&&mapp[*i][*j-1]=='p'&&(onsearchBluePacMan||onsearchPurplePacMan||onsearchRedPacMan||onsearchYellowPacMan))
                break;
                mapp[*i][*j]=*previousState;
                *previousState=mapp[*i][*j-1];
                mapp[*i][*j-1]=ghost;
                *j=*j-1;
                if(*previousState=='p'&&!attack){
                    mapp[*i][*j]='s';
                    *previousState='s';
                    }
                gangle = -90;
                if(mapp[*i][*j-1] == 't'){
                    mapp[*i][*j]='s';
                    *i=10;
                    *j=16;
                    mapp[*i][*j] ='p';
                }
                }


            break;

        case GLUT_KEY_RIGHT:
            if((*j+1<m.widthMap)&&!(mapp[*i][*j+1]=='w')&&!(mapp[*i][*j+1]=='r')&&!(mapp[*i][*j+1]=='b')&&!(mapp[*i][*j+1]=='i')&&!(mapp[*i][*j+1]=='o')){
                if(ghost!=currentGhost&&!fullOn&&mapp[*i][*j+1]=='p'&&(onsearchBluePacMan||onsearchPurplePacMan||onsearchRedPacMan||onsearchYellowPacMan))
                break;
                mapp[*i][*j]=*previousState;
                *previousState=mapp[*i][*j+1];
                mapp[*i][*j+1]=ghost;
                if(*previousState=='p'&&!attack){
                    mapp[*i][*j+1]='s';
                    *previousState='s';
                    }
                *j=*j+1;
                gangle = 90;
                if(mapp[*i][*j+1] == 't'){
                    mapp[*i][*j]='s';
                    *i=10;
                    *j=1;

                    mapp[*i][*j] ='p';

                }
                }
            break;

        case GLUT_KEY_DOWN:
            if((*i+1<m.lengthMap)&&!(mapp[*i+1][*j]=='w')&&!(mapp[*i+1][*j]=='r')&&!(mapp[*i+1][*j]=='b')&&!(mapp[*i+1][*j]=='i')&&!(mapp[*i+1][*j]=='o')){
                if(ghost!=currentGhost&&!fullOn&&mapp[*i+1][*j]=='p'&&(onsearchBluePacMan||onsearchPurplePacMan||onsearchRedPacMan||onsearchYellowPacMan))
                break;
                mapp[*i][*j]=*previousState;
                *previousState=mapp[*i+1][*j];
                mapp[*i+1][*j]=ghost;
                if(*previousState=='p'&&!attack){
                    mapp[*i+1][*j]='s';
                    *previousState='s';
                    }
                *i=*i+1;
                gangle = 0;
                }
            break;

        case GLUT_KEY_UP:
            if((*i-1>=0)&&!(mapp[*i-1][*j]=='w')&&!(mapp[*i-1][*j]=='r')&&!(mapp[*i-1][*j]=='b')&&!(mapp[*i-1][*j]=='i')&&!(mapp[*i-1][*j]=='o')){
                if(ghost!=currentGhost&&!fullOn&&mapp[*i-1][*j]=='p'&&(onsearchBluePacMan||onsearchPurplePacMan||onsearchRedPacMan||onsearchYellowPacMan))
                break;
                mapp[*i][*j]=*previousState;
                *previousState=mapp[*i-1][*j];
                mapp[*i-1][*j]=ghost;
                if(*previousState=='p'&&!attack){
                    mapp[*i-1][*j]='s';
                    *previousState='s';
                    }
                *i=*i-1;
                gangle = 180;
                }
            break;


    }
    die();
    win();

}
bool test=true;



void movePacmanAI(int i){


    int curI=0;
    int curJ=0;
    //srand(time(NULL));
   /* for(int i = 0;i<22;i++){
        for(int j=0;j<18;j++){
            if((m.mazeMap[i][j]=='d'||m.mazeMap[i][j]=='D')){
                //tempPacman_path = p.pathDirections(m.mazeMap,m.y_posPacman,m.x_posPacman,j,i);
                if(Pacman_path.size()<=shortestPath){
                cout<<"Path size:"<<Pacman_path.size()<<endl;
                    Pacman_path = p.pathDirections(m.mazeMap,m.y_posPacman,m.x_posPacman,j,i);
                    shortestPath = Pacman_path.size();
                    curI=i;
                    curJ=j;
                }
            }
        }

        }*/

        test=false;

        int xPos = *last_x;
        int yPos = *last_y;
        bool found=false;
        int shortestPath = 1000;



        while(!found){

        for(int i=xPos-recul;i<=xPos+recul;i++){
            for(int j=yPos-recul;j<=yPos+recul;j++){
                if(i<=0||i>=m.lengthMap||j<=0||j>=m.widthMap)
                    continue;

                 if(m.mazeMap[i][j]=='d'||m.mazeMap[i][j]=='D'){
                 //tempPacman_path = p.pathDirections(m.mazeMap,m.y_posPacman,m.x_posPacman,j,i);

                // if(tempPacman_path.size()<shortestPath){
                    Pacman_path = p.pathDirections(m.mazeMap,*last_y,*last_x,j,i,true);
                  //  shortestPath=Pacman_path.size();
                     found=true;
                     recul=1;
                     curI=i;
                     curJ=j;

                     }


                 //}
            }

        }


        if(!found){
        cout<<"Not found"<<endl;
        recul++;
        }


        }



        /*if(curI==oldI&&curJ==oldJ&&iterat<Pacman_path.size()-1)
            iterat++;
        else{
            iterat=0;
            oldI=curI;
            oldJ=curJ;
            }*/

        if(attack)
            Pacman_path=p.pathDirections(m.mazeMap,m.y_posPacman,m.x_posPacman,Blue_y_posGhost,Blue_x_posGhost,false);

    //if(m.mazeMap[curI][curJ]=='D'&&!attack){
      //               attack=true;
            //         }

    if((Pacman_path).at(0)=="Left")
        movePacman(m.mazeMap,GLUT_KEY_LEFT,last_x,last_y);

    else if((Pacman_path).at(0)=="Right")
        movePacman(m.mazeMap,GLUT_KEY_RIGHT,last_x,last_y);
    else if((Pacman_path).at(0)=="Up")
        movePacman(m.mazeMap,GLUT_KEY_UP,last_x,last_y);
    else if((Pacman_path).at(0)=="Down")
        movePacman(m.mazeMap,GLUT_KEY_DOWN,last_x,last_y);

    //if(attack&&m.x_posPacman==Red_x_posGhost&&m.y_posPacman==Red_y_posGhost)


    glutTimerFunc(60,movePacmanAI,100);
   // usleep(1*1000000);
    //movePacmanAI(0);
}



void GhostMovement(int *x_posGhost,int *y_posGhost,bool *searchPacMan,vector<string> *path,int* iter,char ghost,char *previousState){

    if(*searchPacMan){
    if(!(oldx_posPacman==m.x_posPacman&&oldy_posPacman==m.y_posPacman)){
        (*path)=p.pathDirections(m.mazeMap,*y_posGhost,*x_posGhost,m.y_posPacman,m.x_posPacman,true);
        *iter=0;
    }

    else{
        if(*iter<(*path).size()-1)
        *iter=*iter+1;
    }
    }


     if(!(*x_posGhost==m.x_posPacman&&*y_posGhost==m.y_posPacman)&&*searchPacMan){

    if((*path).at(*iter)=="Left")
        moveGhost(m.mazeMap,GLUT_KEY_LEFT,x_posGhost,y_posGhost,ghost,previousState);

    else if((*path).at(*iter)=="Right")
        moveGhost(m.mazeMap,GLUT_KEY_RIGHT,x_posGhost,y_posGhost,ghost,previousState);
    else if((*path).at(*iter)=="Up")
        moveGhost(m.mazeMap,GLUT_KEY_UP,x_posGhost,y_posGhost,ghost,previousState);
    else if((*path).at(*iter)=="Down")
        moveGhost(m.mazeMap,GLUT_KEY_DOWN,x_posGhost,y_posGhost,ghost,previousState);

        /*if(*iter<(*path).size()){
        *iter=*iter+1;
        cout<<"Path size:"<<(*path).size()<<endl;
        }*/



    }

    else{
        searchPacMan=false;
    }

    die();
    win();


}

void manualGhostMovement(int i){
    moveGhost(m.mazeMap,motion,currentx_posGhost,currenty_posGhost,currentGhost,currentpreviousState);
    previousmotion=motion;
    glutTimerFunc(speed,manualGhostMovement,0);
}

void manualPacmanMovement(int i){
    movePacman(m.mazeMap,motion,&m.x_posPacman,&m.y_posPacman);
    glutTimerFunc(speed,manualPacmanMovement,0);
}



void update(int i)
{
    timing = glutGet(GLUT_ELAPSED_TIME); // get the elapsed time in milliseconds since glutInit() was executed
    // do nothing
    if(onsearchRedPacMan&&!attack)
    GhostMovement(&Red_x_posGhost,&Red_y_posGhost,&searchRedPacMan,&Red_path,&Red_iter,'r',&Red_previousState);
    if(onsearchBluePacMan&&!attack)
    GhostMovement(&Blue_x_posGhost,&Blue_y_posGhost,&searchBluePacMan,&Blue_path,&Blue_iter,'b',&Blue_previousState);
    if(onsearchPurplePacMan&&!attack)
    GhostMovement(&Purple_x_posGhost,&Purple_y_posGhost,&searchPurplePacMan,&Purple_path,&Purple_iter,'i',&Purple_previousState);
    if(onsearchYellowPacMan&&!attack)
    GhostMovement(&Yellow_x_posGhost,&Yellow_y_posGhost,&searchYellowPacMan,&Yellow_path,&Yellow_iter,'o',&Yellow_previousState);

/*
    if(r ==0.0) //changes the mouth to yellow
    {
    r +=1.0;
    g +=1.0;
    }

else                     //changes the mouth to black
    {
    r -=1.0;
    g -=1.0;
    }*/
    glutTimerFunc(300,update,0);
}

void Red(int i){
    if(onsearchRedPacMan&&!attack)
    GhostMovement(&Red_x_posGhost,&Red_y_posGhost,&searchRedPacMan,&Red_path,&Red_iter,'r',&Red_previousState);
    glutTimerFunc(500,Red,0);
}

void Blue(int i){
if(onsearchBluePacMan&&!attack)
    GhostMovement(&Blue_x_posGhost,&Blue_y_posGhost,&searchBluePacMan,&Blue_path,&Blue_iter,'b',&Blue_previousState);
    glutTimerFunc(450,Blue,0);
    }

void Purple(int i){
    if(onsearchPurplePacMan&&!attack)
    GhostMovement(&Purple_x_posGhost,&Purple_y_posGhost,&searchPurplePacMan,&Purple_path,&Purple_iter,'i',&Purple_previousState);
    glutTimerFunc(400,Purple,0);
    }

void Yellow(int i){
    if(onsearchYellowPacMan&&!attack)
    GhostMovement(&Yellow_x_posGhost,&Yellow_y_posGhost,&searchYellowPacMan,&Yellow_path,&Yellow_iter,'o',&Yellow_previousState);
    glutTimerFunc(350,Yellow,0);
}

void threadPacman(){
    movePacmanAI(0);
}

void threadGhosts(){
    update(0);
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */

void reshape(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
width = w;
height = h;
blue=obj.load("blue.obj");
orange = obj.load("yellow.obj");
pink=obj.load("pink.obj");
red1=obj.load("red.obj");
dark=obj.load("dark.obj");
wall=obj.load("bok.obj");

}

void PressNormalKeys(unsigned char key,int x,int y){
    switch(key){
        /*case 'r':
            cam.init();
            break;*/

        case 'q':
            cam.lookUp();
            break;

        case 'a':
            cam.lookDown();
            break;

        case 'e':
            cam.moveUp();
            break;

        case 'd':
            cam.moveDown();
            break;

        case 27:
            exit(0);
        break;

        case 'w':
            cam.moveForward();
            break;

        case 's':
            cam.moveBackward();
            break;

        case 'z':
            cam.turnLeft();
            break;

        case 'x':
            cam.turnRight();
            break;
        case 'b':
            onsearchRedPacMan=true;
            onsearchYellowPacMan=true;
            onsearchPurplePacMan=true;
            onsearchBluePacMan=false;
            currentGhost='b';
            currentpreviousState=&Blue_previousState;
            currentx_posGhost=&Blue_x_posGhost;
            currenty_posGhost=&Blue_y_posGhost;
            break;
        case 'r':
            onsearchRedPacMan=false;
            onsearchBluePacMan=true;
            onsearchYellowPacMan=true;
            onsearchPurplePacMan=true;
            currentGhost='r';
            currentpreviousState=&Red_previousState;
            currentx_posGhost=&Red_x_posGhost;
            currenty_posGhost=&Red_y_posGhost;
            break;
        case 'y':
            onsearchRedPacMan=true;
            onsearchBluePacMan=true;
            onsearchYellowPacMan=false;
            onsearchPurplePacMan=true;
            currentGhost='o';
            currentpreviousState=&Yellow_previousState;
            currentx_posGhost=&Yellow_x_posGhost;
            currenty_posGhost=&Yellow_y_posGhost;
            break;

        case 'p':
            onsearchRedPacMan=true;
            onsearchBluePacMan=true;
            onsearchYellowPacMan=true;
            onsearchPurplePacMan=false;
            currentGhost='i';
            currentpreviousState=&Purple_previousState;
            currentx_posGhost=&Purple_x_posGhost;
            currenty_posGhost=&Purple_y_posGhost;
            break;

    }
    glutPostRedisplay();
}

void update1(int value){
switch(key1){
case 1:
    tx-=1;
    break;
case 2:
    tx+=1;
    break;
case 3:
    tz -=1;
    break;
case 4:
    tz +=1;
    break;
}
    //if(!(Red_x_posGhost==m.x_posPacman&&Red_y_posGhost==m.y_posPacman)&&searchRedPacMan)
    //movePacman(m.mazeMap,m.motion,&m.x_posPacman,&m.y_posPacman);



    glutPostRedisplay(); //Tell GLUT that the display has changed
    glutTimerFunc(200,update1,0);
	//Tell GLUT to call update again in 25 milliseconds

    }
void PressSpecialKeys(int key,int x,int y){

    previousmotion=motion;
    switch(key){

        case GLUT_KEY_UP:
           key1= 4;
           m.motion = GLUT_KEY_UP;
            motion = GLUT_KEY_UP;
            break;

        case GLUT_KEY_DOWN:
           key1=3;
           m.motion = GLUT_KEY_DOWN;
           motion = GLUT_KEY_DOWN;
            break;

        case GLUT_KEY_LEFT:
           key1=2;
           m.motion = GLUT_KEY_LEFT;
           motion = GLUT_KEY_LEFT;
            break;

        case GLUT_KEY_RIGHT:
           key1=1;
           m.motion = GLUT_KEY_RIGHT;
           motion = GLUT_KEY_RIGHT;
            break;


    }
    glutPostRedisplay();
}

void moveMouse(int button, int state, int x, int y){
    // move left
    if(x < 600 && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
     cam.turnLeft();
    }
    //move right
    else  if (x>600 && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
     cam.turnRight();
    }
    //zoom out
    else if (y>550 && button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
     cam.moveBackward();
    }
    //zoom in
    else if (y < 550&& button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
    cam.moveForward();
    }
}

void initDisp(){
    glClear (GL_COLOR_BUFFER_BIT);
    glFlush();
}



void render()
{
    // GL_DEPTH_BUFFER_BIT - resets the depth test values for hidden surface removal
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(height== 0)	height = 1;

    GLfloat ratio = 1.0f * (GLfloat)width / (GLfloat)height;

    // Set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the clipping volume
    gluPerspective(45, ratio, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
    // Reset transformations

    // Set the camera
    cam.lookAt();

    glRotatef(-25,1.0,0.0,0.0);

    glPushMatrix();
    glTranslatef(17,0,21);
    glScalef(2,2,2);
    glRotatef(180,0,1,0);
    m.drawMap(angle1,gangle,blue,orange,pink,red1,dark,wall);
    glPopMatrix();

    //Take note!!! If running in windows: this is is system("cls") not system("clear"). Well to my knowledge!
    system("clear");



    glPushMatrix();
    s.writing(lives,m.points);
    glPopMatrix();

    printmazeMap();
    glMatrixMode(GL_PROJECTION);
    glRotatef(moving,0,1,0);
    moving=0;
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    glEnable(GL_DEPTH_TEST);

if (height==0) height=1;
    // Set the viewport to be the entire window
    glViewport(width-200, height-200, 200, 200);

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the clipping volume
    gluPerspective(45, 16/9, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Reset transformations

    // Set the camera
    cam.miniMap();

    glRotatef(-25,1.0,0.0,0.0);

    glPushMatrix();
    glTranslatef(17,0,21);
    glScalef(2,2,2);
    glRotatef(180,0,1,0);
    m.drawMap(angle1,gangle,blue,orange,pink,red1,dark,wall);
    glPopMatrix();

    //Take note!!! If running in windows: this is is system("cls") not system("clear"). Well to my knowledge!
    system("clear");



    glPushMatrix();
    s.writing(1,m.points);
    glPopMatrix();

    printmazeMap();
    //glMatrixMode(GL_PROJECTION);
    glRotatef(moving,0,1,0);
    moving=0;



    //update(0);
    //update1(0);

    glFlush();   // ******** DO NOT FORGET THIS **********

}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{

    /*render();
        if(height == 0)	height = 1;

   // GLfloat ratio = 1.0f * (GLfloat)width / (GLfloat)height;

    // Set the viewport to be the entire window
    glViewport(width-200, height-200, 200, 200);
    glScissor(width-149,height-200,149,149);
    glEnable(GL_SCISSOR_TEST);

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the clipping volume
    gluPerspective(45, ratio, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    render();*/
    render();

}

void Menu (int item)
{

glutDisplayFunc(display);
}




void menuText(){

if(!font.loadFromFile("COOPBL.TTF")){


    cout<<"Error";

}

if(!font2.loadFromFile("SHOWG.TTF")){


    cout<<"Error";

}


if(!texture.loadFromFile("pacman.jpg")){

    cout<<"Error";

}


if(!texture2.loadFromFile("ghosts.png")){

    cout<<"Error";

}

menu[0].setFont(font);
menu[0].setColor(sf::Color::Red);
menu[0].setPosition(sf::Vector2f(510,500));
menu[0].setString("SINGLE PLAYER");

menu[1].setFont(font);
menu[1].setColor(sf::Color::White);
menu[1].setPosition(sf::Vector2f(510,550));
menu[1].setString("PLAY AS GHOST");

menu[2].setFont(font);
menu[2].setColor(sf::Color::White);
menu[2].setPosition(sf::Vector2f(590,600));
menu[2].setString("DEMO");

menu[3].setFont(font);
menu[3].setColor(sf::Color::White);
menu[3].setPosition(sf::Vector2f(600,650));
menu[3].setString("EXIT");



menu4.setFont(font2);
menu4.setColor(sf::Color::White);
menu4.setScale(5.f,5.f);
menu4.setPosition(sf::Vector2f(300,70));
menu4.setString("Pa          man");

pacmanImage.setTexture(texture);
pacmanImage.setPosition(400,45);
pacmanImage.setScale(0.8,0.8);

pacmanImage2.setTexture(texture2);
pacmanImage2.setPosition(440,330);
pacmanImage2.setScale(0.5,0.5);

selectedItemIndex = 0;


}

void moveUp(){

  if(selectedItemIndex -1 >=0){


    menu[selectedItemIndex].setColor(sf::Color::White);
    selectedItemIndex--;
    menu[selectedItemIndex].setColor(sf::Color::Red);


  }

}

void moveDown(){

  if(selectedItemIndex +1 < MAX_ITEMS){


    menu[selectedItemIndex].setColor(sf::Color::White);
    selectedItemIndex++;
    menu[selectedItemIndex].setColor(sf::Color::Red);


  }

}


int getPressedItem(){

    return selectedItemIndex;

    }

    void PacMenu(){


        sf::RenderWindow window (sf::VideoMode(600,600), "Pacman Menu",sf::Style::Fullscreen);
        menuText();
        Sound.OpeningSound();

    while(window.isOpen()){

    while(window.pollEvent(event)){

            switch(event.type){

            case sf::Event::Closed:
            window.close();
            break;


            case sf::Event::KeyReleased:

                switch(event.key.code){

                case sf::Keyboard::Up:
                    moveUp();
                    break;

                    case sf::Keyboard::Down:
                    moveDown();
                    break;

                    case sf::Keyboard::Return:

                        switch(getPressedItem()){

                        case 0 ://single player
                            glutInitWindowSize(1280, 680);
                            glutInitWindowPosition(50, 50);
                            glutCreateWindow("Pac-Man");
                            glutDisplayFunc(display);
                            speed=30;

                            onsearchRedPacMan=true;

                            fullOn=true;
                            Red(0);
                            Blue(0);
                            Yellow(0);
                            Purple(0);
                            update1(0);
                            manualPacmanMovement(0);
                            Sound.Siren();
                            window.close();
                            break;

                        case 1://Play as ghost
                            glutInitWindowSize(1280, 680);
                            glutInitWindowPosition(50, 50);
                            glutCreateWindow("Pac-Man");
                            glutDisplayFunc(display);
                            speed=150;

                            movePacmanAI(0);
                            Red(0);
                            Blue(0);
                            Yellow(0);
                            Purple(0);
                            update1(0);
                            manualGhostMovement(0);
                            Sound.Siren();
                            window.close();

                        break;

                        case 2://pacman with Ai
                            glutInitWindowSize(1280, 680);
                            glutInitWindowPosition(50, 50);
                            glutCreateWindow("Pac-Man");
                            glutDisplayFunc(display);


                            movePacmanAI(0);
                            Red(0);
                            Blue(0);
                            Yellow(0);
                            Purple(0);
                            update1(0);
                            onsearchRedPacMan=true;
                            fullOn=true;
                            Sound.Siren();
                            window.close();
                        break;

                        case 3://exit
                            exit(0);
                            break;
                        break;
                        }
                }
            }
    }
    window.clear();

    for(int i = 0; i<MAX_ITEMS;i++){
         window.draw(menu[i]);
    }
    window.draw(pacmanImage);
    window.draw(menu4);
    window.draw(pacmanImage2);
    window.display();

    }

        }

int main(int argc, char** argv)
{
sf::Thread pacmanThread(&threadPacman);

    glutInit(&argc, argv);          // Initialize GLUT


    //sf::Thread ghostThread(&threadGhosts);

    PacMenu();
    glutCreateMenu (Menu);
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutFullScreen();
    glutKeyboardFunc(PressNormalKeys);
    glutSpecialFunc(PressSpecialKeys);// Register callback handler for window re-paint even

    glutMouseFunc(moveMouse);

    //ghostThread.launch();

	//pacmanThread.launch();

    initGL();// Our own OpenGL initialization

    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
