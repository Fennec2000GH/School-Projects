#ifndef DIAMOND_H
#define DIAMOND_H

class Diamond
{
    public:
        //constructors
        Diamond(int s, char b = '#', char f = '*');

        //accessors
        int GetSize();
        int Perimeter();
        double Area();

        //mutators
        void Grow();
        void Shrink();
        void SetBorder(char b);
        void SetFill(char f);

        //information display
        void Draw();
        void Summary();

    private:
        int size;
        char border, fill;
};

#endif
