/* Copright the ORR-C Dev Team */
//This file contains *almost* all the classes that the engine uses

#pragma once
#include "../Engine.hpp"

//The timer, used mainly for the FPS, but probably can also be used in random functions and such.
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};


/////////////////////////////////////////////////
//Button Class
/////////////////////////////////////////////////
class button
{
public:
	int x1, y1, x2, y2, dx2, dy2; //Location related stuff.
	int mx, my;
	SDL_Surface *sprite; //The object's sprite.
	SDL_Surface *d_sprite; //The disabled version's sprite
	bool enabled; //Is it enabled?
	int state; //Is it pressed, disabled (as in clicks don't count but it still draws), or is it just waiting to be clicked. 0 for disabled. 1 for enabled.

	//Initializes the button
	void init(int button_width, int button_height, int X, int Y, SDL_Surface *SPRITE, SDL_Surface *D_SPRITE); //TODO: Make it be able to recieve more than one sprite to set the sprites for a disbaled version, a highlighted version, and a pressed version of the button.
	void init(int button_width, int button_height, SDL_Surface *SPRITE, SDL_Surface *D_SPRITE);

	bool clicked(); //Check if the button was clicked.
	void update(); //Updates whatever needs updating.
};


//////////////////////////
//The Camera Class
//////////////////////////
class camera
{
public:
	//the camera's world x, y, and layer.
	int wx, wy, layer;

	//the constructor
	camera(int test);
	//set the camera's position
	void set_pos(int WX, int WY);
	int get_wx(); //Get its world x.
	int get_wy(); //Get its world y.
	//follow an object
	void follow(int WX, int WY);
};
