#include <iostream>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Ohjelma.h"
using namespace std;

int main()
{

	try
	{
		srand((int)time(0));
		sf::Event tapahtuma;
		sf::ContextSettings settings;
		settings.antialiasingLevel = 10;
		sf::RenderWindow ikkuna(sf::VideoMode(800, 600), "Peli", sf::Style::Default, settings);
		ikkuna.setActive(false);
		Ohjelma* pPeli = new Ohjelma("Assets\\ValikonTausta.png", "Assets\\PelinTausta.png", "Assets\\TileMapKuvatEsineet.png", "Assets\\SourceSansPro-Black.ttf", &ikkuna, &tapahtuma);

		enum ohjelmaTilat
		{
			PELAA = 1, OHJEET, VALIKKO, ODOTA, PELI_OHI
		};
		unsigned short int pelinTila = VALIKKO;
		sf::Clock kello;
		sf::Time aika;

		while (ikkuna.isOpen())
		{
			ikkuna.clear(sf::Color::Black);
			aika = kello.getElapsedTime();
			
			while (ikkuna.pollEvent(tapahtuma))
			{
				if (tapahtuma.type == sf::Event::Closed)
					ikkuna.close();

				if (tapahtuma.type == sf::Event::KeyPressed)
				{
					if (tapahtuma.key.code == sf::Keyboard::Escape)
					{
						pPeli->nollaaPeli();
						pelinTila = VALIKKO;
					}
				

					if (tapahtuma.key.code == sf::Keyboard::P)
					{
						if (pelinTila == ODOTA)
						{
							pelinTila = PELAA;
							pPeli->jatkaPelia();
							clog << "JATKA" << endl;
						}
						else
						{
							pelinTila = ODOTA;
							clog << "ODOTA" << endl;
						}
					}

				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (pelinTila == PELAA && tapahtuma.type != sf::Event::MouseMoved)
					{
						if (aika.asMilliseconds() >= 500)
						{
							pPeli->ammu();
							aika.Zero;
							kello.restart();
						}
					}
					else
					{
						if (pPeli->onkoPelaaValittu() && pelinTila == VALIKKO)
						{
							pelinTila = PELAA;
							clog << "PELAA" << endl;
						}
						
						if (pPeli->onkoOhjeetValittu() && pelinTila == VALIKKO)
						{
							pelinTila = OHJEET;
							clog << "OHJEET" << endl;
						}
						
						if (pPeli->onkoPeliOhiValittu() && pelinTila == PELI_OHI)
						{
							pPeli->nollaaPeli();
							pelinTila = VALIKKO;
						}

						

					}

				}

			}
			
			if (pPeli->tykkiOnTuhoutunut)
			{
				pelinTila = PELI_OHI;
			}

			switch (pelinTila)
			{
				case PELAA: pPeli->aloitaPeli(); break;
				case OHJEET: pPeli->piirraOhjeet(); break;
				case VALIKKO: pPeli->piirraValikko(); break;
				case ODOTA: pPeli->pysaytaPeli(); break;
				case PELI_OHI: pPeli->piirraPeliOhi();break;
			}

			ikkuna.display();
		
		}

		delete pPeli;

		return 0;

	}
	catch (exception &e)
	{
		cerr << "Virhe: " << e.what() << endl;
		cerr << "Tiedot: " << typeid(e).name() << endl;
	}

	getchar();

}
