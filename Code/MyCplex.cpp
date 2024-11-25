#include "MyCplex.h"



MyCplex::MyCplex()
{
	model = IloModel(env, "myCplex");
	vars = IloNumVarArray(env);
	constraints = IloRangeArray(env);
}


MyCplex::~MyCplex()
{
	env.end();
}

IloNumVarArray MyCplex::Define1DArray(int M, IloNum pLowBound, std::vector<float> pUpBound, IloNumVar::Type pType, std::string pName)
{
	IloNumVarArray vars1D = IloNumVarArray(env, M);
	for (int k = 0; k < M; k++)
	{
		std::string tName = pName + "[" + std::to_string(k) + "]";
		vars1D[k] = IloNumVar(env, pLowBound, pUpBound[k], pType, tName.c_str());
	}
	return vars1D;
}

NumVar3Matrix MyCplex::Define3DArray(int M, int N, int K)
{
	NumVar3Matrix vars3D(env, M);

	for (int i = 0; i < M; i++)
	{
		vars3D[i] = NumVarMatrix(env, N);
		for (int j = 0; j < N; j++)
		{
			//vars3D[i][j] = IloNumVarArray(env, K, 0, 1, ILOINT);
			vars3D[i][j] = IloNumVarArray(env,K);
			for (int k = 0; k < K; k++)
			{
				std::string tName = "x[" + std::to_string(i) + "][" + std::to_string(j) + "][" + std::to_string(k) + "]";
				vars3D[i][j][k] = IloNumVar(env, 0, IloInfinity, ILOINT,tName.c_str());
			}			
			//vars3D[i][j][0] = IloNumVar(env, 1, 40, "x1");
			//vars3D[i][j][1] = IloNumVar(env, 1, IloInfinity, "x2");
			//vars3D[i][j][2] = IloNumVar(env, 1, IloInfinity, "x3");
		}
	}

	return vars3D;
}

NumVar4Matrix MyCplex::Define4DArray(int M, int N, int K,int W)
{
	NumVar4Matrix vars4D(env, M);

	for (int i = 0; i < M; i++)
	{
		vars4D[i] = NumVar3Matrix(env, N);
		for (int j = 0; j < N; j++)
		{
			vars4D[i][j] = NumVarMatrix(env, K);
			for (int k = 0; k < K; k++)
			{
				vars4D[i][j][k] = IloNumVarArray(env, W);
				for (int w = 0; w < W; w++)
				{
					std::string tName = "x[" + std::to_string(i) + "][" + std::to_string(j) + "][" + std::to_string(k) + "]";
					vars4D[i][j][k][w] = IloNumVar(env, 0, IloInfinity, ILOINT, tName.c_str());
				}
			}

		}
	}

	return vars4D;
}

NumVar5Matrix MyCplex::Define5DArray(int M, int N, int K, int W,int Q)
{
	NumVar5Matrix vars5D(env, M);

	for (int i = 0; i < M; i++)
	{
		vars5D[i] = NumVar4Matrix(env, N);
		for (int j = 0; j < N; j++)
		{
			vars5D[i][j] = NumVar3Matrix(env, K);
			for (int k = 0; k < K; k++)
			{
				vars5D[i][j][k] = NumVarMatrix(env, W);
				for (int w = 0; w < W; w++)
				{
					vars5D[i][j][k][w] = IloNumVarArray(env, Q);
					for (int q = 0; q < Q; q++)
					{
						std::string tName = "x[" + std::to_string(i) + "][" + std::to_string(j) + "][" + std::to_string(k) + "]";
						vars5D[i][j][k][w][q] = IloNumVar(env, 0, IloInfinity, ILOINT, tName.c_str());
					}
				}
			}

		}
	}

	return vars5D;
}



