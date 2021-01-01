#ifndef ASE_H
#define ASE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ammukset.h"
#include "Aseet.h"
using namespace std;

class Ase
{
 public:
	 Ase(sf::Font, int, int);
	 ~Ase();
	 void ammu();
	 void paivitaAmmukset(sf::Time);
	 void poistaAmmus(size_t);
	 void liikuHiirenMukaan(sf::Event*);
	 void piirra(sf::RenderWindow*);
	 void vahennaElamia(int);
	 void nollaa();
	 int haeAmmustenMaara();
	 int haeElamat();
	 

 private:
	 float elamat;
	 double kulma, deltay, deltax;
	 int ammustenMaara, lippaanKoko, lippaidenMaara, alkuperainenLippaidenMaara;
	 bool paivitaAmmustekstit, paivitaElamat;
	 
	 Aseet aseidenTiedot;
	 Ammukset ammustenTiedot;

	 Ammukset::Ammus ammus;
	 Aseet::Tykki ase;

	 sf::Text ammuksetJaLippaat;
	 sf::Text torninKunto;
	 sf::Font fontti;

 public:
	 vector<Ammukset::Ammus> ammukset;

};

#endif
