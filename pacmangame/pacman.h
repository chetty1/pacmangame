#ifndef PACMAN_H
#define PACMAN_H


class PacMan
{
    public:
        PacMan(float r, float g, float b);
        void draw(float angle);
        void render(float angle);
        void update();
        void display(float angle);
        virtual ~PacMan();
    protected:
    private:
    int time;
    double r,g,b;
};

#endif // PACMAN_H
