# SCGB
SCGB is an object-oriented wrapper of curses for creating games.

## What can SCGB do?
SCGB provides some object-oriented API to manage text-based interface.
Currently, the main feature is `BaseWindow`, a refined version of
curses `WINDOW`. `BaseWindow` can write text in a rectangle shape like
`WINDOW` does, but also can be moved outside of the screen.
It adds enhanced visual effects for games.

SCGB also has built-in input functions based on curses getch.

## Prerequisites
On Unix-like OS (Linux or Mac), you have two library options:
+ use ncurses (run on a terminal)
+ use PDCurses (can be run without a terminal)

On Windows, the former option is not available unless you are
using MinGW or Cygwin or something like that.

If you want a ncurses version, you need `ncursesw` to build SCGB.
If you want a PDCurses version, create a directory called `lib`
first. Then you need to put PDCurses static library
and PDCurses header (`curses.h`) in the `lib` directory.

## Build
You can use CMake to build SCGB.
Make a directory called `build` on the project root directory,
then inside of the `build` directory, run `cmake ..` .

On Linux, the commands will look like this:
```
mkdir build
cd build
cmake ..
make
```
These commands create a static library of SCGB and a demo program
inside of `build` directory. CMake automatically copies the demo
executable to the project root directory. Run the copied
one because the demo uses files inside of `assets` using relative paths.

## Test Programs
The test program shows some fundamental functionalities of SCGB.

## What does SCGB mean?
SCGB stands for "Simple Curses Game Base."
As a recursive abbreviation, SCGB stands for
"SCGB Can be Good and Bad."  No one knows.

## OS supports
For now, I tested  SCGB on gnome-terminals, xterm, and
terminator running on Debian 9(stretch) using ncurses.
I also tested PDCurses (XCurses) to build SCGB, and it worked fine.
However, there might be bugs caused by the difference between
the libraries, especially on platform-specific features.

