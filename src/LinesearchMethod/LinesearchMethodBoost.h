/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE 
   This software is licensed under the Eclipse Public License 2.0. 
   Please see the README and LICENSE files for more information.
*/

#pragma once
#include "ILinesearchMethod.h"
#include "SHOTSettings.h"
#include "../Model.h"
#include "../OptProblems/OptProblemOriginal.h"
#include "../ProcessInfo.h"

#include "boost/math/tools/roots.hpp"

namespace SHOT
{
class Test
{
  private:
    EnvironmentPtr env;
    VectorInteger nonlinearConstraints;

  public:
    VectorDouble firstPt;
    VectorDouble secondPt;

    double valFirstPt;
    double valSecondPt;

    Test(EnvironmentPtr envPtr);
    ~Test();
    void determineActiveConstraints(double constrTol);
    void setActiveConstraints(VectorInteger constrIdxs);
    VectorInteger getActiveConstraints();
    void clearActiveConstraints();
    void addActiveConstraint(int constrIdx);

    double operator()(const double x);
};

class TerminationCondition
{
  private:
    double tol;

  public:
    TerminationCondition(double tolerance)
    {
        tol = tolerance;
    }

    bool operator()(double min, double max)
    {
        return (abs(min - max) <= tol);
    }
};

class LinesearchMethodBoost : public ILinesearchMethod
{
  public:
    LinesearchMethodBoost(EnvironmentPtr envPtr);
    virtual ~LinesearchMethodBoost();

    virtual std::pair<VectorDouble, VectorDouble> findZero(VectorDouble ptA,
                                                           VectorDouble ptB, int Nmax, double lambdaTol, double constrTol);

    virtual std::pair<VectorDouble, VectorDouble> findZero(VectorDouble ptA,
                                                           VectorDouble ptB, int Nmax, double lambdaTol, double constrTol, VectorInteger constrIdxs);

  private:
    Test *test;
    EnvironmentPtr env;
};
} // namespace SHOT