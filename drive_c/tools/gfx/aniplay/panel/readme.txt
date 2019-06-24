It's possible to choose the panel of the main window (the player) 
and the Playlist, just copy an IMG file (GEM image) in the Aniplayer's
directory. There are some files in this folder.
The number of colors must be equal to the screen, so the name of the 
file contains the number of colors excepted in (near) true color.
It's possible to choose a different motif for each window, but the 
default name is PANELxxx.IMG (with xxx the number of colors). The name
for the main window is PPLAYxx.IMG and for the Playlist PLISTxxx.IMG.
For example if there are this files in the Aniplayer's directory:
 PANEL16.IMG
 PPLAY256.IMG
 PLIST256.IMG
 PANEL.IMG
 PPLAY.IMG
- PANEL16.IMG is used in 16 colors for the 2 windows.
- PPLAY256.IMG is used for the main window and PLIST256.IMG for the 
Playlist in 256 colors. Please set the 'Current palette' in the 
'Display configuration' box if your image uses the 16 GEM colors. 
- PPLAY.IMG is used for the main window and PANEL.IMG for the Playlist 
in 32K, 65K, or 16M colors.
It's not easy to found a program for create and see an IMG file in true 
color, there are a RIM/WIN with M&E system, used by programs like 
Picollo or Digital Lab. Another solution is to save a JPEG file into 
IMG file with Aniplayer... 