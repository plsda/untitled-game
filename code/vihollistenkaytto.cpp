#include "VihollistenKaytto.h"
#include <stdexcept>
#include <typeinfo>
#include <iostream>

VihollistenKaytto::VihollistenKaytto(sf::RenderWindow* ikkuna, string vihollistenKuvat)
{
	this->ikkuna = ikkuna;

	if (!tekstuuri.loadFromFile(vihollistenKuvat)) 
	{
		throw runtime_error("Virhe vihollisten kuvien lataamisessa");
	}		

	sprite.setTexture(tekstuuri);
	sprite.setPosition(780, 535);
	
	sf::Vector2f ensimmaisenSijainti = sf::Vector2f(1, 2);

	for (int i = 0; i < 5; i++)
	{
		sprite.setTextureRect(sf::IntRect(ensimmaisenSijainti.x, ensimmaisenSijainti.y, 29, 38));
		framet.push_back(sprite);
		ensimmaisenSijainti.x += 33;
	}

	ensimmaisenSijainti.x = 2;

	for (int j = 0; j < 5; j++)
	{
		sprite.setTextureRect(sf::IntRect(ensimmaisenSijainti.x, ensimmaisenSijainti.y + 42, 37, 41)); //28
		hyokkaysFramet.push_back(sprite);
		ensimmaisenSijainti.x += 37; 
	}

	miekkamies.kuva = framet.at(0);
	miekkamies.framenNumero = 0;
	miekkamies.framejenLkm = 4;
	miekkamies.hyokkaysFramejenLkm = 4;
	miekkamies.nopeus = -20;
	miekkamies.hyokkaa = false;
	miekkamies.kunto = 50.0;
	miekkamies.tekeeVahinkoa = false;
	miekkamies.vahinko = 5;

}

VihollistenKaytto::~VihollistenKaytto()
{

}

void VihollistenKaytto::muutaKuolleeksi(size_t vihollisenNumero)
{
	for (size_t i = 0; i < viholliset.size(); i++)
	{
		if (i == vihollisenNumero)
			continue;
		
		poistoLista.push_back(viholliset.at(i));
	}

	viholliset = poistoLista;
	poistoLista.clear(); 
	
}

void VihollistenKaytto::lisaaVihollinen(int vihollisenNimi)
{
	switch (vihollisenNimi)
	{
		case MIEKKAMIES: viholliset.push_back(miekkamies);
			break;
		case KEIHASMIES:									
			break;
		
		default:											
			break;
	}
}

void VihollistenKaytto::liikutaVihollisia(int kentta[], sf::Time kulunutAika)
{
	int vihollisenTilenX, vihollisenTilenY, vihollisenTilenNumero = 0;

	if (!viholliset.empty())
		for (size_t i = 0; i < viholliset.size(); ++i)
		{
				Vihollinen& v = viholliset.at(i);

				vihollisenTilenX = v.kuva.getPosition().x / 30;
				vihollisenTilenY = v.kuva.getPosition().y / 30;
				vihollisenTilenNumero = 27 * (vihollisenTilenY - 1) + vihollisenTilenX;

				if (kentta[vihollisenTilenNumero] == 4)
					v.hyokkaa = true;
				else
					v.kuva.move(v.nopeus * kulunutAika.asSeconds(), 0);		
					
		}
}

void VihollistenKaytto::paivitaVihollistenFramet()
{
	if (!viholliset.empty())
		for (size_t i = 0; i < viholliset.size(); ++i)
		{
			Vihollinen& v = viholliset.at(i);

			if (v.hyokkaa == false)
			{
				if (v.framenNumero >= v.framejenLkm)
					v.framenNumero = 0;
				else
					v.framenNumero++;

				sf::Vector2f entisenSijainti = v.kuva.getPosition();
				v.kuva = framet.at(v.framenNumero);
				v.kuva.setPosition(entisenSijainti);
			}
			else
			{


				if (v.framenNumero >= v.hyokkaysFramejenLkm)
					v.framenNumero = 0;
				else
					v.framenNumero++; 

				sf::Vector2f entisenSijainti = v.kuva.getPosition();
				v.kuva = hyokkaysFramet.at(v.framenNumero);
				v.kuva.setPosition(entisenSijainti);
			
				if (v.framenNumero >= v.hyokkaysFramejenLkm)
					v.tekeeVahinkoa = true;
				else
					v.tekeeVahinkoa = false;

			}

		}
}

void VihollistenKaytto::piirraViholliset(sf::RenderWindow* ikkuna)
{

	if (!viholliset.empty())
		for (size_t i = 0; i < viholliset.size(); ++i)
		{
			ikkuna->draw(viholliset.at(i).kuva);
		}
	
}

void VihollistenKaytto::nollaa()
{
	viholliset.clear();
}

int VihollistenKaytto::haeVihollistenMaara()
{
	return viholliset.size();
}
