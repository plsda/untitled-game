#ifndef VIHOLLISTENKAYTTO_H
#define VIHOLLISTENKAYTTO_H

#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class VihollistenKaytto
{
 public:
	 VihollistenKaytto(sf::RenderWindow*, string);
	 ~VihollistenKaytto();
	 void muutaKuolleeksi(size_t);
	 void lisaaVihollinen(int);
	 void liikutaVihollisia(int[], sf::Time);
	 void paivitaVihollistenFramet();
	 void piirraViholliset(sf::RenderWindow*); 
	 void nollaa();
	 int haeVihollistenMaara();

 private:
	 struct Vihollinen
	 {
		 sf::Sprite kuva;
		 int framenNumero, framejenLkm, hyokkaysFramejenLkm, nopeus, vahinko;
		 bool hyokkaa, tekeeVahinkoa;
		 float kunto;
	 };

	 enum vihollisLajit
	 { 
		MIEKKAMIES = 1, KEIHASMIES
	 };

	 Vihollinen miekkamies;

	 sf::Texture tekstuuri;
	 sf::Sprite sprite;
	 sf::RenderWindow* ikkuna;
	 vector<Vihollinen> poistoLista;
	 vector<sf::Sprite> framet;
	 vector<sf::Sprite> hyokkaysFramet;

 public:
	 vector<Vihollinen> viholliset;

};

#endif
