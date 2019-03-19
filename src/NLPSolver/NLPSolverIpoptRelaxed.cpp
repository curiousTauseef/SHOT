/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/

#include "NLPSolverIpoptRelaxed.h"

namespace SHOT
{

NLPSolverIpoptRelaxed::NLPSolverIpoptRelaxed(EnvironmentPtr envPtr, ProblemPtr source) : INLPSolver(envPtr)
{
    sourceProblem = source;

    for(auto& V : sourceProblem->allVariables)
        originalVariableType.push_back(V->type);

    lowerBounds = sourceProblem->getVariableLowerBounds();
    upperBounds = sourceProblem->getVariableUpperBounds();
}

NLPSolverIpoptRelaxed::~NLPSolverIpoptRelaxed() {}

void NLPSolverIpoptRelaxed::setSolverSpecificInitialSettings()
{
    ipoptApplication->Options()->SetNumericValue(
        "constr_viol_tol", env->settings->getDoubleSetting("Ipopt.ConstraintViolationTolerance", "Subsolver") + 1e-12);

    ipoptApplication->Options()->SetNumericValue(
        "tol", env->settings->getDoubleSetting("Ipopt.RelativeConvergenceTolerance", "Subsolver") + 1e-12);

    ipoptApplication->Options()->SetIntegerValue(
        "max_iter", env->settings->getIntSetting("Ipopt.MaxIterations", "Subsolver"));

    ipoptApplication->Options()->SetNumericValue(
        "max_cpu_time", env->settings->getDoubleSetting("FixedInteger.TimeLimit", "Primal"));
}

VectorDouble NLPSolverIpoptRelaxed::getSolution() { return (NLPSolverIpoptBase::getSolution()); }
} // namespace SHOT