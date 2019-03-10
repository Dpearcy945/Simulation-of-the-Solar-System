#include "nbody.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iomanip>


Body::Body()
{
	xpos = 0;
	ypos = 0;
	xvel = 0;
	yvel = 0;
	mass = 0;
	fname = '\0';
}
Body::Body(float x_pos, float y_pos, float x_vel, float y_vel, float bmass, string name)
{
	xpos = x_pos;
	ypos = y_vel;
	xvel = x_vel;
	yvel = y_vel;
	mass = bmass;
	fname = name;
}
istream& operator >>(istream &fin, Body &nBody)
{
	fin >> nBody.xpos >> nBody.ypos >> nBody.xvel >> nBody.yvel >> nBody.mass >> nBody.fname;
	
	return fin;
}
ostream& operator <<(ostream& out, const Body& nBody)
{
	//out.width(10);
	//out.precision(4);
	out << setprecision(4) << right << setw(12) << nBody.xpos; 
	out << setprecision(4) << right << setw(12) <<nBody.ypos; 
	out << setprecision(4) << right << setw(12) <<nBody.xvel; 
	out << setprecision(4) << right << setw(12) <<nBody.yvel; 
	out << setprecision(4) << right << setw(12) <<nBody.mass; 
	out << setprecision(4) << right << setw(12) <<nBody.fname;

	return out;
}
//The Value calculators

//distance calculator
double calc_dist(float x1, float x2, float y1, float y2)
{
	float dist, x, y;

	x = x2 - x1;
	y = y2 - y1;
	dist = sqrt((x * x)+(y * y));

	cout << "dist: " << dist << endl;
	return dist;
}
//general gravitational force calculator
double calc_force(double dist, double mass1, double mass2)
{
	double force;
	//universal Gravitational Constant
	double uGC = 6.67e-11;
	

	force = uGC * (mass1 * mass2);
	force = force / pow(dist, 2.0);
	cout << "force: " << force << endl;
	return force;

}
//X and Y components of particle force
double calc_XF(float force, float xP1, float xP2, float dist)
{
	float xforce;
	xforce = force *(xP2 - xP1);
	xforce = xforce / dist;
	cout << "xforce: " << xforce << endl;
	return xforce;
}
double calc_YF(float force, float yP1, float yP2, float dist)
{
	float yforce;
	yforce = force *(yP2 - yP1);
	yforce = yforce / dist;
	cout << "yforce: " << yforce << endl;
	return yforce;
}
//alters position in Body by the velocity private members
void Body::step(double time)
{		
	//cout << "--step--" << endl;
	xpos = xpos - (time * xvel);
	ypos = ypos - (time * yvel);
}
//The Body value getters
float Body::get_x_pos()
{
	return xpos;
}
float Body::get_y_pos()
{
	return ypos;
}
float Body::get_x_vel()
{
	return xvel;
}
float Body::get_y_vel()
{
	return yvel;
}
float Body::get_mass()
{
	return mass;
}
string Body::get_fname()
{
	return fname;
}
//The Body value setters
void Body::set_x_pos(float x_pos)
{
	xpos = x_pos;
}
void Body::set_y_pos(float y_pos)
{
	ypos = y_pos;
}
void Body::set_x_vel(float x_vel)
{
	xvel = x_vel;
}
void Body::set_y_vel(float y_vel)
{
	yvel = y_vel;
}
void Body::set_mass(float bmass)
{
	mass = bmass;
}
void Body::set_file_name(string name)
{
	fname = name;
}