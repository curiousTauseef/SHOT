/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Stefan Vigerske, GAMS Development Corp.

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/

#pragma once
#include "NLPSolverBase.h"

#include "gmomcc.h"
#include "gevmcc.h"

namespace SHOT
{
class NLPSolverGAMS : public NLPSolverBase
{
private:
    gmoHandle_t modelingObject;
    gevHandle_t modelingEnvironment;

    std::string nlpsolver;
    std::string nlpsolveropt;
    double timelimit;
    int iterlimit;
    bool showlog;

public:
    NLPSolverGAMS(EnvironmentPtr envPtr, gmoHandle_t modelingObject);

    ~NLPSolverGAMS() override;

    void setStartingPoint(VectorInteger variableIndexes, VectorDouble variableValues) override;
    void clearStartingPoint() override;

    void fixVariables(VectorInteger variableIndexes, VectorDouble variableValues) override;

    void unfixVariables() override;

    void saveOptionsToFile(std::string fileName) override;

    void saveProblemToFile(std::string fileName) override;

    VectorDouble getSolution() override;
    double getSolution(int i) override;

    double getObjectiveValue() override;

    void updateVariableLowerBound(int variableIndex, double bound) override;
    void updateVariableUpperBound(int variableIndex, double bound) override;

    std::string getSolverVersion() override { return (std::to_string(GAMSMAJOR) + "." + std::to_string(GAMSMINOR)); };

protected:
    E_NLPSolutionStatus solveProblemInstance() override;

    VectorDouble getVariableLowerBounds() override;
    VectorDouble getVariableUpperBounds() override;

private:
};
} // namespace SHOT