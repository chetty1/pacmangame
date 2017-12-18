#ifndef MAZE_H
#define MAZE_H
#include "pacman.h"


class maze
{
    public:
        maze(float r, float g, float b,bool* attack);
        maze();
        const int widthMap=18;
const int lengthMap=22;


float angl=180;

//This is the initial position of pacman on the Game Matrix
int x_posPacman = 16;
int y_posPacman = 8;

//This tracks the position Pacman is moving Initially set to no movement
int motion = 0;

int edible = 0;
int maxdots=149;
int powerDots = 4;
long int points=0;

//This is the Game Matrix. Important!!
char mazeMap[22][18] = {
{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
{'w','D','d','d','d','d','d','d','w','w','d','d','d','d','d','d','D','w'},
{'w','d','w','w','d','w','w','d','w','w','d','w','w','d','w','w','d','w'},
{'w','d','w','w','d','w','w','d','w','w','d','w','w','d','w','w','d','w'},
{'w','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','w'},
{'w','d','w','w','d','w','d','w','w','w','w','d','w','d','w','w','d','w'},
{'w','d','d','d','d','w','d','d','w','w','d','d','w','d','d','d','d','w'},
{'w','w','w','w','d','w','w','d','w','w','d','w','w','d','w','w','w','w'},
{'s','s','s','w','d','w','s','s','s','s','s','s','w','d','w','s','s','s'},
{'w','w','w','w','d','w','s','w','r','b','w','s','w','d','w','w','w','w'},
{'t','d','d','d','d','s','s','w','i','o','w','s','s','d','d','d','d','t'},
{'w','w','w','w','d','w','s','w','w','w','w','s','w','d','w','w','w','w'},
{'s','s','s','w','d','w','s','s','s','s','s','s','w','d','w','s','s','s'},
{'w','w','w','w','d','w','s','w','w','w','w','s','w','d','w','w','w','w'},
{'w','d','d','d','d','d','d','d','w','w','d','d','d','d','d','d','d','w'},
{'w','d','w','w','d','w','w','d','w','w','d','w','w','d','w','w','d','w'},
{'w','d','d','w','d','d','d','d','p','d','d','d','d','d','w','d','d','w'},
{'w','w','d','w','d','w','d','w','w','w','w','d','w','d','w','d','w','w'},
{'w','d','d','d','d','w','d','d','w','w','d','d','w','d','d','d','d','w'},
{'w','d','w','w','w','w','w','d','w','w','d','w','w','w','w','w','d','w'},
{'w','D','d','d','d','d','d','d','d','d','d','d','d','d','d','d','D','w'},
{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
};


//int*p[widthMap]= mazeMap;

        void drawMap(float angle,float ghost_angle,int blue,int orange,int pink, int red,int dark,int wall);
        void Score();
        virtual ~maze();
    protected:
    private:

};

#endif // MAZE_H
