#pragma once

class PlanetClass
{
private:

public:
	LPCWSTR Name;
	long Diam;
	int X;
	int Y;
	COLORREF Color;
	int Number;
	int DistToSun;
	PlanetClass(LPCWSTR name, long diam, COLORREF color, int number, int distToSun);
	PlanetClass();
	~PlanetClass();
};

PlanetClass::PlanetClass(LPCWSTR name, long diam, COLORREF color, int number, int distToSun)
{
	Name = name;
	Diam = diam;
	Color = color;
	Number = number;
	DistToSun = distToSun;

}

PlanetClass::PlanetClass() {}

PlanetClass::~PlanetClass() {}
