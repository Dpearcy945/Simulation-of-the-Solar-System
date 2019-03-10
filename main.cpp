//Donovan Pearcy

#include <iostream>
#include <string>
#include "nbody.hpp"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <iomanip>
#include <memory>
using namespace std;

int main(int argc, char* argv[])
{
	double displayTime = atof(argv[1]);
	double deltaT = atof(argv[2]);
	//size of the window
	double wSize;
	//the number of Bodies
	int gSize;
	float xscale = 900000000; //10e8 - 10e7
	double secondsElapsed = 0.0;
	//cout << "number of bodies, and size" << endl;
	cin >> gSize >> wSize;
	wSize = (wSize/xscale);
	
	sf::RenderWindow window(sf::VideoMode(2*wSize, 2*wSize), "Stellar Diagram");
	window.setFramerateLimit(40);

	//the vector that holds all of the body objects
	
	vector <unique_ptr<Body>> Galaxy;
	
	//the vector that holds all of the textures
	vector <unique_ptr<sf::Texture>> texture_pack;

	for(int i = 0; i < gSize; i++)
	{
		
		unique_ptr<Body> uTempBody(new Body);
		unique_ptr<sf::Texture> uTempText(new sf::Texture);
		Galaxy.push_back(move(uTempBody));
		texture_pack.push_back(move(uTempText));
		
		cin >> *Galaxy[i];

		//load the texture, and then the next command is setting the sprites texture to the loaded texture
		if(!texture_pack[i]->loadFromFile(Galaxy[i]->get_fname()))
			{return -1;}

		Galaxy[i]->setTexture(*texture_pack[i]);

	}

	/*sf::Text timeElapsed;
	timeElapsed.setString("0.0");
	timeElapsed.setColor(sf::Color::White);
	timeElapsed.setStyle(sf::Text::Bold);
	timeElapsed.setPosition(30, 30);
	*/
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		} 
		if(secondsElapsed >= displayTime)
		{
			window.close();
		}


		window.clear(sf::Color::Black);
		
		//in this loop the planets are drawn using their current coordinates
		for(int i = 0; i < gSize; i++)
		{
			window.draw(*Galaxy[i]);
			//calculates the middle of the galaxy and place the object in relation to it
			Galaxy[i]->setPosition(wSize+(Galaxy[i]->get_x_pos()/xscale),
				wSize+(Galaxy[i]->get_y_pos()/xscale));
			Galaxy[i]->step(deltaT);

			//cout << *Galaxy[i] << endl;
		}
	
		for(int j = 0; j < gSize; j++)
			{
				double dist, force, xf, yf;
				for(int k = 0; k < size; k++)
				{
					if(k != j){
						dist = calc_dist(galaxy[k]->get_x_pos(), galaxy[j]->get_x_pos(), 
							galaxy[k]->get_y_pos(), galaxy[j]->get_y_pos());

						force = calc_force(dist, galaxy[k]->get_mass(), galaxy[j]->get_mass());
						xf = calc_XF(force, galaxy[k]->get_x_pos(), galaxy[j]->get_x_pos(), dist);
						yf = calc_YF(force, galaxy[k]->get_y_pos(), galaxy[j]->get_y_pos(), dist);
						galaxy[j]->set_x_vel(galaxy[j]->get_x_vel() + ((xf*deltaT)/galaxy[j]->get_mass()));
						galaxy[j]->set_y_vel(galaxy[j]->get_y_vel() + ((yf*deltaT)/galaxy[j]->get_mass()));
					}
				}
		}
		//display the passing of time
		/*window.draw(timeElapsed);

		timeElapsed.setString(to_string(secondsElapsed));
		*/
		cout << "Time: " << secondsElapsed << endl;
		secondsElapsed += deltaT;
		
		window.display();
	}
	cout << "The output of the Simulation yields:" << endl;
	cout << gSize <<endl << wSize << endl;
	for(int i = 0; i < gSize; i++)
	{
		cout << *Galaxy[i] << endl;
	}
	return 0;
}
