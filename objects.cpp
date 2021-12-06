#include "objects.hpp"
#include "doodler.hpp"
#include <iostream>

Object::Object(int x, int y)
{
	position.x = x;
	position.y = y;
	picture = "assets//main pictures//game-tiles2.png";
	velocity.x = 0;
	velocity.y = 0;
}

Platform::Platform(int x, int y) : Object(x, y)
{
	width = 120;
	height = 36;
	picture_x = 0;
	picture_y = 0;
}

Mplatform::Mplatform(int x, int y) : Object(x, y)
{
	velocity.x = 5;
	width = 120;
	height = 36;
	picture_x = 0;
	picture_y = 36;
}

Bplatform::Bplatform(int x, int y) : Object(x, y)
{
	width = 120;
	height = 36;
	picture_x = 0;
	picture_y = 144;
}

Spring::Spring(int x, int y) : Object(x, y)
{
	width = 120;
	height = 72;
	picture_x = 1052;
	picture_y = 550;
}

Enemy::Enemy(int x, int y) : Object(x, y)
{
	width = 136;
	height = 184;
	picture_x = 125;
	picture_y = 0;
}

void Object::update_position(int y, int window_width, int window_height)
{
	if (y > 0)
	{
		position.y -= y;
	}
}

void Mplatform::update_position(int y, int window_width, int window_height)
{
	if (y > 0)
	{
		position.y -= y;
	}

	position.x += velocity.x;
	if (position.x > window_width - width/2 || position.x < width/2)
	{
		velocity.x = -velocity.x;
	}
}

bool Object::is_out_of_range()
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

void Platform::draw_me(Window *window, int window_width, int window_height)
{
	window->draw_img(picture, Rectangle(position.x - width/2, window_height -(position.y + height), width, height),
	Rectangle(picture_x, picture_y, width, height));
}

void Mplatform::draw_me(Window *window, int window_width, int window_height)
{
	window->draw_img(picture, Rectangle(position.x - width/2, window_height -(position.y + height), width, height),
	Rectangle(picture_x, picture_y, width, height));
}

void Bplatform::draw_me(Window *window, int window_width, int window_height)
{
	window->draw_img(picture, Rectangle(position.x - width/2, window_height -(position.y + height), width, height),
	Rectangle(picture_x, picture_y, width, height));
}

void Spring::draw_me(Window *window, int window_width, int window_height)
{
	window->draw_img(picture, Rectangle(position.x - width/2, window_height -(position.y + height), width, height),
	Rectangle(picture_x, picture_y, width, height));
}

void Enemy::draw_me(Window *window, int window_width, int window_height)
{
	window->draw_img(picture, Rectangle(position.x - width/2, window_height -(position.y + height), width, height),
	Rectangle(picture_x, picture_y, width, height));
}

void Bplatform::collision_handeler(Doodler* doodler)
{
	if (doodler->is_ghost())
	{
		return;
	}
	int delta_y = position.y - doodler->get_position().y;
	int delta_x = position.x - doodler->get_position().x;
	if(delta_y >= -height && doodler->get_velocity().y < 0 && -doodler->get_velocity().y > delta_y)
	{
		if(delta_x < (doodler->get_width() + width)/2 && delta_x > -(doodler->get_width() + width)/2)
		{
			picture_y = 234;
			height = 55;
		}
	}
}

void Platform::collision_handeler(Doodler* doodler)
{
	if (doodler->is_ghost())
	{
		return;
	}
	int delta_y = position.y - doodler->get_position().y;
	int delta_x = position.x - doodler->get_position().x;
	if(delta_y >= -height && doodler->get_velocity().y < 0 && -doodler->get_velocity().y > delta_y)
	{
		if(delta_x < (doodler->get_width() + width)/2 && delta_x > -(doodler->get_width() + width)/2)
		{
			doodler->set_vertical_velocity(25);
		}
	}
}

void Mplatform::collision_handeler(Doodler* doodler)
{
	void horizontal_move();
	if (doodler->is_ghost())
	{
		return;
	}
	int delta_y = position.y - doodler->get_position().y;
	int delta_x = position.x - doodler->get_position().x;
	if(delta_y >= -height && doodler->get_velocity().y < 0 && -doodler->get_velocity().y > delta_y)
	{
		if(delta_x < (doodler->get_width() + width)/2 && delta_x > -(doodler->get_width() + width)/2)
		{
			doodler->set_vertical_velocity(25);
		}
	}
}

void Enemy::collision_handeler(Doodler* doodler)
{
	if (doodler->is_ghost())
	{
		return;
	}
	int delta_y = position.y - doodler->get_position().y;
	int delta_x = position.x - doodler->get_position().x;
	if(delta_y < doodler->get_height() && delta_y > -height)
	{
		if(delta_x < (doodler->get_width() + width)/2 && delta_x > -(doodler->get_width() + width)/2)
		{
			doodler->set_vertical_velocity(0);
			doodler->you_are_dead();
		}
	}
}

void Spring::collision_handeler(Doodler* doodler)
{
	if (doodler->is_ghost())
	{
		return;
	}
	int delta_y = position.y - doodler->get_position().y;
	int delta_x = position.x - doodler->get_position().x;
	if(delta_y >= -height/2 && doodler->get_velocity().y < 0 && -doodler->get_velocity().y > delta_y)
	{
		if(delta_x < (doodler->get_width() + width)/2 && delta_x > -(doodler->get_width() + width)/2)
		{
			doodler->set_vertical_velocity(40);
			picture_y = 455;
		}
	}
}