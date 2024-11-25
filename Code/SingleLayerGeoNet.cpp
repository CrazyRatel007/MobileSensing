#include "MyCplex.h"
#include "STRUCTSET.h"



void OutPutList(std::vector<double> pStoreResult, std::string pFileName)
{
	std::ofstream tOutPut(pFileName);
	for (int i = 0; i < pStoreResult.size(); i++)
	{
		tOutPut << pStoreResult[i];
		if (i < pStoreResult.size() - 1)
			tOutPut << std::endl;
	}
	tOutPut.close();

	return;
}

void OutPutIntList(std::vector<int> pStoreResult, std::string pFileName)
{
	std::ofstream tOutPut(pFileName);
	for (int i = 0; i < pStoreResult.size(); i++)
	{
		tOutPut << pStoreResult[i];
		if (i < pStoreResult.size() - 1)
			tOutPut << std::endl;
	}
	tOutPut.close();
	return;
}

void OutPutTWOINTONEDOUBLE(std::string pFileName, std::vector<TWOINTONEDOUBLE> pResult, bool pTag)
{
	std::ofstream tInput;
	if (pTag)
		tInput.open(pFileName);
	else
	{
		tInput.open(pFileName, std::ios::app);
		tInput << "\n";
	}


	for (int i = 0; i < pResult.size(); i++)
	{
		tInput << pResult[i].Value1 << "," << pResult[i].Value2 << "," << pResult[i].Value3;
		if (i < pResult.size() - 1)
			tInput << "\n";
	}
	tInput.close();

	return;
}

void MultiRoutePlanningIntegration(int tEdgeNumber, std::vector<ONEINTONEFLOAT>* pRandomVisitRoadProbability, int tTaxiNumber, std::vector<ONEINTONEFLOAT>* pDeterministicVisitRoadProbability, int tBusNumber, std::vector<float> pEdgeLength, int pStart, int pEnd)
{

	int tMaxVehicleNumber = tBusNumber + tTaxiNumber;
	std::vector<TWOINTONEDOUBLE> tObjectiveResult;
	for (int i = pStart; i < pEnd; i++)
	{
		////////////////////////////////////////////////////////////////
		/////////////////优化定义///////////////////////////////////////
		MyCplex CPlexOptimization;
		IloNumVarArray BusVariate = IloNumVarArray(CPlexOptimization.env, tBusNumber);
		for (int k = 0; k < tBusNumber; k++)
			BusVariate[k] = IloNumVar(CPlexOptimization.env, 0, 1, ILOINT, ("Bus" + std::to_string(k)).c_str());

		IloNumVarArray TaxiVariate = IloNumVarArray(CPlexOptimization.env, tBusNumber);
		for (int k = 0; k < tTaxiNumber; k++)
			TaxiVariate[k] = IloNumVar(CPlexOptimization.env, 0, 1, ILOINT, ("Taxi" + std::to_string(k)).c_str());

		IloNumVarArray RoadVariate = IloNumVarArray(CPlexOptimization.env, tEdgeNumber);
		for (int k = 0; k < tEdgeNumber; k++)
			RoadVariate[k] = IloNumVar(CPlexOptimization.env, 0, 1, ILOFLOAT, ("Grid" + std::to_string(k)).c_str());

		IloExpr ObjectiveExpression(CPlexOptimization.env);
		IloExprArray EXpreSet(CPlexOptimization.env, tEdgeNumber);
		for (int i = 0; i < tEdgeNumber; i++)
			EXpreSet[i] = IloExpr(CPlexOptimization.env);


		CPlexOptimization.constraints = IloRangeArray(CPlexOptimization.env, 2 + tEdgeNumber);

		CPlexOptimization.constraints[0] = IloRange(CPlexOptimization.env, i, i);
		for (int k = 0; k < tBusNumber; k++)
			CPlexOptimization.constraints[0].setLinearCoef(BusVariate[k], 1);
		for (int k = 0; k < tTaxiNumber; k++)
			CPlexOptimization.constraints[0].setLinearCoef(TaxiVariate[k], k + 1);


		CPlexOptimization.constraints[1] = IloRange(CPlexOptimization.env, 0, 1);
		for (int k = 0; k < tTaxiNumber; k++)
			CPlexOptimization.constraints[1].setLinearCoef(TaxiVariate[k], 1);


		for (int k0 = 1; k0 <= tTaxiNumber; k0++)
			for (int k1 = 0; k1 < pRandomVisitRoadProbability[k0].size(); k1++)
			{
				int  tmpEdgeID = pRandomVisitRoadProbability[k0][k1].Value1;
				float tProbability = pRandomVisitRoadProbability[k0][k1].Value2;
				if (tmpEdgeID < tEdgeNumber)
					EXpreSet[tmpEdgeID] += tProbability * TaxiVariate[k0 - 1];
			}

		for (int k0 = 0; k0 < tBusNumber; k0++)
			for (int k1 = 0; k1 < pDeterministicVisitRoadProbability[k0].size(); k1++)
			{
				int tmpEdgeID = pDeterministicVisitRoadProbability[k0][k1].Value1;
				float tProbability = pDeterministicVisitRoadProbability[k0][k1].Value2;
				EXpreSet[tmpEdgeID] += tProbability * BusVariate[k0];
			}

		for (int k = 0; k < tEdgeNumber; k++)
		{
			CPlexOptimization.constraints[k + 2] = IloRange(CPlexOptimization.env, 0, IloInfinity);
			EXpreSet[k] += RoadVariate[k] * (-1);
			CPlexOptimization.constraints[k + 2].setExpr(EXpreSet[k]);
		}


		CPlexOptimization.model.add(CPlexOptimization.constraints);

		for (int k = 0; k < tEdgeNumber; k++)
		{
			ObjectiveExpression += RoadVariate[k] * pEdgeLength[k];
		}

		CPlexOptimization.objective = IloMaximize(CPlexOptimization.env, ObjectiveExpression);
		CPlexOptimization.model.add(CPlexOptimization.objective);
		//solution
		CPlexOptimization.cplex = IloCplex(CPlexOptimization.model);
		CPlexOptimization.cplex.solve();

		CPlexOptimization.cplex.out() << "solution status:" << CPlexOptimization.cplex.getStatus() << std::endl;
		CPlexOptimization.cplex.out() << "objective value:" << CPlexOptimization.cplex.getObjValue() << std::endl;
		CPlexOptimization.cplex.exportModel("model.lp");

		//
		TWOINTONEDOUBLE tmpResult;
		tmpResult.Value1 = 0;
		for (int k = 0; k < tTaxiNumber; k++)
		{
			float tTag = CPlexOptimization.cplex.getValue(TaxiVariate[k]);
			if (tTag > 0.1)
				tmpResult.Value1 = k + 1;
		}

		tmpResult.Value2 = 0;
		std::vector<int> tBusFleet;
		for (int k = 0; k < tBusNumber; k++)
		{
			float tTag = CPlexOptimization.cplex.getValue(BusVariate[k]);
			if (tTag > 0.1)
			{
				tmpResult.Value2++;
				tBusFleet.push_back(k);
			}

		}
		tmpResult.Value3 = CPlexOptimization.cplex.getObjValue();
		tObjectiveResult.push_back(tmpResult);


		OutPutTWOINTONEDOUBLE("Objective.csv", tObjectiveResult, false);
		tObjectiveResult.clear();

		//Output
		std::vector<double> tmpRoadVisitedProbability;
		for (int k = 0; k < tEdgeNumber; k++)
		{
			double tProbability = CPlexOptimization.cplex.getValue(RoadVariate[k]);
			tmpRoadVisitedProbability.push_back(tProbability);
		}

		std::vector<int> tTaxiNumberSet;
		tTaxiNumberSet.push_back(tmpResult.Value1);
		OutPutIntList(tTaxiNumberSet, ".\\OptimizationResult\\" + std::to_string(i) + "TaxiNumber.csv");
		OutPutIntList(tBusFleet, ".\\OptimizationResult\\" + std::to_string(i) + "BusFleet.csv");
		OutPutList(tmpRoadVisitedProbability, ".\\OptimizationResult\\" + std::to_string(i) + "RoadVisitedProbability.csv");
	}

	return;
}

