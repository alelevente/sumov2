//
// Created by levente on 2019.09.08..
//

#include "LPSolver.h"
#define USE_CBC
#include "ortools/include/ortools/linear_solver/linear_solver.h"

//using namespace operations_research;

operations_research::MPVariable** initializeVariables(int n, operations_research::MPSolver& solver){
    operations_research::MPVariable** answer = new operations_research::MPVariable*[n];
    for (int i=0; i<n; ++i) {
        answer[i] = solver.MakeIntVar(0.0,1.0, "xasf");
    }
    return answer;
}

void setConflictMatrix(std::vector<operations_research::MPVariable*>& mpVars, int** conflictMtx, int* addConstraints, operations_research::MPSolver& solver) {
    for (int i=0; i<conflictMtx[0][0]; ++i) {
        for (int j=i; j<conflictMtx[0][0]; ++j){
            if (conflictMtx[i][j] == 1) {
                operations_research::MPConstraint* c = solver.MakeRowConstraint(0, 1.0);
                c->SetCoefficient(mpVars[i], 1.0);
                c->SetCoefficient(mpVars[j], 1.0);
            }
        }
        if (addConstraints[i]==0 || addConstraints[i]==1) {
            operations_research::MPConstraint* c = solver.MakeRowConstraint(addConstraints[i], addConstraints[i]);
            c->SetCoefficient(mpVars[i], 1);
        }
    }
}

operations_research::MPObjective* makeOptimization(std::vector<operations_research::MPVariable*>& mpVars, int** conflictMtx, operations_research::MPSolver& solver){
    operations_research::MPObjective* objective = solver.MutableObjective();
    for (int i=0; i<conflictMtx[0][0]; ++i) {
        objective->SetCoefficient(mpVars[i], 1);
    }
    objective->SetMaximization();
    return objective;
}

std::vector<int> LPSolver::getLPSolution(int **conflictMtx, int *addConstraints) {
    operations_research::MPSolver solver("", operations_research::MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);
    std::vector<operations_research::MPVariable*> vars;
    solver.MakeIntVarArray(conflictMtx[0][0], 0.0, 1.0, "x", &vars);
    setConflictMatrix(vars, conflictMtx, addConstraints, solver);
    operations_research::MPObjective* objective = makeOptimization(vars, conflictMtx, solver);

    operations_research::MPSolver::ResultStatus result_status = solver.Solve();

    // Check that the problem has an optimal solution.
    if (result_status != operations_research::MPSolver::OPTIMAL) {
        std::cerr << "The problem does not have an optimal solution!";
    }

    std::vector<int> answer;

    //std::cout << "Solution:" << std::endl;
    //std::cout << "Optimal objective value = " << objective->Value() << std::endl;
    for (int i=0; i<conflictMtx[0][0]; ++i){
        if (vars[i]->solution_value() != 0){
            //std::cout << vars[i]->name() << std::endl;
            answer.insert(answer.end(), 1);
        } else answer.insert(answer.end(), 0);
    }

    solver.Clear();
    return answer;
}