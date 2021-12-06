#include <string>
#include "doodler.hpp"

Doodler::Doodler(int x, int y)
{
	position.x = x;
	position.y = y;
	picture = "assets//main pictures//right.png";
	width = 62;
	height = 60;
	acceleration.x = 0;
	acceleration.y = -0.8;
	velocity.x = 0;
	velocity.y = 25;
	score = 0;
	ghost = false;
}

int Doodler::get_score()
{
	return score;
}

int Doodler::get_width()
{
	return width;
}

int Doodler::get_height()
{
	return height;
}

bool Doodler::is_ghost()
{
	return ghost;
}

void Doodler::you_are_dead()
{
	ghost = true;
}

bool Doodler::is_out_of_range()
{
	if (position.y + height < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Doodler::draw_me(Window *window, int window_width, int window_height)
{
	window->draw_img(picture, Rectangle(position.x - width, window_height -(position.y + 2*height), 2*width, 2*height));
}

void Doodler::set_horizontal_velocity(float vx)
{
	if (ghost)
	{
		return;
	}
	velocity.x = vx;
	if (vx > 0)
		picture = "assets//main pictures//right.png";

	else if (vx < 0)
		picture = "assets//main pictures//left.png";
}

void Doodler::set_vertical_velocity(float vy)
{
	velocity.y = vy;
}

void Doodler::change_vertical_position(int y)
{
	position.y -= y;
	score += y;
}

Point Doodler::get_position()
{
	return position;
}

Velocity Doodler::get_velocity()
{
	return velocity;
}

void Doodler::update_position(int window_width, int window_height)
{
	position.x += velocity.x;
	position.y += velocity.y;
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;
	if (position.x > window_width)
	{
		position.x -= window_width;
	}
	else if (position.x < 0)
	{
		position.x += window_width;
	}
	update_picture();
}

void Doodler::update_picture()
{
	if (velocity.y > 20)
	{
		if (picture == "assets//main pictures//right.png")
		{
			picture = "assets//main pictures//right_jumping.png";
		}
		else if (picture == "assets//main pictures//left.png")
		{
			picture = "assets//main pictures//left_jumping.png";
		}
	}
	else
	{
		if (picture == "assets//main pictures//right_jumping.png")
		{
			picture = "assets//main pictures//right.png";
		}
		else if (picture == "assets//main pictures//left_jumping.png")
		{
			picture = "assets//main pictures//left.png";
		}
	}
}