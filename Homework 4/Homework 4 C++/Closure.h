#ifndef __CLOSURE_H
#define __CLOSURE_H

class Closure {
private:
    int x, y;

public:
    Closure(int _x, int _y) : x(_x), y(_y) {}

    int operator()(int a, int b) {
        return (x + y) * (a + b);
    }
};

#endif