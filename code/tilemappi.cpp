#include "TileMappi.h"
#include <iostream>
using namespace std;

bool TileMappi::lataa(sf::Texture kuva, int kentta[], int kokoX, int kokoY, int leveys, int korkeus)
{
	this->kokoX = kokoX;
	this->kokoY = kokoY;
	this->leveys = leveys;
	this->korkeus = korkeus;

	tekstuuri = kuva;

	kuutiot.setPrimitiveType(sf::Quads);
	kuutiot.resize(leveys * korkeus * 4);

	for (int i = 0; i < korkeus; ++i)
		for (int j = 0; j < leveys; ++j) 
		{
			int tileId = kentta[j + i * leveys];

			sf::Vertex* kuutio = &kuutiot[(j + i * leveys) * 4];

			kuutio[0].position = sf::Vector2f(j * kokoX, i * kokoY);
			kuutio[1].position = sf::Vector2f((j + 1) * kokoX, i * kokoY);
			kuutio[2].position = sf::Vector2f((j + 1) * kokoX, (i + 1) * kokoY);
			kuutio[3].position = sf::Vector2f(j * kokoX, (i + 1) * kokoY);

			kuutio[0].texCoords = sf::Vector2f(0, tileId * kokoY);
			kuutio[1].texCoords = sf::Vector2f(kokoX, tileId * kokoY);
			kuutio[2].texCoords = sf::Vector2f(kokoX, (tileId + 1) * kokoY);
			kuutio[3].texCoords = sf::Vector2f(0, (tileId + 1) * kokoY);


	}

	return true;
}

void TileMappi::paivita(int kentta[], bool rakennusTila)
{
	for(int i = 0; i < korkeus; ++i)
	{
		for(int j = 0; j < leveys; ++j)
		{
			int tileId = kentta[j + i * leveys];

			sf::Vertex* kuutio = &kuutiot[(j + i * leveys) * 4];

			if (rakennusTila && tileId == 7 && (kentta[j + i * leveys + leveys] == 0 || kentta[j + i * leveys + leveys] == 4))
			{
				kuutio[0].texCoords = sf::Vector2f(0, 8 * kokoY);
				kuutio[1].texCoords = sf::Vector2f(kokoX, 8 * kokoY);
				kuutio[2].texCoords = sf::Vector2f(kokoX, (8 + 1) * kokoY);
				kuutio[3].texCoords = sf::Vector2f(0, (8 + 1) * kokoY);
			}
			else if (rakennusTila && tileId == 7)
			{
				kuutio[0].texCoords = sf::Vector2f(0, 9 * kokoY);
				kuutio[1].texCoords = sf::Vector2f(kokoX, 9 * kokoY);
				kuutio[2].texCoords = sf::Vector2f(kokoX, (9 + 1) * kokoY);
				kuutio[3].texCoords = sf::Vector2f(0, (9 + 1) * kokoY);
			}
			else 
			{
				kuutio[0].texCoords = sf::Vector2f(0, tileId * kokoY);
				kuutio[1].texCoords = sf::Vector2f(kokoX, tileId * kokoY);
				kuutio[2].texCoords = sf::Vector2f(kokoX, (tileId + 1) * kokoY);
				kuutio[3].texCoords = sf::Vector2f(0, (tileId + 1) * kokoY);
			}

			kuutio[0].position = sf::Vector2f(j * kokoX, i * kokoY);
			kuutio[1].position = sf::Vector2f((j + 1) * kokoX, i * kokoY);
			kuutio[2].position = sf::Vector2f((j + 1) * kokoX, (i + 1) * kokoY);
			kuutio[3].position = sf::Vector2f(j * kokoX, (i + 1) * kokoY);

	   }
	}
}

void TileMappi::paivitaYksi(int kentta[], int indeksiX, int indeksiY, bool rakennusTila)
{
	int tileId = kentta[indeksiX * indeksiY];

	sf::Vertex* kuutio = &kuutiot[indeksiX * indeksiY * 4];

	if (rakennusTila && tileId == 7 && (kentta[indeksiX + indeksiY * leveys + leveys] == 0 || kentta[indeksiX + indeksiY * leveys + leveys] == 4))
	{
		kuutio[0].texCoords = sf::Vector2f(0, 8 * kokoY);
		kuutio[1].texCoords = sf::Vector2f(kokoX, 8 * kokoY);
		kuutio[2].texCoords = sf::Vector2f(kokoX, (8 + 1) * kokoY);
		kuutio[3].texCoords = sf::Vector2f(0, (8 + 1) * kokoY);
	}
	else if (rakennusTila && tileId == 7)
	{
		kuutio[0].texCoords = sf::Vector2f(0, 9 * kokoY);
		kuutio[1].texCoords = sf::Vector2f(kokoX, 9 * kokoY);
		kuutio[2].texCoords = sf::Vector2f(kokoX, (9 + 1) * kokoY);
		kuutio[3].texCoords = sf::Vector2f(0, (9 + 1) * kokoY);
	}

	kuutio[0].position = sf::Vector2f(indeksiX * kokoX, indeksiY * kokoY);
	kuutio[1].position = sf::Vector2f((indeksiX + 1) * kokoX, indeksiY * kokoY);
	kuutio[2].position = sf::Vector2f((indeksiX + 1) * kokoX, (indeksiY + 1) * kokoY);
	kuutio[3].position = sf::Vector2f(indeksiX * kokoX, (indeksiY + 1) * kokoY);
}

void TileMappi::piirra(sf::RenderWindow* ikkuna)
{
	ikkuna->draw(kuutiot, &tekstuuri);
}
