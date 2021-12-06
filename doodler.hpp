#include <string>
#include "structs.hpp"
#include "RSDL/src/rsdl.hpp"

#ifndef __DOODLER_HPP__
#define __DOODLER_HPP__

class Doodler
{
public:
	Doodler(int x, int y);
	int get_score();
	int get_width();
	int get_height();
	bool is_ghost();
	bool is_out_of_range();
	void you_are_dead();
	void draw_me(Window *window, int window_width, int window_height);
	void set_horizontal_velocity(float vx);
	void set_vertical_velocity(float vy);
	void update_position(int window_width, int window_height);
	void change_vertical_position(int y);
	Point get_position();
	Velocity get_velocity();

private:
	void update_picture();
	Acceleration acceleration;
	Velocity velocity;
	Point position;
	std::string picture;
	int height;
	int width;
	int score;
	bool ghost;
};

#endif