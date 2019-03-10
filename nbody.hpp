#ifndef NBODY_HPP
#define NBODY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class Body: public sf::Sprite
{
public:
	Body();
	Body(float x_pos, float y_pos, float x_vel, float y_vel, float bmass, string name);
	friend istream& operator >>(istream& fin, Body& nBody);
	friend ostream& operator <<(ostream& out, const Body& nBody);

	void step(double time);

	float get_x_pos();
	float get_y_pos();
	float get_x_vel();
	float get_y_vel();
	float get_mass();
	string get_fname();

	void set_x_pos(float x_pos);
	void set_y_pos(float y_pos);
	void set_x_vel(float x_vel);
	void set_y_vel(float y_pos);
	void set_mass(float bmass);
	void set_file_name(string name);
private:
	float xpos;
	float ypos;
	float xvel;
	float yvel;
	float mass;
	string fname;
};

double calc_force(double dist, double mass1, double mass2);
double calc_dist(float x1, float x2, float y1, float y2);
double calc_XF(float force, float xP1, float xP2, float dist);
double calc_YF(float force, float yP1, float yP2, float dist);

#endif