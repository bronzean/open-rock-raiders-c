/* Copright the ORR-C Dev Team */
#include "../main.hpp"

int load_sprites()
{
	teleport_button_spr = img_load2(teleport_button_path);
	if(teleport_button_spr == NULL)
	{
		std::cout << "\nFailed loading teleport button sprite\n";
		return 1;
	}

	no_teleport_button_spr = img_load2(no_teleport_button_path);
	if(no_teleport_button_spr == NULL)
	{
		std::cout << "Failed loading disabled teleport button sprite\n";
		return 1;
	}

	return 0;
}
