#include "Bibliothek.h"

using namespace std;

Bibliothek::Bibliothek(string pfad)
{
	datei = pfad;
}

Bibliothek::Bibliothek()
{

}

Bibliothek::~Bibliothek(void)
{
}

string Bibliothek::getPfad()
{
	return datei;
}

GatterTyp* Bibliothek::getBibElement(string typ)
{
	for(int i = 0 ; i < bibElemente.size(); i++)
	{
		if(typ == bibElemente.at(i)->getName())
		{
			return bibElemente.at(i);
		}
	}
	return NULL;
}

void Bibliothek::dateiAusgabe()
{
	ifstream bib(datei.c_str());
	if(bib)
	{
		int zeilenNr = 1;
		string zeile;
		while(getline(bib,zeile))
		{
			cout << zeilenNr << " " << zeile << endl;
			zeilenNr++;
		}
	} else {
		openError();
	}
	system("pause");
}

void Bibliothek::dateiAuswerten()
{
	ifstream bib(datei.c_str());
	bibElemente.clear();

	if(bib)
	{
		string zeile;
		while(getline(bib,zeile))
		{
			if((zeile != "[[Bausteine]]") && (zeile.find("[") == 0))
			{
				int posEnd = zeile.find("]");
				string temp = zeile.substr(1,posEnd-1);
				if(temp != "dff")
				{
					bibElemente.push_back(new GatterTyp);
				} else 
				{
					bibElemente.push_back(new Flipflop);
				}
				bibElemente.back()->setName(temp);
			} else if(zeile.find("ei:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setEingaenge(atof(temp.c_str()));
			} else if(zeile.find("tpd0:") == 0)
			{
				string temp = zeile.substr(5);
				bibElemente.back()->setGrundLaufzeit(atof(temp.c_str()));
			} else if(zeile.find("kl:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setLastFaktor(atof(temp.c_str()));
			} else if(zeile.find("cl:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setLastKapazitaet(atof(temp.c_str()));
			} else if(zeile.find("tsetup:") == 0)
			{
				string temp = zeile.substr(7);
				bibElemente.back()->setSetupTime(atof(temp.c_str()));
			} else if(zeile.find("thold:") == 0)
			{
				string temp = zeile.substr(6);
				bibElemente.back()->setHoldTime(atof(temp.c_str()));
			} else if(zeile.find("ct:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setLastKapazitaetClock(atof(temp.c_str()));
			} else if(zeile.find("ed:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setEingaenge(atof(temp.c_str()));
			} else if(zeile.find("cd:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setLastKapazitaet(atof(temp.c_str()));
			} else if(zeile.find("tpdt:") == 0)
			{
				string temp = zeile.substr(5);
				bibElemente.back()->setGrundLaufzeit(atof(temp.c_str()));
			}
			
		}
	}
	if(bibElemente.size() == 0)
	{
		readError();
	}
	bib.close();
}

bool Bibliothek::pfadEinlesen(string pfad)
{
	datei = pfad;
	ifstream bib(datei.c_str());
	if(bib)
	{
		bib.close();
		return 1;
	} else 
	{
		return 0;
	}
}

void Bibliothek::openError()
{
	cout << "Die Datei konnte nicht geoeffnet werden" << endl;
}

void Bibliothek::readError()
{
	cout << "Beim lesen der Datei ist ein Fehler aufgetreten" << endl;
}