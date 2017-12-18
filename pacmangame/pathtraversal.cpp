#include "pathtraversal.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include<cstdlib>
#include "node.h"
using namespace std;



pathTraversal::pathTraversal()
{
    pathTraversal::n=new int(18);
    pathTraversal::m=new int(22);
    pathTraversal::dir=new int(4);



}

pathTraversal::~pathTraversal()
{
    //dtor
}



// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
string pathTraversal::pathFind( const int & xStart, const int & yStart,
                 const int & xFinish, const int & yFinish,char mazeMap[22][18],bool guard )
{
    static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    static int map[18][22];
    static int closed_nodes_map[18][22]; // map of closed (tried-out) nodes
    static int open_nodes_map[18][22]; // map of open (not-yet-tried) nodes
    static int dir_map[18][22]; // map of directions
    pqi=0;
    cout<<*n<<" "<<*m<<" "<<*dir<<endl;
    for(int t=0;t<*m;t++)
    {
        for(int r=0;r<*n;r++) map[r][t]=0;
    }



    for(int t=0;t<22;t++){
        for(int r=0;r<18;r++){
            if(mazeMap[t][r]=='w'||mazeMap[t][r]=='r'||mazeMap[t][r]=='b'||mazeMap[t][r]=='i'||mazeMap[t][r]=='o'){
                if(mazeMap[t][r]=='w')
                map[r][t]=1;
                if(guard)
                map[r][t]=1;

                }
        }
    }

    // reset the node maps
    for(y=0;y<*m;y++)
    {
        for(x=0;x<*n;x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }

    // create the start node and push into list of open nodes
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y]=n0->getPriority(); // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish)
        {
            // generate the path from finish to start
            // by following the directions
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+*dir/2)%*dir;

                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].pop();
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for(i=0;i<*dir;i++)
        {

            xdx=x+dx[i]; ydy=y+dy[i];
            if(!(xdx<0 || xdx>*n-1 || ydy<0 || ydy>*m-1 || map[xdx][ydy]==1
                || closed_nodes_map[xdx][ydy]==1))
            {
                // generate a child node
                m0=new node( xdx, ydy, n0->getLevel(),
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);
                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(i+*dir/2)%*dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+*dir/2)%*dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().getxPos()==xdx &&
                           pq[pqi].top().getyPos()==ydy))
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pq[pqi].pop(); // remove the wanted node

                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }


    return ""; // no route found
}




vector<string> pathTraversal::pathDirections(char mazeMap[22][18],int xPosGhost,int yPosGhost,int xPosPacMan,int yPosPacMan,bool guard){
    //srand(time(NULL));

    vector<string> pathVector;






    // randomly select start and finish locations
    int xA=xPosGhost; int yA=yPosGhost;int xB=xPosPacMan;int yB=yPosPacMan;


    cout<<"Map Size (X,Y): "<<*n<<","<<*m<<endl;
    cout<<"Start: "<<xA<<","<<yA<<endl;
    cout<<"Finish: "<<xB<<","<<yB<<endl;
    // get the route
    clock_t start = clock();
    string route=pathFind(xA, yA, xB, yB,mazeMap,guard);
    if(route=="") cout<<"An empty route generated!"<<endl;
    clock_t end = clock();
    double time_elapsed = double(end - start);
    cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
    cout<<"Route:"<<endl;
    cout<<route<<endl<<endl;

    if(route!=""){
    for(unsigned int i=0;i<(route.size());i++){
    switch(route[i]){
                    case '1':
                        cout<<"Down ";
                        pathVector.push_back("Down");
                        break;

                    case '0':
                        cout<<"Right ";
                        pathVector.push_back("Right");
                        break;
                    case '2':
                        cout<<"Left ";
                        pathVector.push_back("Left");
                        break;
                    case '3':
                        cout<<"Up ";
                        pathVector.push_back("Up");
                        break;
                    default:
                        cout<<" ";
                        break;
                }
                cout<<endl;
                }
                }

    else{
        pathVector.push_back("Null");
    }

    // follow the route on the map and display it
   /* if(route.length()>0)
    {
        int j; char c;
        int x=xA;
        int y=yA;
        map[x][y]=2;
        for(int i=0;i<route.length();i++)
        {
            c =route.at(i);
            j=atoi(&c);
            x=x+dx[j];
            y=y+dy[j];
            map[x][y]=3;
        }
        map[x][y]=4;

        // display the map with the route
        for(int y=0;y<*m;y++)
        {
            for(int x=0;x<*n;x++)
                if(map[x][y]==0)
                    cout<<" ";
                else if(map[x][y]==1)
                    cout<<"O"; //obstacle
                else if(map[x][y]==2)
                    cout<<"S"; //start
                else if(map[x][y]==3)
                    cout<<"."; //route
                else if(map[x][y]==4)
                    cout<<"F"; //finish
            cout<<endl;
        }
    }*/
//    getchar(); // wait for a (Enter) keypress


    return pathVector;
}

