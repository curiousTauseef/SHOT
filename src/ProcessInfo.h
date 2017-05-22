#pragma once
#include "Enums.h"
#include <vector>
#include <map>
#include "Iteration.h"
#include "Timer.h"

// Used for OSOutput
#include <cstdio>
#define HAVE_STDIO_H 1
#include "OSOutput.h"

#include "SHOTSettings.h"

#include "TaskHandler.h"

#include "OSResult.h"
#include "OSrLWriter.h"
#include "OSErrorClass.h"

#include "MILPSolver/IRelaxationStrategy.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class OptProblemOriginal;
class IMILPSolver;
class ILinesearchMethod;

#include <LinesearchMethod/ILinesearchMethod.h>

struct InteriorPoint
{
		vector<double> point;
		int NLPSolver;
		IndexValuePair maxDevatingConstraint;
};

struct PrimalSolution
{
		vector<double> point;
		E_PrimalSolutionSource sourceType;
		double objValue;
		int iterFound;
		IndexValuePair maxDevatingConstraint;
};

struct PrimalFixedNLPCandidate
{
		vector<double> point;
		E_PrimalNLPSource sourceType;
		double objValue;
		int iterFound;
		IndexValuePair maxDevatingConstraint;
};

struct DualSolution
{
		vector<double> point;
		E_DualSolutionSource sourceType;
		double objValue;
		int iterFound;
};

struct Hyperplane
{
		int sourceConstraintIndex;
		std::vector<double> generatedPoint;
		E_HyperplaneSource source;
};

class ProcessInfo
{
	public:
		static ProcessInfo* getInstance();

		OSResult *osResult;
		OptProblemOriginal *originalProblem;

		IMILPSolver *MILPSolver;
		IRelaxationStrategy *relaxationStrategy;

		TaskHandler *tasks;

		void initializeResults(int numObj, int numVar, int numConstr);

		~ProcessInfo()
		{
			instanceFlag = false;
		}

		vector<double> primalSolution; // TODO remove
		//double lastObjectiveValue; // TODO remove
		vector<Iteration> iterations;
		vector<PrimalSolution> primalSolutions;
		vector<DualSolution> dualSolutions;

		vector<PrimalSolution> primalSolutionCandidates;
		vector<PrimalFixedNLPCandidate> primalFixedNLPCandidates;
		vector<DualSolution> dualSolutionCandidates;

		pair<double, double> getCorrectedObjectiveBounds();

		void addPrimalSolution(vector<double> pt, E_PrimalSolutionSource source, double objVal, int iter,
				IndexValuePair maxConstrDev);
		void addPrimalSolution(vector<double> pt, E_PrimalSolutionSource source, double objVal, int iter);
		void addPrimalSolution(SolutionPoint pt, E_PrimalSolutionSource source);

		void addPrimalFixedNLPCandidate(vector<double> pt, E_PrimalNLPSource source, double objVal, int iter,
				IndexValuePair maxConstrDev);

		void addDualSolution(vector<double> pt, E_DualSolutionSource source, double objVal, int iter);
		void addDualSolution(SolutionPoint pt, E_DualSolutionSource source);
		void addDualSolution(DualSolution solution);
		void addPrimalSolutionCandidate(vector<double> pt, E_PrimalSolutionSource source, int iter);
		void addPrimalSolutionCandidates(vector<vector<double>> pts, E_PrimalSolutionSource source, int iter);

		void addPrimalSolutionCandidate(SolutionPoint pt, E_PrimalSolutionSource source);
		void addPrimalSolutionCandidates(std::vector<SolutionPoint> pts, E_PrimalSolutionSource source);

		void checkPrimalSolutionCandidates();
		void checkDualSolutionCandidates();

		bool isRelativeObjectiveGapToleranceMet();
		bool isAbsoluteObjectiveGapToleranceMet();

		void addDualSolutionCandidate(SolutionPoint pt, E_DualSolutionSource source);
		void addDualSolutionCandidates(std::vector<SolutionPoint> pts, E_DualSolutionSource source);
		void addDualSolutionCandidate(vector<double> pt, E_DualSolutionSource source, int iter);
		void addDualSolutionCandidate(DualSolution solution);

		std::pair<double, double> currentObjectiveBounds;
		double getAbsoluteObjectiveGap();
		double getRelativeObjectiveGap();
		void setObjectiveUpdatedByLinesearch(bool updated);
		bool getObjectiveUpdatedByLinesearch();

		int iterationCount;
		int iterLP;
		int iterQP;
		int iterFeasMILP;
		int iterOptMILP;
		int iterFeasMIQP;
		int iterOptMIQP;
		int iterFeasMIQCQP;
		int iterOptMIQCQP;

		int numNLPProbsSolved;
		int numPrimalFixedNLPProbsSolved;

		int itersWithStagnationMILP; // TODO move to task
		int iterSignificantObjectiveUpdate; // TODO move to task
		int itersMILPWithoutNLPCall; // TODO move to task
		double solTimeLastNLPCall; // TODO move to task

		int iterLastPrimalBoundUpdate;
		int iterLastDualBoundUpdate;

		double timeLastDualBoundUpdate;

		int lastLazyAddedIter;

		int numOriginalInteriorPoints;

		int numFunctionEvals;
		int numGradientEvals;

		int numConstraintsRemovedInPresolve;
		int numVariableBoundsTightenedInPresolve;
		int numIntegerCutsAdded;

		std::vector<int> itersSolvedAsECP;

		//double getLastMaxDeviation();
		void setOriginalProblem(OptProblemOriginal *problem);

		void createTimer(string name, string description);
		void startTimer(string name);
		void stopTimer(string name);
		void restartTimer(string name);
		double getElapsedTime(string name);

		double getPrimalBound();
		double getDualBound();

		Iteration *getCurrentIteration();
		Iteration *getPreviousIteration();

		E_TerminationReason terminationReason;

		std::string getOSrl();
		std::string getTraceResult();

		void createIteration();

		std::vector<InteriorPoint> interiorPts;

		std::vector<Hyperplane> hyperplaneWaitingList;

		std::vector<std::vector<int>> integerCutWaitingList;

		std::vector<Timer> timers;

		void outputAlways(std::string message);
		void outputError(std::string message);
		void outputError(std::string message, std::string errormessage);
		void outputSummary(std::string message);
		void outputWarning(std::string message);
		void outputInfo(std::string message);
		void outputDebug(std::string message);
		void outputTrace(std::string message);
		void outputDetailedTrace(std::string message);

		ILinesearchMethod *linesearchMethod;
	private:
		static bool instanceFlag;
		static ProcessInfo *single;
		SHOTSettings::Settings *settings;
		bool objectiveUpdatedByLinesearch;

		bool checkPrimalSolutionPoint(PrimalSolution primalSol);

		ProcessInfo();

};
