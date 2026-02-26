
Maps to fix
wrong_png




AI HELPED TO FIX LEAK IN GNL BECAUSE ON ERROR_EXIT GNL DOEESN'T GET TO FINISH.
Look at the very first variable inside your get_next_line function:
static char *txt;

When you use get_next_line to read the line with IA ./textures/wallE.png, it reads a big chunk of the file (based on BUFFER_SIZE) and stores the leftover text in that static variable.

When your parse_id function sees IA, it immediately triggers your error_exit. The program dies right there. But get_next_line never got to finish the file! That static variable txt is still holding onto the remaining 31 bytes of text.

(Note: This is exactly why Valgrind calls it "still reachable" instead of "definitely lost". The static pointer still knows where the memory is, but the program closed before it could free it).

The Fix: "Draining" GNL
You have two choices to fix this. You can either modify your Libft's get_next_line to accept a special command to clear itself, OR you can simply force it to finish reading the file inside your error_exit function.

The second option is much easier and keeps your Libft clean.

Before you close the fd in error_exit, you just need to loop get_next_line until it reaches the end of the file. Once it hits the end, your get_next_line logic will naturally call free(txt) and fix the leak!


-------------------------
The Raycaster's Reality
Visually, the corners of those two 1s are touching exactly at a single pixel. But in a 3D raycasting engine, rays are essentially infinitely thin mathematical lines.

If your player stands on that 0 and looks exactly South-East, the math of the ray will slide perfectly between the mathematical corners of those two 1s and shoot right out into the       (the void).
When a ray hits a space or goes out of bounds, your game will either crash with a Segmentation Fault, or it will draw corrupted garbage pixels on the screen because it doesn't know what texture the "void" is supposed to have!

Furthermore, depending on how you write your player collision later, your player might be able to physically squeeze through that crack and fall out of the map.

How the 8-way Floodfill fixes this:
If you add the diagonal checks to your floodfill, when it stands on that 0, it will check South-East.
It will immediately see the       (Space), realize the corners aren't properly sealed, trigger your return (0), and correctly declare the map INVALID.