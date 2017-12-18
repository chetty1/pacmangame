#include "node.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include<cstdlib>
#include "pathtraversal.h"
using namespace std;

node::node(int xp, int yp, int d, int p)
{
    xPos=xp; yPos=yp; level=d; priority=p;
}

node::~node()
{
    //dtor
}




        int node::getxPos() const {return node::xPos;}
        int node::getyPos() const {return node::yPos;}
        int node::getLevel() const {return node::level;}
        int node::getPriority() const {return node::priority;}

        void node::updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        // give better priority to going strait instead of diagonally
        void node::nextLevel(const int & i) // i: direction
        {
             level+=(4==8?(i%2==0?10:14):10);
        }

        // Estimation function for the remaining distance to the goal.
        const int & node::estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-node::xPos;
            yd=yDest-node::yPos;

            // Euclidian Distance
            d=static_cast<int>(sqrt(xd*xd+yd*yd));

            // Manhattan distance
            //d=abs(xd)+abs(yd);

            // Chebyshev distance
            //d=max(abs(xd), abs(yd));

            return(d);
        }

