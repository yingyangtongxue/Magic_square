
# Magic Square with GTK+3.0 in C

This application consists of showing the user the magic matrix (magic square) from 2 to 10. For this, the user must click on the buttons and the result will be displayed in the right side.
## Installing GTK 3.0 on Linux
Run the following command to install the GTK 3.0 library:
```sh
$ sudo apt-get install libgtk-3-dev
```
If the GCC compiler is not installed, run the following command to install it:
```sh
$ sudo apt-get install gcc
```
## Compilation 
To compile the gui_c.c file and generate the gui_c executable, simply run the command in the Linux terminal:
```sh
$ gcc `pkg-config --cflags gtk+-3.0` -o gui_c gui_c.c `pkg-config --libs gtk+-3.0`
```
## Executation
To execute the executable file it is necessary to use the following command:
```sh
$ ./gui
```
