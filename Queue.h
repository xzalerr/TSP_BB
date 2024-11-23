#ifndef TSP_BB_QUEUE_H
#define TSP_BB_QUEUE_H
#include <iostream>
#include "Vector.h"
#include "ProblemSolver.h"

class Queue {
public:
    Vector<Node> vect;

    void push(Node value) {
        vect.push(value);
    }

    void pop() {
        for(int i = 0; i < vect.index-1; i++) {
            vect[i] = vect[i+1];
        }
        vect.pop();
    }

    Node front() {
        return vect[0];
    }

    bool empty() {
        if(vect.index==0) return true;
        else return false;
    }
};

#endif //TSP_BB_QUEUE_H
