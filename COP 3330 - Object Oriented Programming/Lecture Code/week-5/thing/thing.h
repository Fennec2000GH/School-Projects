#ifndef __THING_H
#define __THING_H

class Thing
{
public:
    Thing();
    Thing(int x);

    virtual ~Thing();

private:
    int* data;
};

#endif
