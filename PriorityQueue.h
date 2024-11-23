#ifndef TSP_BB_PRIORITYQUEUE_H
#define TSP_BB_PRIORITYQUEUE_H
#include <iostream>
#include "Vector.h"
#include "ProblemSolver.h"

class PriorityQueue {
public:
    Vector<Node> vect;

    void push(Node value) {
        vect.push(value);

        for (int i = 0; i < vect.index; i++) {
            for (int j = 0; j < vect.index - i - 1; j++) {
                if (vect[j].cost > vect[j + 1].cost) {
                    Node temp = vect[j];
                    vect[j] = vect[j + 1];
                    vect[j + 1] = temp;
                }
            }
        }
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

#endif //TSP_BB_PRIORITYQUEUE_H
