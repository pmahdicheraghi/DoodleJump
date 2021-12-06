#include <string>
#include "structs.hpp"
#include "doodler.hpp"
#include "RSDL/src/rsdl.hpp"

#ifndef __OBJECTS_HPP__
#define __OBJECTS_HPP__

class Object
{
    public:
    Object(int x, int y);
    bool is_out_of_range();
    void change_vertical_position(int y);
    virtual void collision_handeler(Doodler* doodler) = 0;
    virtual void draw_me(Window *window, int window_width, int window_height) = 0;
    virtual void update_position(int y, int window_width, int window_height);
    protected:
    int picture_x;
    int picture_y;
    int width;
    int height;
    Point position;
    Velocity velocity;
    std::string picture;
};

class Platform : public Object
{
    public:
    Platform(int x, int y);
    virtual void collision_handeler(Doodler* doodler);
    virtual void draw_me(Window *window, int window_width, int window_height);
};

class Mplatform : public Object
{
    public:
    Mplatform(int x, int y);
    virtual void collision_handeler(Doodler* doodler);
    virtual void draw_me(Window *window, int window_width, int window_height);
    virtual void update_position(int y, int window_width, int window_height);
};

class Bplatform : public Object
{
    public:
    Bplatform(int x, int y);
    virtual void collision_handeler(Doodler* doodler);
    virtual void draw_me(Window *window, int window_width, int window_height);
};

class Spring : public Object
{
    public:
    Spring(int x, int y);
    virtual void collision_handeler(Doodler* doodler);
    virtual void draw_me(Window *window, int window_width, int window_height);
};

class Enemy : public Object
{
    public:
    Enemy(int x, int y);
    virtual void collision_handeler(Doodler* doodler);
    virtual void draw_me(Window *window, int window_width, int window_height);
};

#endif