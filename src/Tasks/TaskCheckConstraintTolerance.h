/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE 
   This software is licensed under the Eclipse Public License 2.0. 
   Please see the README and LICENSE files for more information.
*/

#pragma once
#include "TaskBase.h"
#include "../ProcessInfo.h"
#include "../OptProblems/OptProblemOriginal.h"
#include <algorithm>

namespace SHOT
{
class TaskCheckConstraintTolerance : public TaskBase
{
  public:
    TaskCheckConstraintTolerance(EnvironmentPtr envPtr, std::string taskIDTrue);
    virtual ~TaskCheckConstraintTolerance();

    virtual void run();

    virtual std::string getType();

  private:
    std::string taskIDIfTrue;

    bool isInitialized = false;
    // Without the (possible) nonlinear objective constraint
    VectorInteger nonlinearConstraintIndexes;
    bool isObjectiveNonlinear;
    int nonlinearObjectiveConstraintIndex;
};
} // namespace SHOT