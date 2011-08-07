/* Copyright the ORR-C Dev Team */
#include "construction.hpp"

void construction::update_connections() //Updates this tile's connection sprite.
{
	if(!neighbour_left && !neighbour_right && !neighbour_up && !neighbour_down) //If it has no neighbours.
	{
		connection = NULL; //No connection!

		cout << "No connection.\n";
	}
	else //Has atleast one connection.
	{
		bool done = false;
		if(neighbour_left && neighbour_right && neighbour_up && neighbour_down) //If it has neighbours on all four sides.
		{
			connection = four_way_spr; //The connection is four ways.
			done = true; //No need to continue.

			cout << "four way.\n";
		}

		if(!done)
		{
			if(neighbour_left && neighbour_right && neighbour_down && !neighbour_up) //If it has neighbours to the left, right, and down.
			{
				connection = horz_downcon_spr;
				done = true;

				cout << "horz downcon.\b";
			}
		}

		if(!done)
		{
			if(neighbour_left && neighbour_right && !neighbour_down && !neighbour_up) //If it has neighbours to the left and right.
			{
				connection = horz_endsopen_spr;
				done = true;

				cout << "horz endsopen\n";
			}
		}

		if(!done)
		{
			if(neighbour_left && neighbour_down && !neighbour_right && !neighbour_up) //If it has neighbours to the left and down.
			{
				connection = corner_left_down_spr;
				done = true;

				cout << "corner left down.\n";
			}
		}

		if(!done)
		{
			if(neighbour_left && neighbour_up && !neighbour_down && !neighbour_right) //If it has a neighbour to the left and up.
			{
				connection = corner_left_up_spr;
				done = true;

				cout << "corner left up.\n";
			}
		}

		if(!done)
		{
			if(neighbour_right && neighbour_down && !neighbour_left && !neighbour_up) //If it has a neighbour to the right and down.
			{
				connection = corner_right_down_spr;
				done = true;

				cout << "corner right down.\n";
			}
		}

		if(!done)
		{
			if(neighbour_right && neighbour_up && !neighbour_down && !neighbour_left) //If it has a neighbour to the right and up.
			{
				cout << "corner right up.\n";

				connection = corner_right_up_spr;
				done = true;
			}
		}

		if(!done)
		{
			if(neighbour_right && !neighbour_up && !neighbour_down && !neighbour_left) //If it has a neighbour to the right.
			{
				connection = horz_leftend_spr;
				done = true;

				cout << "horz leftend.\n";
			}
		}

		if(!done)
		{
			if(neighbour_left && !neighbour_up && !neighbour_down && !neighbour_right) //If it has a neighbour to the left.
			{
				connection = horz_rightend_spr;
				done = true;

				cout << "horz rightend.\n";
			}
		}

		if(!done)
		{
			if(neighbour_up && !neighbour_down && !neighbour_left && !neighbour_right) //If it has a neighbour up.
			{
				connection = vert_downend_spr;
				done = true;

				cout << "vert downend.\n";
			}
		}

		if(!done)
		{
			if(neighbour_up && neighbour_down && !neighbour_left && !neighbour_right) //If it has a neighbour up and a neighbour down.
			{
				connection = vert_endsopen_spr;
				done = true;

				cout << "vert endsopen.\n";
			}
		}

		if(!done)
		{
			if(neighbour_up && neighbour_down && neighbour_left && !neighbour_right) //If it has a neighbour up, down, and left.
			{
				connection = vert_leftcon_spr;
				done = true;

				cout << "vert leftcon.\n";
			}
		}

		if(!done)
		{
			if(neighbour_up && neighbour_down && neighbour_right && !neighbour_left) //If it has a neighbour to the up, down, and right.
			{
				connection = vert_rightcon_spr;
				done = true;

				cout << "vert rightcon.\n";
			}
		}

		if(!done)
		{
			if(neighbour_down && !neighbour_right && !neighbour_left && !neighbour_up) //If it has a neighbour down.
			{
				connection = vert_upend_spr;
				done = true;

				cout << "vert upend.\n";
			}
		}

		if(!done)
		{
			if(neighbour_left && neighbour_right && neighbour_up && !neighbour_down) //If it has neighbours to the left, right, and up.
			{
				connection = horz_upcon_spr;
				done = true;

				cout << "horz upcon.\n";
			}
		}

		if(done)
		{
			cout << "Found connection.\n";
		}
		else
		{
			cout << "Failed to find connection.\n";

			if(neighbour_left)
			{
				cout << "Has neighbour left.\n";
			}
			if(neighbour_right)
			{
				cout << "Has neighbour right\n";
			}
			if(neighbour_up)
			{
				cout << "Has neighbour up\n";
			}
			if(neighbour_down)
			{
				cout << "Has neighbour down.\n";
			}
		}
	}
}
