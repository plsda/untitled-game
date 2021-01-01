#ifndef AMMUKSET_H
#define AMMUKSET_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Ammukset
{
 
 public:
	struct Ammus
	{
		sf::CircleShape luoti;
		double kulmakerroin;
		float nopeus, nopeusY, teho, hinta;
		string nimi;
	};

	Ammukset();
	Ammus haeAmmuksenTiedot(string);
	vector<Ammus> haeListaAmmuksista();

 private:
	 vector<Ammus> ammukset;

};
#endif
