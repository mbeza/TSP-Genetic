#ifndef FUNCTIONSTSP_H
#define FUNCTIONSTSP_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "MatrixGraph.h"
#include <algorithm>
#include "Timer.h"
#include <stack>
#include <cmath>
#include <vector>
#include <ctime>

using namespace std;

int genetic(MatrixGraph &, double*, int*);

void generatePopulation(vector<vector<int>>&, int, int);

void cross(vector<vector<int>>&,int);

void mutation(vector<int>&,int);

void showPopulation(vector<vector<int>>&, int*);

void qSort(int* tab, vector<vector<int>>&, int l, int p);

int partition(int* tab, vector<vector<int>>&, int left, int right);

void getWeights(vector<vector<int>>&, int*, MatrixGraph&);

int* addWeightAfterCrossing(vector<vector<int>>&, int*, MatrixGraph&, int);

int changeWeight(int *, MatrixGraph&, vector<int>&, int);

int* selection(vector<vector<int>>&, int*, int);


#endif // !FUNCTIONSTSP_H