std::vector<ONEINTONEFLOAT> ReadTaxiVisitedProbability(int pEdgeNum,std::string pFile)
{
	std::vector<ONEINTONEFLOAT> tResult;
	ONEINTONEFLOAT tmpValue;

	for (int i = 0; i < pEdgeNum; i++)
	{
		tmpValue.Value1 = i;
		tmpValue.Value2 = 0;
		tResult.push_back(tmpValue);
	}
		
	int tTaxiNum(0);;
	std::ifstream tInput(pFile);
	while (!tInput.eof())
	{
		tInput >> tTaxiNum >> tmpValue.Value1 >> tmpValue.Value2;
		tResult[tmpValue.Value1].Value2 = tmpValue.Value2;
	}
	tInput.close();
	return tResult;
}

std::vector<ONEINTONEFLOAT> ReadBusVisitedRoad(int pEdgeNum, std::string pFile)
{
	std::vector<ONEINTONEFLOAT> tResult;
	ONEINTONEFLOAT tmpValue;
	for (int i = 0; i < pEdgeNum; i++)
	{
		tmpValue.Value1 = i;
		tmpValue.Value2 = 0;
		tResult.push_back(tmpValue);
	}

	int tTaxiNum(0);
	std::ifstream tInput(pFile);
	while (!tInput.eof())
	{
		tInput >> tmpValue.Value1;
		tResult[tmpValue.Value1].Value2 = 1;
	}
	tInput.close();
	return tResult;
}

std::vector<float> ReadRoadLength(int pEdgeNum, std::string pFile)
{
	std::vector<float> tResult;
	for (int i = 0; i < pEdgeNum; i++)
		tResult.push_back(0);

	int tRoadID(0);
	float tRoadLength(0);
	std::ifstream tInput(pFile);
	while (!tInput.eof())
	{
		tInput >> tRoadID >> tRoadLength;
		tResult[tRoadID] = tRoadLength;
	}
	tInput.close();
	return tResult;
}

int main(int argc, char* argv[])
{
	std::string tFile = "Data\\";
	int tTotalEdge = 272783; //the number of all edges
	std::vector<ONEINTONEFLOAT>* tTaxiRandomVisitRoadProbability = new std::vector<ONEINTONEFLOAT>[10];
	for (int i = 1; i <= 10; i++)
		tTaxiRandomVisitRoadProbability[i] = ReadTaxiVisitedProbability(tTotalEdge, tFile + std::to_string(i) + "Taxi-Probability.csv");

	std::vector<ONEINTONEFLOAT>* pDeterministicVisitRoadProbability = new std::vector<ONEINTONEFLOAT>[9];
	for (int i = 1; i <= 9; i++)
		pDeterministicVisitRoadProbability[i] = ReadBusVisitedRoad(tTotalEdge, tFile + "Bus-" + std::to_string(i));

	std::vector<float> tRoadLengthSet = ReadRoadLength(tTotalEdge, tFile + "EdgeLength.csv.csv");

	MultiRoutePlanningIntegration(tTotalEdge, tTaxiRandomVisitRoadProbability,10, pDeterministicVisitRoadProbability,9, tRoadLengthSet,0,19);
	return 1;

}