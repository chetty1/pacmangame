#ifndef PATHTRAVERSAL_H
#define PATHTRAVERSAL_H
#include <vector>
#include <string>
using namespace std;


class pathTraversal
{
    public:
        pathTraversal();
        virtual ~pathTraversal();
        vector<string> pathDirections(char mazeMap[22][18],int xPosGhost,int yPosGhost,int xPosPacMan,int yPosPacMan,bool guard);

    protected:
    private:
        const int* n; // horizontal size of the map
        const int* m; // vertical size size of the map
        const int* dir; // number of possible directions to go at any position


        //bool operator<(const node & a);

        // if dir==4
        int dx[4]={1,0,-1,0};
        int dy[4]={0, 1, 0, -1};
        string pathFind( const int & xStart, const int & yStart,
                 const int & xFinish, const int & yFinish,char mazeMap[22][18],bool guard );
};

#endif // PATHTRAVERSAL_H
