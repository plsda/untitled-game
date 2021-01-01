#ifndef KAUPPA_H
#define KAUPPA_H

#include <vector>
#include "Ammukset.h"
#include "Aseet.h"

using namespace std;

class Kauppa
{
 public:
	 Kauppa(sf::Font);
	 void kaynnistaOstaminen(sf::Event*);
	 void piirraKaupanSisalto(sf::RenderWindow*, sf::Event*);
	 string haeMyytavanTiedot(string);

 private:
	 Aseet aseidenTiedot;
	 Ammukset ammustenTiedot;
	 sf::Text kaupanTeksti, myytavanTiedot;
	 vector<Ammukset::Ammus> myytavatAmmukset;
	 vector<Aseet::Tykki> myytavatAseet;

};

#endif
