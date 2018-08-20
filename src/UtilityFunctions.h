/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE 
   This software is licensed under the Eclipse Public License 2.0. 
   Please see the README and LICENSE files for more information.
*/

#pragma once
#include <ostream>
#include "boost/format.hpp"
#include <math.h>
#include <stdio.h>
#include <cmath>
#include <boost/math/special_functions/fpclassify.hpp> // isnan
#include "Structs.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cerrno>
#include "OSInstance.h"

// Fix for missing NAN i Visual Studio
#ifdef WIN32
#ifndef NAN
static const unsigned long __nan[2] =
    {0xffffffff, 0x7fffffff};
#define NAN (*(const float *)__nan)
#endif
#endif

// Fix for Visual Studio c++ compiler
namespace SHOT::UtilityFunctions
{
int round(double d);

bool isnan(double val);

void saveVariablePointVectorToFile(VectorDouble point, VectorString variables,
                                   std::string fileName);

void savePrimalSolutionToFile(PrimalSolution solution, VectorString variables, std::string fileName);

bool isObjectiveGenerallyNonlinear(OSInstance *instance);
bool isObjectiveQuadratic(OSInstance *instance);
bool areAllConstraintsLinear(OSInstance *instance);
bool areAllConstraintsQuadratic(OSInstance *instance);
bool areAllVariablesReal(OSInstance *instance);

void displayVector(VectorDouble point);
void displayVector(VectorDouble point1, VectorDouble point2);
void displayVector(VectorInteger point);
void displayVector(VectorString point);
void displayVector(VectorInteger point1, VectorInteger point2);
void displayVector(VectorInteger point1, VectorDouble point2);

void displayVector(std::vector<VectorDouble> points);
void displayVector(std::vector<VectorInteger> points);
void displayVector(std::vector<VectorString> points);

void displayDifferencesInVector(VectorDouble point1, VectorDouble point2, double tol);

double L2Norm(VectorDouble ptA, VectorDouble ptB);
VectorDouble L2Norms(std::vector<VectorDouble> ptsA, VectorDouble ptB);
VectorDouble calculateCenterPoint(std::vector<VectorDouble> pts);

int numDifferentRoundedSelectedElements(VectorDouble firstPt, VectorDouble secondPt,
                                        VectorInteger indexes);
bool isDifferentRoundedSelectedElements(VectorDouble firstPt, VectorDouble secondPt,
                                        VectorInteger indexes);

bool isDifferentSelectedElements(VectorDouble firstPt, VectorDouble secondPt,
                                 VectorInteger indexes);

std::string toStringFormat(double value, std::string format, bool useInfinitySymbol);
std::string toStringFormat(double value, std::string format);
std::string toString(double value);

double getJulianFractionalDate();

bool writeStringToFile(std::string fileName, std::string str);

std::string getFileAsString(std::string fileName);
} // namespace SHOT::UtilityFunctions
