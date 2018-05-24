# SCGB
SCGB is a game engine in c++ using curses.

## What can SCGB do?
SCGB can display ASCII arts,images on a terminal window.
Internally,SCGB handles curses WINDOWs as layers,
so you do not need to worry about overlappings of WINDOWs.

## Prerequisites
In Linux,you need to install ncurses with `--enable-widec`.

## Test Programs
First,`make` this program,then you should see an executable
named `scgb`.This is a test program for SCGB,and shows
some fundamental functionarities.

## What does SCGB mean?
SCGB stands for "Simple (n)Curses Game Base".
As a recursive abbreviation,SCGB stands for
"SCGB Can be Good and Bad". Who knows.

## OS supports
For now,this program is tested only on Linux(Debian).No Windows
support yet.I'll make pdcurses version in near future.
