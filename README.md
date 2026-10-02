<img width="1408" height="768" alt="cub3d" src="https://github.com/user-attachments/assets/38070eb5-aded-4e2d-b816-b31726349326" />

*This project has been created as part of the 42 curriculum by msimek and ssukhija.*

# DESCRIPTION

cub3D is a dynamic, first-person 3D graphical representation of a maze built entirely in C using ray-casting principles. Inspired by the world-famous 1992 game Wolfenstein 3D, this project serves as a deep dive into the practical applications of mathematics, rendering a 3D perspective from a 2D map grid.

The program utilizes the MLX42 graphics library to manage window creation, pixel drawing, and event handling. It rigorously parses a custom scene description file (.cub) to load specific textures for North, South, East, and West facing walls, as well as distinct RGB colors for the floor and ceiling. Users can navigate the maze fluidly using the W, A, S, D keys for movement and the left/right arrows for camera rotation.


# INSTRUCTIONS


1) git clone...

2) cd CUB3D

3) To use the MLX42 library, copy/paste this:

        git submodule update --init --recursive
        cd MLX42
        cmake -B build
        cmake --build build
        cd ..
        make


## EXECUTION

    ./cub3D <path/map.cub>
    CandyLand:
    ./cub3D maps/candyland.cub
    Life Sentence:
    ./cub3D maps/life_sentence.cub
    Darkness:
    ./cub3D maps/darkness.cub


## CONTROLS
    ESC = Exit Game

    W = Move Forward
    S = Move Backward
    A = Strafe Left
    D = Strafe Right
    <- = Turn Left
    -> = Turn Right


## CONFIGURATION

To launch the game, a valid configuration file with a .cub extension must be provided as a 
command-line argument. This file defines the paths to the wall textures, the RGB color codes 
for the ceiling and floor, and the layout of the map itself.

The configuration file must adhere to the following format:

The map must be designate of only 6 possible characters: 0 representing empty space, 1 for a wall, 
and N,S,E or W for the player’s start position and spawning orientation.

The map must be closed/surrounded by walls, if not the program must return an error.

Except for the map content, each type of element can be separated by one or more empty lines.

Except for the map content which always has to be the last, each type of element can be set 
in any order in the file.

Except for the map, each type of information from an element can be separated by one or more spaces.

The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle. 
You must be able to parse any kind of map, as long as it respects the rules of the map.

Except for the map, each element must begin with its type identifier (composed by one or two characters), 
followed by its specific information in a strict order:

    NO => North texture
    SO => South texture
    WE => West texture
    EA => East texture
    F => Floor color
    C => Ceiling color


## CONFIGURATION EXAMPLE
    NO ./path_to_the_north_texture
    SO ./path_to_the_south_texture
    WE ./path_to_the_west_texture
    EA ./path_to_the_east_texture

    F 220,100,0
    C 225,30,0

            1111111111111111111111111
            1000000000110000000000001
            1011000001110000000000001
            1001000000000000000000001
    111111111011000001110000000000001
    100000000011000001110111111111111
    11110111111111011100000010001
    11110111111111011101010010001
    11000000110101011100000010001
    10000000000000001100000010001
    10000000000000001101010010001
    11000001110101011111011110N0111
    11110111 1110101 101111010001
    11111111 1111111 111111111111


# RESOURCES
AI Usage: LLMs were used to assist with conceptual understanding, mathematical principles.

## Websites:

* [Lodev's Raycasting Tutorial: The definitive classic guide for understanding the DDA algorithm required to calculate ray distances on a grid](https://lodev.org/cgtutor/raycasting.html)

* [Wolfenstein 3D Raycasting in C](https://timallanwheeler.com/blog/2023/04/01/wolfenstein-3d-raycasting-in-c/)

* [RayCasting @abdelhadi-salah](https://medium.com/@abdelhadi-salah/ray-casting-cub3d-bb5d99de742d)

* [Youtube - tutorial](https://www.youtube.com/watch?v=gYRrGTC7GtA&list=PLMTDxt7L_MNXx7QP80seZUfcSoJ4jl34D&index=5)
