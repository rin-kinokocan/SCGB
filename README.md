# SCGB
SCGB is a game engine in c++ using curses.

## What can SCGB do?
SCGB can display ASCII arts, images in a terminal window.
Internally, SCGB consists of layer structures,
and you do not need to worry about overlapping problems
often found in programming using curses.

SCGB also has a little built in input functions based on curses getch.

## Prerequisites
On Linux, you need to install ncurses with `--enable-widec`.

## Build
On Linux,if you run `make` on the project root directory,
`make` will put all object files into `build` directory.

Cmake support is still in progress.

## Test Programs
First,`make` this program,then you should see an executable
named `scgb`.This is a test program for SCGB,and shows
some fundamental functionalities.

## What does SCGB mean?
SCGB stands for "Simple (n)Curses Game Base".
As a recursive abbreviation,SCGB stands for
"SCGB Can be Good and Bad". Who knows.

## OS supports
For now,this program is tested only on Linux(Debian).
I'm going to make pdcurses version in near future.
