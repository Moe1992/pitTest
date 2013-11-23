#pragma once

#include <iostream>
#include "itiv_win_drv.h"

class Faktoren
{
public:
	Faktoren(void);
	~Faktoren(void);
	double getSpannung();
	double getTemperatur();
	short getProzess();
	void getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor);
	void setSpannung(double spg);
	void setTemperatur(double temp);
	void setProzess(short prz);
	void ausgabeFaktoren();

private:
	double spannung;
	double temperatur;
	short prozess;
	double spannungFaktor;
	double temperaturFaktor;
	double prozessFaktor;
	double spannungListe[7][2];
	double temperaturListe[15][2];
	double prozessListe[3];

	bool berechneSpannungFaktor(double spg);
	bool berechneTemperaturFaktor(double temp);
	bool berechneProzessFaktor(short prz);
	double berechneFaktor(double wert, double arr[][2], int laenge);
	double interpolation(double wert, double x1, double y1, double x2, double y2);
};