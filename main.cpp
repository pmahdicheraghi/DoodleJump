#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <vector>
#include <fstream>
#include "RSDL/src/rsdl.hpp"
#include "doodler.hpp"
#include "objects.hpp"

using namespace std;
using namespace chrono;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 1024;

void handle_events(Window *window, Doodler *doodler)
{
	char pressed_char;
	while (window->has_pending_event())
	{
		Event new_event = window->poll_for_event();
		switch (new_event.get_type())
		{
		case Event::EventType::QUIT:
			exit(0);
			break;

		case Event::KEY_PRESS:
			pressed_char = new_event.get_pressed_key();
			if (pressed_char == 'a')
			{
				doodler->set_horizontal_velocity(-10);
			}
			else if (pressed_char == 'd')
			{
				doodler->set_horizontal_velocity(10);
			}
			break;

		case Event::KEY_RELEASE:
			pressed_char = new_event.get_pressed_key();
			if (pressed_char == 'a')
			{
				if(doodler->get_velocity().x < 0)
				{
					doodler->set_horizontal_velocity(0);
				}
			}
			else if (pressed_char == 'd')
			{
				if(doodler->get_velocity().x > 0)
				{
					doodler->set_horizontal_velocity(0);
				}
			}
			break;

		default:
			break;
		}

	}
}

void update(Window *window, Doodler *doodler, vector<Object*> &objects)
{
	doodler->update_position(WINDOW_WIDTH, WINDOW_HEIGHT);

	int doodler_position_above_center = (doodler->get_position().y - WINDOW_HEIGHT/2);

	if(doodler_position_above_center > 0)
	{
		doodler->change_vertical_position(doodler_position_above_center);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update_position(doodler_position_above_center, WINDOW_WIDTH, WINDOW_HEIGHT);
		objects[i]->collision_handeler(doodler);
		if (objects[i]->is_out_of_range())
		{
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}
}

void render(Window *window, Doodler *doodler, const vector<Object*> &objects)
{
	window->draw_img("assets//main pictures//background.png");
	window->draw_img("assets//main pictures//top-score@2x.png", Rectangle(0, 0, WINDOW_WIDTH, 60));
	window->show_text(to_string(doodler->get_score()), Point(5, 5), BLACK, "Lemon Friday.ttf", 40);
	for (auto object : objects)
	{
		object->draw_me(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	doodler->draw_me(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	window->update_screen();
}

Object* object_creator(string name, int width, int height)
{
	if(name == "platform")
	{
		Object* platform = new Platform(width, height);
		return platform;
	}
	else if(name == "mplatform")
	{
		Object* mplatform = new Mplatform(width, height);
		return mplatform;
	}
	else if(name == "bplatform")
	{
		Object* bplatform = new Bplatform(width, height);
		return bplatform;
	}
	else if(name == "spring")
	{
		Object* spring = new Spring(width, height);
		return spring;
	}
	else if(name == "enemy")
	{
		Object* enemy = new Enemy(width, height);
		return enemy;
	}
}

vector<Object*> read_objects_from_file(string file_name = "static//map.txt")
{
	fstream input_file_stream;
	string temp_input_line;
	
	string object_name;
	string object_width;
	string object_height;

	input_file_stream.open(file_name, ios::in);

	getline(input_file_stream, temp_input_line);

	int number_of_objects = stoi(temp_input_line);

	vector<Object*> objects;

	for (int i = 0; i < number_of_objects; i++)
	{
		input_file_stream >> object_width;
		input_file_stream >> object_height;
		input_file_stream >> object_name;

		objects.push_back(object_creator(object_name, stoi(object_width), stoi(object_height)));
	}

	input_file_stream.close();

	return objects;
}

int main()
{
	auto time_start = high_resolution_clock::now();

	Window* window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Doodle jump");
	Doodler* doodler = new Doodler(320, 100);

	vector<Object*> objects = read_objects_from_file();

	while (true)
	{
		handle_events(window, doodler);
		if (doodler->is_out_of_range())
		{
			break;
		}
		update(window, doodler, objects);
		render(window, doodler, objects);

		auto delta_time = duration_cast<milliseconds>(high_resolution_clock::now() - time_start);
		delay(20 - (delta_time.count() % 20));
		time_start = high_resolution_clock::now();
	}
	while (true)
	{
		window->draw_img("assets//main pictures//background.png");
		window->draw_img("assets//main pictures//top-score@2x.png", Rectangle(0, 0, WINDOW_WIDTH, 60));
		for (auto object : objects)
		{
			object->draw_me(window, WINDOW_WIDTH, WINDOW_HEIGHT);
		}
		window->draw_img("assets//main pictures//doodlestein-darkness@2x.png");
		window->show_text("Game Over", Point(200, WINDOW_HEIGHT/2 - 50), RED, "static//Lemon Friday.ttf", 50);
		window->show_text("YOUR SCORE IS: " + to_string(doodler->get_score()), Point(140, WINDOW_HEIGHT/2 + 50), BLACK, "Lemon Friday.ttf", 40);
		window->update_screen();
		while (window->has_pending_event())
		{
			Event new_event = window->poll_for_event();
			switch (new_event.get_type())
			{
			case Event::EventType::QUIT:
			case Event::KEY_PRESS:
				exit(0);
				break;
			}
		}
	}
}