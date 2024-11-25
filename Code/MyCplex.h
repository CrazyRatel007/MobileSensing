#pragma once
#include "ilcp\cp.h"
#include "ilcplex/ilocplex.h"

#include <vector>

typedef IloArray<IloNumVarArray> NumVarMatrix;  //变量数组
typedef IloArray<NumVarMatrix> NumVar3Matrix;
typedef IloArray<NumVar3Matrix> NumVar4Matrix;
typedef IloArray<NumVar4Matrix> NumVar5Matrix;


typedef IloArray<IloNumArray> NumMatrix;        //常量数组
typedef IloArray<NumMatrix> Num3Matrix;
typedef IloArray<Num3Matrix> Num4Matrix;
typedef IloArray<Num4Matrix> Num5Matrix;

class MyCplex
{
public:
	IloEnv env;
	IloModel model;
	IloCplex cplex;
	IloObjective objective;  
	IloRangeArray constraints;
	IloNumVarArray vars;

public:
	NumVar3Matrix Define3DArray(int M,int N,int K);
	//IloNumVarArray Define1DArray(int M, IloNum pLowBound, std::vector<float> pUpBound, IloNumVar::Type pType, std::string pName);
	IloNumVarArray Define1DArray(int M, IloNum pLowBound, std::vector<float> pUpBound, IloNumVar::Type pType, std::string pName);
	NumVar4Matrix Define4DArray(int M, int N, int K, int W);
	NumVar5Matrix Define5DArray(int M, int N, int K, int W,int Q);

	MyCplex(void);
	void test();

	~MyCplex(void);
};

