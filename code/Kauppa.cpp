#include "Kauppa.h"
#include <sstream>
#include <iostream>

Kauppa::Kauppa(sf::Font fontti)
{

	myytavatAseet = aseidenTiedot.haeListaAseista();
	myytavatAmmukset = ammustenTiedot.haeListaAmmuksista();
	
	kaupanTeksti.setFont(fontti);
	kaupanTeksti.setString("Store");
	kaupanTeksti.setPosition(380, 150);
	kaupanTeksti.setCharacterSize(30);
	kaupanTeksti.setColor(sf::Color::Black);

	myytavanTiedot.setFont(fontti);
	myytavanTiedot.setCharacterSize(10);
	myytavanTiedot.setColor(sf::Color::Red);

	for (size_t i = 0; i < myytavatAseet.size(); ++i)
		myytavatAseet.at(i).kuva.setPosition(i * 20 + 100, 250);

	for (size_t i = 0; i < myytavatAmmukset.size(); ++i)
		myytavatAmmukset.at(i).luoti.setPosition(i * 20 + 150, 400);

}

string Kauppa::haeMyytavanTiedot(string nimi)
{
	Aseet::Tykki naytettavaT;
	Ammukset::Ammus naytettavaA;
	stringstream ss;

	if (naytettavaT.hinta == NULL || naytettavaT.lahtonopeus == NULL)
	{
		ss << "Price: " << naytettavaA.hinta 
			<< "\nSpeed " << naytettavaA.nopeus 
		    << "\nPower: " << naytettavaA.teho;
	}
	else
	{
		ss << "Price: " << naytettavaT.hinta
			<< "\nVelocity: " << naytettavaT.lahtonopeus;
	}

	return ss.str();
}

void Kauppa::kaynnistaOstaminen(sf::Event* tapahtuma)
{

}

void Kauppa::piirraKaupanSisalto(sf::RenderWindow* ikkuna, sf::Event* tapahtuma)
{
	if (!myytavatAseet.empty())
	{
		for (size_t i = 0; i < myytavatAseet.size(); ++i)
		{
			ikkuna->draw(myytavatAseet.at(i).kuva);
		}
	}

	if (!myytavatAmmukset.empty())
	{
		for (size_t i = 0; i < myytavatAmmukset.size(); ++i)
		{
			ikkuna->draw(myytavatAmmukset.at(i).luoti);
		}
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (size_t i = 0; i < myytavatAseet.size(); ++i)
		{
			if (myytavatAseet.at(i).kuva.getGlobalBounds().contains(tapahtuma->mouseButton.x, tapahtuma->mouseButton.y))
			{
				myytavanTiedot.setString(haeMyytavanTiedot(myytavatAseet.at(i).nimi));
				myytavanTiedot.setPosition(myytavatAseet.at(i).kuva.getPosition().x + 10, myytavatAseet.at(i).kuva.getPosition().y + 50);

				ikkuna->draw(myytavanTiedot);
			}
			else if (i >= myytavatAseet.size())
			{
				for (size_t j = 0; j < myytavatAmmukset.size(); ++j)
				{
					if (myytavatAmmukset.at(j).luoti.getGlobalBounds().contains(tapahtuma->mouseButton.x, tapahtuma->mouseButton.y))
					{
						myytavanTiedot.setString(haeMyytavanTiedot(myytavatAmmukset.at(j).nimi));
						myytavanTiedot.setPosition(myytavatAmmukset.at(j).luoti.getPosition().x + 10, myytavatAmmukset.at(j).luoti.getPosition().y + 50);

						ikkuna->draw(myytavanTiedot);
					}
				}
			}
		}

	}
}


