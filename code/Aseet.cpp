#include "ASEET.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

Aseet::Aseet()
{
	if (!tekstuuri.loadFromFile("Assets\\AseidenKuvat.png"))
	{
		throw runtime_error("Virhe asieden kuvien lataamisessa");
	}

	Tykki pieniTykki, isoTykki, ohutTykki;

	pieniTykki.kuva.setTexture(tekstuuri);
	pieniTykki.kuva.setTextureRect(sf::IntRect(0, 0, 39, 19));
	pieniTykki.kuva.setPosition(45, 440);
	pieniTykki.kuva.setOrigin(0, 9);
	pieniTykki.lahtonopeus = 240;
	pieniTykki.hinta = 0.00;
	pieniTykki.nimi = "pieniTykki";

	isoTykki.kuva.setTexture(tekstuuri);
	isoTykki.kuva.setTextureRect(sf::IntRect(0, 20, 39, 20));
	isoTykki.kuva.setPosition(45, 440);
	isoTykki.kuva.setOrigin(0, 10);
	isoTykki.lahtonopeus = 480;
	isoTykki.hinta = 450.00;
	isoTykki.nimi = "isoTykki";

	ohutTykki.kuva.setTexture(tekstuuri);
	ohutTykki.kuva.setTextureRect(sf::IntRect(0, 40, 39, 20));
	ohutTykki.kuva.setPosition(45, 440);
	ohutTykki.kuva.setOrigin(0, 10);
	ohutTykki.lahtonopeus = 720;
	ohutTykki.hinta = 375.00;
	ohutTykki.nimi = "ohutTykki";

	aseet.push_back(pieniTykki);
	aseet.push_back(isoTykki);
	aseet.push_back(ohutTykki);
}

Aseet::Tykki Aseet::haeAseenTiedot(string aseenTyyppi)
{
	Tykki tykki = {};
	for (size_t i = 0; i < aseet.size(); ++i)
	{
		if (aseenTyyppi == aseet.at(i).nimi)
		{
			tykki = aseet.at(i);
		}
	}

	return tykki;
}

vector<Aseet::Tykki> Aseet::haeListaAseista()
{
	return aseet;
}
