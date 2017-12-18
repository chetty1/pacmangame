#ifndef NODE_H
#define NODE_H
#include "pathtraversal.h"

class node
{
    public:
        node(int xp, int yp, int d, int p);
        virtual ~node();
        int getxPos() const;
        int getyPos() const;
        int getLevel() const;
        int getPriority() const;
        void updatePriority(const int & xDest, const int & yDest);
        void nextLevel(const int & i);
    protected:
    private:

        // current position
        int xPos;
        int yPos;
        // total distance already travelled to reach the node
        int level;
        // priority=level+remaining distance estimate
        int priority;  // smaller: higher priority
        const int & estimate(const int & xDest, const int & yDest) const;
};

#endif // NODE_H
