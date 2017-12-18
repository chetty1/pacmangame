#ifndef WALL_H
#define WALL_H


class wall
{
    public:
        wall();
        int id1;
        virtual ~wall();
        void draw(int id);
        void render();
    protected:
    private:
};

#endif // WALL_H
