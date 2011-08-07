/* Copyright the ORR-C Dev Team */
#include "construction.hpp"

void construction::load_connection_sprites(string folderpath) //Draw the construction's sprite.
{
	img_load_safe(folderpath + "4-way.png", &four_way_spr);
	img_load_safe(folderpath + "corner_left-down.png", &corner_left_down_spr);
	img_load_safe(folderpath + "corner_left-up.png", &corner_left_up_spr);
	img_load_safe(folderpath + "corner_right-down.png", &corner_right_down_spr);
	img_load_safe(folderpath + "corner_right-up.png", &corner_right_up_spr);
	img_load_safe(folderpath + "horz_downcon.png", &horz_downcon_spr);
	img_load_safe(folderpath + "horz_endsopen.png", &horz_endsopen_spr);
	img_load_safe(folderpath + "horz_leftend.png", &horz_leftend_spr);
	img_load_safe(folderpath + "horz_rightend.png", &horz_rightend_spr);
	img_load_safe(folderpath + "horz_upcon.png", &horz_upcon_spr);
	img_load_safe(folderpath + "vert_downend.png", &vert_downend_spr);
	img_load_safe(folderpath + "vert_endsopen.png", &vert_endsopen_spr);
	img_load_safe(folderpath + "vert_leftcon.png", &vert_leftcon_spr);
	img_load_safe(folderpath + "vert_rightcon.png", &vert_rightcon_spr);
	img_load_safe(folderpath + "vert_upend.png", &vert_upend_spr);
}
