/*  Copyright 2016 Theo Berkau

    This file is part of MPGROMDUMP.

    MPGROMDUMP is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    MPGROMDUMP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MPGROMDUMP; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*  Initiate mpeg/vcd rom dump, then try communicating  */
/*  with the commlink program                           */

#include    <iapetus.h>

int main()
{
   int ret;
   screen_settings_struct settings;
   font_struct main_font;
   
   init_iapetus(RES_320x224);

   // Setup a screen for us draw on
   settings.is_bitmap = TRUE;
   settings.bitmap_size = BG_BITMAP512x256;
   settings.transparent_bit = 0;
   settings.color = BG_256COLOR;
   settings.special_priority = 0;
   settings.special_color_calc = 0;
   settings.extra_palette_num = 0;
   settings.map_offset = 0;
   settings.rotation_mode = 0;
   settings.parameter_addr = 0x25E60000;
   vdp_rbg0_init(&settings);

   // Use the default palette
   vdp_set_default_palette();

   // Setup the default 8x8 1BPP font
   main_font.data = font_8x8;
   main_font.width = 8;
   main_font.height = 8;
   main_font.bpp = 1;
	main_font.transparent = 0;
   main_font.out = (u8 *)0x25E00000;
   vdp_set_font(SCREEN_RBG0, &main_font, 1);

   // Display everything
   vdp_disp_on();

   vdp_printf(&main_font, 8, 8, 0xF, "MPGROMDUMP v" MPGROMDUMP_VERSION);

   for (;;)
   {
		if ((ret = bios_is_mpeg_card_present(0)) < 0)
		{
			vdp_printf(&main_font, 8, 4 * 8, 0xF, "bios_is_mpeg_card_present < 0(%d).", ret);
			vdp_printf(&main_font, 8, 5 * 8, 0xF, "Press any button to retry.");
			for (;;)
			{
				vdp_vsync();
				if (per[0].but_push_once)
					break;
			}      
		}

		if ((ret = bios_get_mpeg_rom(246, 128, 0x00200000)) < 0)
      {
         vdp_printf(&main_font, 8, 4 * 8, 0xF, "bios_get_mpeg_rom < 0(%d).", ret);
         vdp_printf(&main_font, 8, 5 * 8, 0xF, "Press any button to retry.");
         for (;;)
         {
            vdp_vsync();
            if (per[0].but_push_once)
               break;
         }      
      }
      else
		{
			int bytes_read = ret;

			if ((ret = bios_get_mpeg_rom(246+128, 128, 0x00240000)) < 0)
			{
				vdp_printf(&main_font, 8, 4 * 8, 0xF, "bios_get_mpeg_rom < 0(%d).", ret);
				vdp_printf(&main_font, 8, 5 * 8, 0xF, "Press any button to retry.");
				for (;;)
				{
					vdp_vsync();
					if (per[0].but_push_once)
						break;
				}      
			}
			else
			{
				bytes_read += ret;
				vdp_printf(&main_font, 8, 6 * 8, 0xF, "bytes read = %d", bytes_read);
				break;
			}
		}
   }

   vdp_printf(&main_font, 8, 8 * 8, 0xF, "COMPLETE!");
	vdp_printf(&main_font, 8, 9 * 8, 0xF, "You can retrieve data by");
	vdp_printf(&main_font, 8, 10 * 8, 0xF, "dumping 0x0020000-0x0027FFFF");

	commlink_stop_service();
	if (ud_detect() == IAPETUS_ERR_OK)
	{
		cl_set_service_func(ud_check);
		commlink_start_service();
	}
	else
		vdp_printf(&main_font, 8, 12 * 8, 0xF, "error detecting usbdev cart");

	for (;;) { vdp_vsync(); }
}
