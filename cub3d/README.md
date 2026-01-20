*This project has been created as part of the 42 curriculum by bde-luce and frteixei.*

# Cub3d

## Description

Cub3D is a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective, inspired by the classic game Wolfenstein. The goal of this project is to implement a simple raycasting engine using Minilibx.

## Instructions

Clone the repository and compile the project using **make**, to clean object files use **make clean**, to fully clean the project use **make fclean**, to recompile from scratch use **make re**.
To run the program use **./cub3D map.cub**.

*Map Elements*

1 - Wall
0 - Empty Space
N/S/E/W - Player starting position and orientation
Valid maps must be closed/surrounded by walls

*Graphics*

Textured walls (North, South, East, West)
Different wall textures based on orientation
Floor and ceiling colors
Wall collisions

*Controls*

W/A/S/D - Movement
←/→ - Camera rotation
ESC - Exit the program

## Resources