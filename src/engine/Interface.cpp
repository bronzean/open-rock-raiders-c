/* Copright the ORR-C Dev Team */
#include "Interface.hpp"

void interface::update()
{
	if(GameState == Level)
	{
		if(def_teleporter < 0) //Check if no default teleporter is set.
		{
			g_teleport_button.state = 0;
			g_teleport_button.update();
		}
		else if(def_teleporter >= 0) //If there is a default teleporter, then do this.
		{
			g_teleport_button.state = 1;
			g_teleport_button.update();
		}

		construct_wall_button.update();
	}

	draw_ui();
}

void interface::draw_ui()
{
	Draw_Message_Handler.draw_all(); //Draw all messages;

	if(GameState == Level)
	{
		if(paused)
		{
			pause_text_spr = TTF_RenderText_Solid(font1, "PAUSED. Press P to continue.", c_white);
			draw((SCREEN_WIDTH / 2) - (pause_text_spr->w / 2), (SCREEN_HEIGHT / 2) - (pause_text_spr->h / 2), pause_text_spr, screen);
		}

		draw((SCREEN_WIDTH - current_layer_sprite->w), 0, current_layer_sprite, screen);
	}
}

void draw_message_handler::add_message(int wx, int wy, int layer, SDL_Surface *to_draw_spr, int message_duration) //Adds a message to be drawn.
{
	world_x_list.push_back(wx); //Store the message's world x.
	world_y_list.push_back(wy); //Store the message's world y.
	draw_what_sprite_list.push_back(to_draw_spr); //Store the message's sprite.
	message_duration_frames_list.push_back(message_duration); //Store the message's duration.
	layer_list.push_back(layer);
	//SDL_FreeSurface(to_draw_spr); //TODO: Make this work. If it is needed.
}

void draw_message_handler::draw_all() //Draw everything it's supposed to draw. This is called at the end of the update function, so that the message is drawn on top of everything else.
{

	int counter = 0; //Used in the below loop.
	for(list_iterator = world_x_list.begin(); list_iterator < world_x_list.end(); list_iterator++, counter++)
	{
		
		if(layer_list[counter] == PCamera->layer && world_x_list[counter] + draw_what_sprite_list[counter]->w >= PCamera->wx && world_x_list[counter] <= (PCamera->wx + SCREEN_WIDTH) && world_y_list[counter] + draw_what_sprite_list[counter]->h >= PCamera->wy && world_y_list[counter] <= (PCamera->wy + SCREEN_HEIGHT)) //Check if the message is onscreen.
		{
			draw(world_x_list[counter] - (PCamera->wx), world_y_list[counter] - (PCamera->wy), draw_what_sprite_list[counter], screen); //Draw the message.
		}

		message_duration_frames_list[counter]--; //"Tick the timer".
		if(message_duration_frames_list[counter] <= 0) //If the message's duration has expired...Remove it from the list.
		{
			world_x_list.erase(world_x_list.begin() + counter);
			world_y_list.erase(world_y_list.begin() + counter);
			layer_list.erase(layer_list.begin() + counter);
			draw_what_sprite_list.erase(draw_what_sprite_list.begin() + counter);
			message_duration_frames_list.erase(message_duration_frames_list.begin() + counter);
		}
	}
}

draw_message_handler Draw_Message_Handler; //Handles all the messages to be drawn.

interface Interface;
