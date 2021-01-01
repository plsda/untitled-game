#include "Ammukset.h"
#include <SFML/Graphics.hpp>

Ammukset::Ammukset()
{
	Ammus kiviammus, rautaammus, volframiammus;

	kiviammus.luoti = sf::CircleShape(2);
	kiviammus.luoti.setPosition(45, 440);
	kiviammus.luoti.setFillColor(sf::Color(90, 90, 90, 255));
	kiviammus.nopeus = 60;
	kiviammus.nopeusY = 60;
	kiviammus.teho = 20.0;
	kiviammus.hinta = 10.00;
	kiviammus.nimi = "kiviammus";

	rautaammus.luoti = sf::CircleShape(1);
	rautaammus.luoti.setPosition(45, 440);
	rautaammus.luoti.setFillColor(sf::Color(90, 90, 90, 255));
	rautaammus.nopeus = 120;
	rautaammus.nopeusY = 120;
	rautaammus.teho = 30.0;
	rautaammus.hinta = 25.00;
	rautaammus.nimi = "rautaammus";

	volframiammus.luoti = sf::CircleShape(1);
	volframiammus.luoti.setPosition(45, 440);
	volframiammus.luoti.setFillColor(sf::Color(90, 90, 90, 255));
	volframiammus.nopeus = 90;
	volframiammus.nopeusY = 90;
	volframiammus.teho = 50.0;
	volframiammus.hinta = 70.00;
	volframiammus.nimi = "volframiammus";

	ammukset.push_back(kiviammus);
	ammukset.push_back(rautaammus);
	ammukset.push_back(volframiammus);
}

Ammukset::Ammus Ammukset::haeAmmuksenTiedot(string ammustyyppi)
{
	Ammus ammus = {};
	for (size_t i = 0; i < ammukset.size(); ++i)
	{
		if (ammustyyppi == ammukset.at(i).nimi)
		{
			ammus = ammukset.at(i);
		}
	}

	return ammus;
}

vector<Ammukset::Ammus> Ammukset::haeListaAmmuksista()
{
	return ammukset;
}
