#ifndef EFEKTIT_H
#define EFEKTIT_H

//#pragma comment(lib,"glew32.lib")
//#pragma comment(lib,"glu32.lib")
//#pragma comment(lib,"opengl32.lib")

//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace Efektit
{
 
	class Partikkelit
	{
	 public:
		 Partikkelit();
		 ~Partikkelit();
		 void muodostaPartikkeleita(sf::Vector2f, int, sf::Color, bool);
		 void paivitaPartikkelit(sf::Time);
		 void poistaPartikkeleita(vector<size_t>);
		 void piirra(sf::RenderWindow*);
	
	 private:
		 struct Hiukkanen
		 {
			 sf::Time elinaika;
			 float nopeus, kulmakerroin;
			 bool painovoimaAlas;
		 };
		 Hiukkanen lisattavaHiukkanen;
		 vector<Hiukkanen> tiedot;
		 vector<sf::Vertex> listaPartikkeleista;
	};

	class Varjostin
	{
	 public:
		 Varjostin();
		 ~Varjostin();
		 void kaytaVarjostinta(sf::RenderWindow*, sf::Sprite);
		 void kaytaVarjostinta(sf::RenderWindow*, sf::CircleShape);
		 void kaytaVarjostinta(sf::RenderWindow*, sf::VertexArray);

	 private:
		 sf::Shader varjostin;
		 sf::RenderStates tila;

	};



	
};

#endif