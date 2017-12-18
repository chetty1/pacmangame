#ifndef RED_GHOST_H
#define RED_GHOST_H


class red_ghost
{
    public:
        red_ghost();
        void draw(int i,int red,int dark);
        void render(int i,int red,int dark);
        float angle;
        virtual ~red_ghost();
    protected:
    private:
};

#endif // RED_GHOST_H
