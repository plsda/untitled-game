#ifndef TILEMAPPI_H
#define TILEMAPPI_H

#include <SFML/Graphics.hpp>
using namespace std;

class TileMappi
{
public:
	bool lataa(sf::Texture, int[], int, int, int, int);
	void paivita(int[], bool);
	void paivitaYksi(int[], int, int, bool);
	void piirra(sf::RenderWindow*);

private:
	sf::VertexArray kuutiot;
	sf::Texture tekstuuri;
	int kokoX, kokoY, leveys, korkeus;

};

#endif