#ifndef ASEET_H
#define ASEET_H

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Aseet
{

public:
	Aseet();
	struct Tykki
	{
		sf::Sprite kuva;
		float lahtonopeus, hinta;
		string nimi;
	};
	Tykki haeAseenTiedot(string);
	vector<Tykki> haeListaAseista();

 private:
	 vector <Tykki> aseet;
	 sf::Texture tekstuuri;
	
};

#endif