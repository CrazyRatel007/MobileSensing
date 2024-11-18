#pragma once
#include <deque>
#include <queue>
#include <vector>


struct TWOINT
{
	int Value1;
	int Value2;
	TWOINT()
	{
		Value1 = 0;
		Value2 = 0;
	}
};


struct ONEINTTWODOUBLE
{
	int Value1;
	double Value2;
	double Value3;
	ONEINTTWODOUBLE()
	{
		Value1 = 0;
		Value2 = 0.0;
		Value3 = 0.0;
	}
};

struct TWODOUBLE
{
	double Value1;
	double Value2;
	TWODOUBLE()
	{
		Value1 = 0.0;
		Value2 = 0.0;
	}
};


struct THREEDOUBLE
{
	double Value1;
	double Value2;
	double Value3;
	THREEDOUBLE()
	{
		Value1 = 0.0;
		Value2 = 0.0;
		Value3 = 0.0;
	}
};


struct FOURINT
{
	int Value1;
	int Value2;
	int Value3;
	int Value4;
	FOURINT()
	{
		Value1 = 0;
		Value2 = 0;
		Value3 = 0;
		Value4 = 0;
	}
};

struct FOURINTONEDOUBLE
{
	int Value1;
	int Value2;
	int Value3;
	int Value4;
	double Value5;
	FOURINTONEDOUBLE()
	{
		Value1 = 0;
		Value2 = 0;
		Value3 = 0;
		Value4 = 0;
		Value5 = 0;
	}
};

struct THREEINT
{
	int Value1;
	int Value2;
	int Value3;
	THREEINT()
	{
		Value1 = 0;
		Value2 = 0;
		Value3 = 0;
	}
};


struct TWOINTONEDOUBLE
{
	int Value1;
	int Value2;
	double Value3;
	TWOINTONEDOUBLE()
	{
		Value1 = 0;
		Value2 = 0;
		Value3 = 0;
	}
};


struct ONEINTONEFLOAT
{
	int Value1;
	float Value2;
	ONEINTONEFLOAT()
	{
		Value1 = 0;
		Value2 = 0;
	}
};


struct TWOLONG
{
	long Value1;
	long Value2;
	TWOLONG()
	{
		Value1 = 0;
		Value2 = 0;
	}
};


struct STRINGFLOGT
{
	std::string Value1;
	float Value2;
	STRINGFLOGT()
	{
		Value1 = "";
		Value2 = 0;
	}

};


struct THREEINTONEDOUBLE
{
	int Value1;
	int Value2;
	int Value3;
	double Value4;
	THREEINTONEDOUBLE()
	{
		Value1 = 0;
		Value2 = 0;
		Value3 = 0;
		Value4 = 0.0;
	}
};
