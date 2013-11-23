#include "Faktoren.h"

using namespace std;

Faktoren::Faktoren(void)
{
	spannung = 0;
	temperatur = 0;
	prozess = 0;

	//Erzeugen der Listen, aus denen die Faktoren berechnet werden
	spannungListe[0][0] = 1.08;
	spannungListe[1][0] = 1.12;
	spannungListe[2][0] = 1.16;
	spannungListe[3][0] = 1.2;
	spannungListe[4][0] = 1.24;
	spannungListe[5][0] = 1.28;
	spannungListe[6][0] = 1.32;
	
	spannungListe[0][1] = 1.121557;
	spannungListe[1][1] = 1.075332;
	spannungListe[2][1] = 1.035161;
	spannungListe[3][1] = 1.0;
	spannungListe[4][1] = 0.96848;
	spannungListe[5][1] = 0.940065;
	spannungListe[6][1] = 0.914482;
	
	temperaturListe[0][0] = -25;
	temperaturListe[1][0] = -15;
	temperaturListe[2][0] = 0;
	temperaturListe[3][0] = 15;
	temperaturListe[4][0] = 25;
	temperaturListe[5][0] = 35;
	temperaturListe[6][0] = 45;
	temperaturListe[7][0] = 55;
	temperaturListe[8][0] = 65;
	temperaturListe[9][0] = 75;
	temperaturListe[10][0] = 85;
	temperaturListe[11][0] = 95;
	temperaturListe[12][0] = 105;
	temperaturListe[13][0] = 115;
	temperaturListe[14][0] = 125;
	
	temperaturListe[0][1] = 0.897498;
	temperaturListe[1][1] = 0.917532;
	temperaturListe[2][1] = 0.948338;
	temperaturListe[3][1] = 0.979213;
	temperaturListe[4][1] = 1.0;
	temperaturListe[5][1] = 1.020305;
	temperaturListe[6][1] = 1.04054;
	temperaturListe[7][1] = 1.061831;
	temperaturListe[8][1] = 1.082983;
	temperaturListe[9][1] = 1.103817;
	temperaturListe[10][1] = 1.124124;
	temperaturListe[11][1] = 1.144245;
	temperaturListe[12][1] = 1.164563;
	temperaturListe[13][1] = 1.18437;
	temperaturListe[14][1] = 1.204966;

	prozessListe[0] = 1.174235;
	prozessListe[1] = 1.0;
	prozessListe[2] = 0.876148;

}


Faktoren::~Faktoren(void)
{
}

double Faktoren::getSpannung()
{
	return spannung;
}

double Faktoren::getTemperatur()
{
	return temperatur;
}

short Faktoren::getProzess()
{
	return prozess;
}

void Faktoren::getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor)
{
	spgFaktor = spannungFaktor;
	tmpFaktor = temperaturFaktor;
	przFaktor = prozessFaktor;
}

void Faktoren::setSpannung(double spg)
{
	spannung = spg;
	berechneSpannungFaktor(spannung);
}

void Faktoren::setTemperatur(double temp)
{
	temperatur = temp;
	berechneTemperaturFaktor(temperatur);
}

void Faktoren::setProzess(short prz)
{
	prozess = prz;
	berechneProzessFaktor(prozess);
}

void Faktoren::ausgabeFaktoren()	//Gibt die berechneten Faktoren aus, falls diese ermittelt werden können
{
	if (berechneSpannungFaktor(spannung) && berechneTemperaturFaktor(temperatur) && berechneProzessFaktor(prozess))
	{
		cout << "Faktoren: KV: " << spannungFaktor << " | KT: " << temperaturFaktor << " | KP: " << prozessFaktor << endl;
	}
	else
	{
		cout << "Einer oder mehrere Faktoren konnten nicht berechnet werden.\n";
	}
	system("pause");
}

bool Faktoren::berechneSpannungFaktor(double spg)	//Prueft, ob die Spannung im gueltigen Bereich ist. Falls ja wird der Faktor ueber berechneFaktor ermittelt
{
	if (spg < spannungListe[0][0] || spg > spannungListe[6][0])
	{
		cout << "Die Betriebsspannung liegt ausserhalb des g\x81ltigen Bereichs.\n";
		return false;
	}
	else
	{
		spannungFaktor = berechneFaktor(spg,spannungListe,7);
		return true;
	}
}

bool Faktoren::berechneTemperaturFaktor(double temp)	//Prueft, ob die Temperatur im gueltigen Bereich ist. Falls ja wird der Faktor ueber berechneFaktor ermittelt
{
	if (temp < temperaturListe[0][0] || temp > temperaturListe[14][0])
	{
		cout << "Die Betriebstemperatur liegt ausserhalb des g\x81ltigen Bereichs.\n";
		return false;
	}
	else
	{
		temperaturFaktor = berechneFaktor(temp,temperaturListe,15);
		return true;
	}
	return true;
}

bool Faktoren::berechneProzessFaktor(short prz)	//Weist den Prozesswerten 1, 2 und 3 den Faktor zu. Bei anderer Angabe von Prozess gibt die Konsole eine Fehlermeldung aus
{
	switch ((int)prz)
	{
	case 1:
		prozessFaktor = prozessListe[0];
		break;
	case 2:
		prozessFaktor = prozessListe[1];
		break;
	case 3:
		prozessFaktor = prozessListe[2];
		break;
	default:
		cout << "Ung\x81ltiger Prozess\n";
		return false;
	}
	return true;
}

double Faktoren::berechneFaktor(double wert, double arr[][2], int laenge)
{
	for (int i = 0; i < laenge; i++)	//Pfrueft zuerst, ob sich der Wert schon in der Liste befindet. Falls ja, gib den passenden Faktor zurueck
	{
		if (wert == arr[i][0])
		{
			return arr[i][1];
		}
	}
	//Der Wert wurde nicht in der Liste gefunden, daher muss der Faktor per Interpolation ermittelt werden. Ermittle daher im naechsten Schritt die nacheliegendsten Werte
	double x1, x2, y1, y2;

	for (int i = 0; i < laenge; i++)
	{
		if (arr[i][0] < wert)
		{
			x1 = arr[i][0];
			y1 = arr[i][1];
		}
		if (arr[laenge-i-1][0] > wert)
		{
			x2 = arr[laenge-i-1][0];
			y2 = arr[laenge-i-1][1];
		}
	}
	//Interpolation liefert den Faktor, welcher zurueckgegeben wird
	return interpolation(wert,x1,y1,x2,y2);
}

double Faktoren::interpolation(double wert, double x1, double y1, double x2, double y2)
{
	if (x1!=x2)
	{
		double erg=y1+((y2-y1)/(x2-x1))*(wert-x1);	//Y(X0) = Y1 + Steigung mal (Entfernung von X0 zu x1)
		return erg;
	}
	cout << "Fehler bei der Interpolation: x1 = x2 ist nicht m\x94glich";
	return 0;
}