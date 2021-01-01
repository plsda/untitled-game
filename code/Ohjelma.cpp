#include"Ohjelma.h"
#include "Kentat.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

Ohjelma::Ohjelma(string valikonTausta, string pelinTausta, string tilemapinKuvat, string fontti, sf::RenderWindow* kaytettavaIkkuna, sf::Event* kaytettavaTapahtuma)
{	
	clog << "Aloitetaan peli" << endl;


	if (!pelinTekstuuri.loadFromFile(pelinTausta)) 
	{
		throw runtime_error("Virhe kuvan lataamisessa(1)");
	}


	if (!valikonTekstuuri.loadFromFile(valikonTausta)) 
	{
		throw runtime_error("Virhe kuvan lataamisessa(2)");
	}

	if (!tilemapinTekstuuri.loadFromFile(tilemapinKuvat)) 
	{
		throw runtime_error("Virhe kuvien lataamisessa(3)");
	}

	if (!pimennysTekstuuri.create(800, 600)) 
	{
		throw runtime_error("Virhe tekstuurin luonnissa(4)");
	}
	
	this->pelinTausta.setTexture(pelinTekstuuri);
	this->valikonTausta.setTexture(valikonTekstuuri);
	this->tilemapinKuvat.setTexture(tilemapinTekstuuri);
	taustanMaski.create(800, 600);

	for (int i = 0; i < 800; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			taustanMaski.setPixel(i, j, sf::Color(25, 25, 25, 220));
		}
	}

	pimennysTekstuuri.update(taustanMaski);
	pimennysSprite.setTexture(pimennysTekstuuri);

	if (!this->fontti.loadFromFile(fontti)) 
	{
		throw runtime_error("Virhe fontin lataamisessa(5)");
	}

	if (!kentanPiirto.lataa(tilemapinTekstuuri, kenttaNro1, 30, 30, 27, 20)) 
	{
		throw runtime_error("Virhe kentan lataamisessa(6)");
	}

	pTykki = new Ase(this->fontti, 10, 5);
	pViholliset = new VihollistenKaytto(ikkuna, "Assets\\VihollistenKuvat.png");
	pKauppa = new Kauppa(this->fontti);
	pPartikkelit = new Efektit::Partikkelit();
	pVarjostin = new Efektit::Varjostin();

	ikkuna = kaytettavaIkkuna;
	tapahtuma = kaytettavaTapahtuma;

	int ikkunaLeveys = ikkuna->getSize().x;
	int ikkunaKorkeus = ikkuna->getSize().y;
	
	pelaaTeksti.setFont(this->fontti);
	pelaaTeksti.setString("Play");
	pelaaTeksti.setCharacterSize(20);
	pelaaTeksti.setColor(sf::Color::White);
	pelaaTeksti.setPosition(ikkunaLeveys/2 - 50, ikkunaKorkeus/2);

	ohjeetTeksti.setFont(this->fontti);
	ohjeetTeksti.setString("Options");
	ohjeetTeksti.setCharacterSize(20);
	ohjeetTeksti.setColor(sf::Color::White);
	ohjeetTeksti.setPosition(ikkunaLeveys/2 - 50, ikkunaKorkeus/2 + 50);

	ohjeteksti.setFont(this->fontti);
	ohjeteksti.setString("LMB - Shoot\nesc - Go back to main menu\np - Pause");
	ohjeteksti.setCharacterSize(20);
	ohjeteksti.setColor(sf::Color::White);
	ohjeteksti.setPosition(ikkunaLeveys/2 - 50, ikkunaKorkeus/2);

	peliOhiTeksti.setFont(this->fontti);
	peliOhiTeksti.setString("Game over");
	peliOhiTeksti.setCharacterSize(25);
	peliOhiTeksti.setColor(sf::Color::Black);
	peliOhiTeksti.setPosition(350, 300);

	odotaTeksti.setFont(this->fontti);
	odotaTeksti.setString("Paused");
	odotaTeksti.setCharacterSize(25);
	odotaTeksti.setColor(sf::Color(0, 0, 0, 100));
	odotaTeksti.setPosition(370, 300);

	kierrokset.setFont(this->fontti);
	kierrokset.setString("0");
	kierrokset.setCharacterSize(15);
	kierrokset.setColor(sf::Color(0, 0, 0, 200));
	kierrokset.setPosition(400, 10);

	jatkaPelia.setFont(this->fontti);
	jatkaPelia.setString("Ready");
	jatkaPelia.setCharacterSize(15);
	jatkaPelia.setColor(sf::Color(0, 0, 0, 200));
	jatkaPelia.setPosition(400, 500);

	vihollistenMaaraKierroksessa = 5;
	vihollistenMaara = 0;

	arvottuAika = (rand() % 6000) + 1000;

	kierros = 0;
	tykkiOnTuhoutunut = false;

}

Ohjelma::~Ohjelma()
{
	delete pTykki;
	delete pViholliset; 
	delete pKauppa;
	delete pPartikkelit;
	delete pVarjostin;
	clog << "Lopetetaan peli" << endl;
}

bool Ohjelma::onkoPelaaValittu()
{
	return onkoNappiValittu(pelaaTeksti, tapahtuma);
}

bool Ohjelma::onkoOhjeetValittu()
{
	return onkoNappiValittu(ohjeetTeksti, tapahtuma);
}

bool Ohjelma::onkoPeliOhiValittu()
{
	return onkoNappiValittu(peliOhiTeksti, tapahtuma);
}

bool Ohjelma::onkoJatkaValittu()
{
	return onkoNappiValittu(jatkaPelia, tapahtuma);
}

