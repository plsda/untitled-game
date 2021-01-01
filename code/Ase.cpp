#define _USE_MATH_DEFINES

#include "Ase.h"
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;



//Ase::Ase(string fontti, int lippaanKoko, int lippaidenMaara)
Ase::Ase(sf::Font fontti, int lippaanKoko, int lippaidenMaara)
{
	this->fontti = fontti;

	this->lippaanKoko = lippaanKoko;
	this->lippaidenMaara = lippaidenMaara;
	alkuperainenLippaidenMaara = lippaidenMaara;
	ammustenMaara = lippaanKoko;

	ammus = ammustenTiedot.haeAmmuksenTiedot("kiviammus");
	ase = aseidenTiedot.haeAseenTiedot("pieniTykki");

	ammuksetJaLippaat.setFont(this->fontti);
	ammuksetJaLippaat.setPosition(15, 10);
	ammuksetJaLippaat.setCharacterSize(15);

	torninKunto.setFont(this->fontti);
	torninKunto.setPosition(40, 410);
	torninKunto.setCharacterSize(15);

	paivitaAmmustekstit = true;
	paivitaElamat = true;

	elamat = 1000.0;
}

Ase::~Ase()
{

}

void Ase::ammu()
{
	if (kulma < 30 && kulma > -70 && (lippaidenMaara > 0 || ammustenMaara > 0))
	{
		paivitaAmmustekstit = true;

		ammus.kulmakerroin = deltay / deltax;
		ammukset.push_back(ammus);

		if (ammustenMaara <= 0)
		{
			lippaidenMaara--;
			ammustenMaara = lippaanKoko;
		}
		else
		{
			ammustenMaara--;
		}
		
	}
}

void Ase::paivitaAmmukset(sf::Time kulunutAika)
{

	if (!ammukset.empty())
		for (size_t i = 0; i < ammukset.size(); i++)
		{
			
			//ammukset.at(i).luoti.move((ammukset.at(i).nopeus + ase.lahtonopeus) * aika.asSeconds(), ammukset.at(i).kulmakerroin * (ammukset.at(i).nopeusY + ase.lahtonopeus) * aika.asSeconds());
			ammukset.at(i).luoti.move((ammukset.at(i).nopeus + ase.lahtonopeus) * (float)kulunutAika.asSeconds(), ammukset.at(i).kulmakerroin * (ammukset.at(i).nopeusY + ase.lahtonopeus) * (float)kulunutAika.asSeconds());

			if (ammukset.at(i).luoti.getPosition().x >= 800 || ammukset.at(i).luoti.getPosition().y >= 600)
				poistaAmmus(i);
			
		}

}

void Ase::poistaAmmus(size_t ammuksenNumero)
{
	vector<Ammukset::Ammus> poistolista;
	//toteuta erase- komennolla
	for (size_t i = 0; i < ammukset.size(); i++)
	{
		if (i == ammuksenNumero)
			continue;

		poistolista.push_back(ammukset.at(i));
	}

	ammukset = poistolista;
}

void Ase::liikuHiirenMukaan(sf::Event* tapahtuma)
{
	int hiirenSijaintiX, hiirenSijaintiY;

	if (tapahtuma->type == sf::Event::MouseMoved)
	{
		hiirenSijaintiX = tapahtuma->mouseMove.x;
		hiirenSijaintiY = tapahtuma->mouseMove.y;
	}
	else
	{
		hiirenSijaintiX = tapahtuma->mouseButton.x;
		hiirenSijaintiY = tapahtuma->mouseButton.y;
	}

	deltay = hiirenSijaintiY - 440;
	deltax = hiirenSijaintiX - 45;

	kulma = atan2(deltay, deltax) / M_PI * 180.0000;

	if (kulma < 30 && kulma > -70)
	{
		ase.kuva.setRotation(kulma);
	}
}

void Ase::piirra(sf::RenderWindow* ikkuna)
{	

	if (paivitaAmmustekstit)
	{
		stringstream s;
		s << ammustenMaara;
		s << "/";
		s << lippaanKoko;
		s << "\t";
		s << lippaidenMaara;

		ammuksetJaLippaat.setString(s.str());

		s.clear();

		paivitaAmmustekstit = false;
	}

	if (paivitaElamat)
	{
		stringstream s;
		s << elamat;
		s << "/";
		s << "1000";

		torninKunto.setString(s.str());

		paivitaElamat = false;
	}

	if (!ammukset.empty())
		for (size_t i = 0; i < ammukset.size(); i++)
		{
			ikkuna->draw(ammukset.at(i).luoti);
		}

	ikkuna->draw(ammuksetJaLippaat);
	ikkuna->draw(torninKunto);
	ikkuna->draw(ase.kuva);
}	

void Ase::vahennaElamia(int maara)
{
	elamat -= maara;
	paivitaElamat = true;
}

void Ase::nollaa()
{
	elamat = 1000;
	ammustenMaara = lippaanKoko;
	lippaidenMaara = alkuperainenLippaidenMaara;
	paivitaElamat = true;
	paivitaAmmustekstit = true;
	ammukset.clear();
}

int Ase::haeElamat()
{
	return elamat;
}

int Ase::haeAmmustenMaara()
{
	return ammukset.size();
}
