//
// Created by levente on 2019.09.08..
//

#ifndef LPSOLVER_LPSOLVER_H
#define LPSOLVER_LPSOLVER_H


#include <vector>

class LPSolver {
public:
    std::vector<int> getLPSolution(int** conflictMatrix, int* addConstraints);
};


#endif //LPSOLVER_LPSOLVER_H