bool Ohjelma::onkoNappiValittu(sf::Text teksti, sf::Event* t)
{
	sf::FloatRect rajat = teksti.getGlobalBounds();

	return (rajat.contains((float)t->mouseButton.x, (float)t->mouseButton.y) && (t->mouseButton.button == sf::Mouse::Left));
	//if (rajat.contains((float)tapahtuma->mouseButton.x, (float)tapahtuma->mouseButton.y))
	//	return true;
	//else
	//	return false;
}

void Ohjelma::aloitaPeli()
{
	paivitysAika = paivitysKello.getElapsedTime();
	aika = kello.getElapsedTime();
	liikuttamisAika = liikuttamisKello.restart();
	
	pTykki->liikuHiirenMukaan(tapahtuma);

	if (aika.asMilliseconds() >= arvottuAika && vihollistenMaara < vihollistenMaaraKierroksessa)
	{
		pViholliset->lisaaVihollinen(MIEKKAMIES);
		vihollistenMaara++;
		aika.Zero;
		kello.restart();
		arvottuAika = (rand() % 6000) + 1000;
	}
	else if (vihollistenMaara >= vihollistenMaaraKierroksessa)
	{
		//kauppa ja ostohetki

		if (onkoJatkaValittu())
		{
			vihollistenMaaraKierroksessa += 2;
			vihollistenMaara = 0;
			kierros++;

			stringstream s;

			s << kierros;
			kierrokset.setString(s.str());
		}
			
	}

	if (pTykki->haeAmmustenMaara() > 0 && pViholliset->haeVihollistenMaara() > 0)
	{
		
		for (size_t i = 0; i < pViholliset->viholliset.size(); ++i)
		{
			sf::FloatRect vihollisenRajat = pViholliset->viholliset.at(i).kuva.getGlobalBounds();

			for (size_t j = 0; j < pTykki->ammukset.size(); ++j)
			{

				if (vihollisenRajat.contains(pTykki->ammukset.at(j).luoti.getPosition()))
				{
					
					pViholliset->viholliset.at(i).kunto -= pTykki->ammukset.at(j).teho;

					if (pViholliset->viholliset.at(i).kunto <= 0)
					{
						pViholliset->muutaKuolleeksi(i);
						pPartikkelit->muodostaPartikkeleita(pTykki->ammukset.at(j).luoti.getPosition(), 600, sf::Color::Black, true);
					}
					else
					{
						pPartikkelit->muodostaPartikkeleita(pTykki->ammukset.at(j).luoti.getPosition(), 10, sf::Color::Red, true);
					}

					pTykki->poistaAmmus(j);
				}
			}
		}
	}

	for (size_t i = 0; i < pViholliset->viholliset.size(); ++i)
	{

		if (pViholliset->viholliset.at(i).hyokkaa)
		{
			if (pViholliset->viholliset.at(i).tekeeVahinkoa)
			{
				if (pTykki->haeElamat() > 0)
				{
					pTykki->vahennaElamia(pViholliset->viholliset.at(i).vahinko);
					pViholliset->viholliset.at(i).tekeeVahinkoa = false;
				}
				else
				{
					tykkiOnTuhoutunut = true;
				}
			}

		}
		else
		{
			break;
		}
	}

	paivitaPelitilanne(paivitysAika);
	piirraPelitilanne();
}

void Ohjelma::paivitaPelitilanne(sf::Time kulunutAika)
{
	if (kulunutAika.asMilliseconds() >= 150)
	{
		pViholliset->paivitaVihollistenFramet();
		pPartikkelit->paivitaPartikkelit(kulunutAika);

		paivitysAika.Zero;
		paivitysKello.restart();
	}

	pViholliset->liikutaVihollisia(kenttaNro1, liikuttamisAika);
	pTykki->paivitaAmmukset(liikuttamisAika);
}

void Ohjelma::piirraPelitilanne()
{
	ikkuna->draw(pelinTausta);
	ikkuna->draw(kierrokset);


	if (vihollistenMaara >= vihollistenMaaraKierroksessa)
	{
		piirraKierrosOhi();
		pKauppa->piirraKaupanSisalto(ikkuna, tapahtuma);
	}
	else
	{
		pTykki->piirra(ikkuna);
		pViholliset->piirraViholliset(ikkuna);
		pPartikkelit->piirra(ikkuna);
		//pVarjostin->kaytaVarjostinta(ikkuna, pimennysSprite);
		//ikkuna->draw(pimennysSprite);
		kentanPiirto.piirra(ikkuna);
	}
}

void Ohjelma::ammu()
{
	//if (vihollistenMaara >= vihollistenMaaraKierroksessa)
		pTykki->ammu();
}

void Ohjelma::piirraValikko()
{
	ikkuna->draw(valikonTausta);
	ikkuna->draw(pelaaTeksti);
	ikkuna->draw(ohjeetTeksti);
}

void Ohjelma::piirraOhjeet()
{
	ikkuna->draw(valikonTausta);
	ikkuna->draw(ohjeteksti);
}

void Ohjelma::piirraPeliOhi()
{
	piirraPelitilanne();
	ikkuna->draw(peliOhiTeksti);
}

void Ohjelma::piirraKierrosOhi()
{
	ikkuna->draw(jatkaPelia);
}

void Ohjelma::nollaaPeli()
{
	tykkiOnTuhoutunut = false;
	pTykki->nollaa();
	pViholliset->nollaa();
}

void Ohjelma::pysaytaPeli()
{
	piirraPelitilanne();
	ikkuna->draw(odotaTeksti);
}
