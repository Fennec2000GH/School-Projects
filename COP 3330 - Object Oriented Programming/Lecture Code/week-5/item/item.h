#ifndef __ITEM_H
#define __ITEM_H

class Item 
{
    public:
          Item();                    // default constructor
          Item(int h, int w);        // constructor with parameters

          void Show() const;         // print the object status

          void Set(int h, int w);    // set height and weight

          int GetHeight() const;
          int GetWeight() const;  

    private:
          int height;
          int weight;
          const int LIMIT;  
          static const int SIZE = 10; // this is a static member variable,
                                      // which means there is only ONE
                                      // that every object shares
};

#endif
