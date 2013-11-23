#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "GatterTyp.h"
#include "Flipflop.h"

class Bibliothek
{
public:
	Bibliothek(std::string pfad);
	Bibliothek();
	~Bibliothek(void);
	std::string getPfad();
	GatterTyp* getBibElement(std::string typ);
	void dateiAusgabe();
	void dateiAuswerten();
	bool pfadEinlesen(std::string pfad);
	
private:
	std::vector<GatterTyp*> bibElemente;
	std::string datei;
	void openError();
	void readError();
};

