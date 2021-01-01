#ifndef OHJELMA_H
#define OHJELMA_H

#include "TileMappi.h"
#include "VihollistenKaytto.h"
#include "Ase.h"
#include "Efektit.h"
#include "Kauppa.h"
#include <SFML/Graphics.hpp>
using namespace std;

class Ohjelma
{
 public:
	 Ohjelma(string, string, string, string, sf::RenderWindow*, sf::Event*);
	 ~Ohjelma();
	 bool onkoPelaaValittu();
	 bool onkoOhjeetValittu();
	 bool onkoPeliOhiValittu();
	 bool onkoJatkaValittu();
	 bool onkoNappiValittu(sf::Text, sf::Event*);
	 void aloitaPeli();
	 void paivitaPelitilanne(sf::Time);
	 void piirraPelitilanne();
	 void piirraValikko();
	 void piirraOhjeet();
	 void piirraPeliOhi();
	 void piirraKierrosOhi();
	 void ammu(); 
	 void nollaaPeli();
	 void pysaytaPeli();
	 void jatkaPelia();
	 bool tykkiOnTuhoutunut;

 private:
	 sf::RenderWindow* ikkuna;
	 sf::Event* tapahtuma;
	 sf::Font fontti;
	 sf::Text pelaaTeksti, ohjeetTeksti, ohjeteksti, peliOhiTeksti, odotaTeksti, kierrokset, jatkaPeliaTeksti;
	 sf::Sprite pelinTausta, valikonTausta, tilemapinKuvat, pimennysSprite;
	 sf::Texture pelinTekstuuri, valikonTekstuuri, tilemapinTekstuuri, pimennysTekstuuri;
	 sf::Image taustanMaski;
	 sf::Clock paivitysKello, liikuttamisKello, kello;
	 sf::Time paivitysAika, liikuttamisAika, aika, viimeAika;

	 TileMappi kentanPiirto;
	 Kauppa* pKauppa;
	 VihollistenKaytto* pViholliset;
	 Ase* pTykki;
	 Efektit::Partikkelit* pPartikkelit;
	 Efektit::Varjostin* pVarjostin;
	 int vihollistenMaaraKierroksessa, vihollistenMaara, arvottuAika, kierros;
	 enum viholliset
	 {
		 MIEKKAMIES = 1, KEIHASMIES
	 };


};


#endif
