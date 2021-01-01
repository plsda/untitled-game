#include "Efektit.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;
using namespace Efektit;

#define USE_MATH_DEFINES_

Partikkelit::Partikkelit()
{
	srand((int)time(0));
}

Partikkelit::~Partikkelit()
{
	
}

void Partikkelit::muodostaPartikkeleita(sf::Vector2f sijainti, int maara, sf::Color vari, bool painovoimaAlas)
{
	for (int i = 0; i <= maara; i++)
	{
		sf::Vertex lisattava;
		lisattava.position = sijainti;
		lisattava.color = vari;

		lisattavaHiukkanen.elinaika = sf::milliseconds((rand() % 2000) + 100);
		lisattavaHiukkanen.kulmakerroin = sin((rand() % 360)) / cos((rand() % 360));
		lisattavaHiukkanen.nopeus = ((rand() % 100));
		lisattavaHiukkanen.painovoimaAlas = painovoimaAlas;

		tiedot.push_back(lisattavaHiukkanen);
		listaPartikkeleista.push_back(lisattava);
	}
	


}

void Partikkelit::paivitaPartikkelit(sf::Time kulunutAika)
{

	if (!tiedot.empty() && !listaPartikkeleista.empty())
	{
		vector<size_t> poistettavat;

		for (size_t i = 0; i < tiedot.size(); ++i)
		{
			Hiukkanen& h = tiedot.at(i);
			h.elinaika -= kulunutAika;

			if (h.elinaika <= sf::Time::Zero)
			{
				if (i <= 0)
				{
					tiedot.erase(tiedot.begin());
					listaPartikkeleista.erase(listaPartikkeleista.begin());
				}
				else
				{
					tiedot.erase(tiedot.begin() + i);
					listaPartikkeleista.erase(listaPartikkeleista.begin() + i);
				}
				//poistettavat.push_back(i);
				continue; //järjesteleminen esim. elinajan/värin perusteella voisi nopeuttaa poistamista ja läpikäyntiä myös binäärihaku
			}

			if (h.painovoimaAlas)
				listaPartikkeleista[i].position += sf::Vector2f(h.nopeus * kulunutAika.asSeconds(), h.kulmakerroin * kulunutAika.asSeconds() + 9.81 * kulunutAika.asSeconds());
			else
				listaPartikkeleista[i].position += sf::Vector2f(h.nopeus * kulunutAika.asSeconds(), h.kulmakerroin * kulunutAika.asSeconds() - 9.81 * kulunutAika.asSeconds());
			
			listaPartikkeleista[i].color.a = h.elinaika.asSeconds() * 255;

		}

		//if (!poistettavat.empty())
		//	poistaPartikkeleita(poistettavat);

	}
}

void Partikkelit::poistaPartikkeleita(vector<size_t> poistettavat)
{
	vector<Hiukkanen> kaytettavatTiedot;
	vector<sf::Vertex> kaytettavatPartikkelit;
	
	size_t j = 0;
	for (size_t i = 0; i < tiedot.size(); ++i)
	{
		if (i == poistettavat.at(j))
		{
			if (j < poistettavat.size() - 1)
			{
				j++;
			}

			continue;
		}
		
		kaytettavatTiedot.push_back(tiedot.at(i));
		kaytettavatPartikkelit.push_back(listaPartikkeleista.at(i));

	}

	tiedot = kaytettavatTiedot;
	listaPartikkeleista = kaytettavatPartikkelit;
}

void Partikkelit::piirra(sf::RenderWindow* ikkuna)
{
	if (!listaPartikkeleista.empty())
		ikkuna->draw(&listaPartikkeleista[0], listaPartikkeleista.size(), sf::Points);
}

Varjostin::Varjostin()
{
	if (!sf::Shader::isAvailable())
		cerr << "Varoitus: varjostimet eivät ole tuettu!" << endl;

	string vertexVarjostin = "void main()"
							 "{"
								 "gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"

								 "gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"

								 "gl_FrontColor = gl_Color;"
							 "}";

	string fragmentVarjostin = "uniform sampler2D texture;"
							   "void main()"
							   "{"
									"vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);"

									"gl_FragColor = gl_Color * pixel;"
								"}";

	if (!varjostin.loadFromMemory(vertexVarjostin, fragmentVarjostin))
		cout << "Virhe varjostimen lataamisessa!" << endl;

	varjostin.setParameter("texture", sf::Shader::CurrentTexture);

	//GLuint fragment;
	//fragment = glCreateShader(GL_FRAGMENT_SHADER);
	

}

Varjostin::~Varjostin()
{

}

void Varjostin::kaytaVarjostinta(sf::RenderWindow* ikkuna, sf::Sprite piirrettavaKuva)
{
	tila.shader = &varjostin;
	ikkuna->draw(piirrettavaKuva, tila);
}

void Varjostin::kaytaVarjostinta(sf::RenderWindow* ikkuna, sf::CircleShape piirrettavaKuva)
{
	tila.shader = &varjostin;
	ikkuna->draw(piirrettavaKuva, tila);
}

void Varjostin::kaytaVarjostinta(sf::RenderWindow* ikkuna, sf::VertexArray piirrettavatKuvat)
{
	tila.shader = &varjostin;
	ikkuna->draw(piirrettavatKuvat, tila);
}
