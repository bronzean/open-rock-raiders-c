/* Copyright the ORR-C Dev Team */
#include "Interface.hpp"

interface::interface() //Constructor.
{
}

interface::~interface() //Deconstructor.
{
}

void interface::update()
{
	if(!server)
	{
		if(GameState == Level)
		{
			if(!def_teleporter) //Check if no default teleporter is set.
			{
				g_teleport_button.state = 0;
				g_teleport_button.update();
			}
			else if(def_teleporter) //If there is a default teleporter, then do this.
			{
				g_teleport_button.state = 1;
				g_teleport_button.update();
			}

			construct_wall_button.update();
			construct_door_button.update();

			if(active_popup_menu)
			{
				active_popup_menus[0]->draw_menu(); //Draw the currently active popup menu.
			}
		}
	}

	//if(screen_needs_updating == false)
	//{
		draw_ui();
	//}

	draw_sprites_that_need_drawing();
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

void draw_message_handler::add_message(int wx, int wy, int layer, SDL_Surface *to_draw_spr, int message_duration, bool global) //Adds a message to be drawn.
{
	message new_message; //The new message.
	new_message.world_x = wx; //Store the message's world x.
	new_message.world_y = wy; //Store the message's world y.
	new_message.layer = layer; //Store the message's layer.
	new_message.global = global; //Stores whether or not the message is global.
	new_message.sprite = to_draw_spr; //Store the message's sprite.
	new_message.message_duration = message_duration; //Store the message's duration.
	messages.push_back(new_message); //Finally add the new message to the message vector.
}

void draw_message_handler::add_message2(int wx, int wy, int layer, SDL_Surface **to_draw_spr, int message_duration, bool global) //Adds a message to be drawn.
{
	message new_message; //The new message.
	new_message.world_x = wx; //Store the message's world x.
	new_message.world_y = wy; //Store the message's world y.
	new_message.layer = layer; //Store the message's layer.
	new_message.global = global; //Stores whether or not the message is global.
	new_message.sprite = *to_draw_spr; //Store the message's sprite.
	new_message.message_duration = message_duration; //Store the message's duration.
	messages.push_back(new_message); //Finally add the new message to the message vector.
}

void add_message3(int wx, int wy, int layer, SDL_Surface to_draw_spr, int message_duration, bool global) //Adds a message to be drawn.
{
}

void draw_message_handler::draw_all() //Draw everything it's supposed to draw. This is called at the end of the update function, so that the message is drawn on top of everything else.
{
	int counter = 0; //Used in the below loop.
	for(_iterator = messages.begin(); _iterator < messages.end(); _iterator++, counter++)
	{
		if(messages[counter].message_duration <= 0) //If the message's duration has expired...Remove it from the list.
		{
			messages.erase(messages.begin() + counter);
		}
		else
		{
			if(!messages[counter].global)
			{
				if(messages[counter].layer == PCamera->layer && messages[counter].world_x + messages[counter].sprite->w >= PCamera->wx && messages[counter].world_x <= (PCamera->wx + SCREEN_WIDTH) && messages[counter].world_y + messages[counter].sprite->h >= PCamera->wy && messages[counter].world_y <= (PCamera->wy + SCREEN_HEIGHT)) //Check if the message is onscreen.
				{
					if(allow_draw)
					{
						draw(messages[counter].world_x - (PCamera->wx), messages[counter].world_y - (PCamera->wy), messages[counter].sprite, screen); //Draw the message.
					}
				}
			}
			else
			{
				if(allow_draw)
				{
					draw(messages[counter].world_x, messages[counter].world_y, messages[counter].sprite, screen); //Draw the message.
				}
			}

			messages[counter].message_duration--; //"Tick the timer".
		}
	}
}

void interface::draw_sprites_that_need_drawing() //Draw the sprites that need drawing.
{
	for(int i = 0; i < sprites_to_draw.size(); i++)
	{
		if(allow_draw)
		{
			sprites_to_draw[i]->draw_sprite();
		}
	}

	sprites_to_draw.clear(); //Empty this.
}

void interface::add_sprite_that_needs_drawing(sprite_wrapper *_sprite) //Add a sprite to the sprites_to_draw vector.
{
	sprites_to_draw.push_back(_sprite); //Store the sprite.
}

draw_message_handler Draw_Message_Handler; //Handles all the messages to be drawn.

interface Interface;
