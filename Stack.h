#ifndef TSP_BB_STACK_H
#define TSP_BB_STACK_H
#include <iostream>
#include "Vector.h"
#include "ProblemSolver.h"

class Stack {
public:
    Vector<Node> vect;

    void push(Node value) {
        vect.push(value);
    }

    void pop() {
        vect.pop();
    }

    Node top() {
        return vect[vect.index-1];
    }

    bool empty() {
        if(vect.index==0) return true;
        else return false;
    }
};

#endif //TSP_BB_STACK_H
