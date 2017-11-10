# Colorful Fractal Binary Tree
Tried my luck on generating a colorful fractal binary tree.

# Screenshot
![Screenshot of the program](/Screenshot.png?raw=true "Screenshot")

# How to Compile
## Pre-requisites:
* Any C++ compiler. g++ is recommended.
* Make (if you are on linux to automate compile and run)
* SDL2.0 Development Libraries
* A brain

## On Windows (MinGW and g++):
1. Go to libSDL2.0 download page: [here](http://libsdl.org/download-2.0.php "libSDL2.0 Download Page")
2. Under Development Libraries -> Windows, download the tar archive for MinGW.
3. Now, copy and paste the **appropriate** files from the archive in your MinGW directory (usually C:\\MinGW\\).

   For **32-bit** installation of MinGW, copy the contents of *"i686-w64-mingw32"* folder in archive and paste in C:\\MinGW\\.  
   For **64-bit** installation of MinGW, copy the contents of *"x86_64-w64-mingw32"* folder in archive and paste in C:\\MinGW\\.  

4. Open command prompt anywhere on your computer where you wish to keep the source files and run the following commands:
```terminal
git clone https://www.github.com/saubanbinusman/fractalTree.git
cd fractalTree\src\
g++ main.cpp -Ofast -lmingw32 -lSDL2main -lSDL2 -o program.exe
```
5. You are done with the compilation. To run the program, type the following command while command prompt is in the same directory:
```terminal
program
```

## On Linux:
1. First, you need to install libSDL2.
   Example terminal command for Ubuntu/Debian:
```terminal
sudo apt install libsdl2-2.0 libsdl2-dev
```
   Example terminal command for Arch:
```terminal
sudo pacman -S sdl2
```
2. Now open your terminal and navigate to the directory where you wish to keep the source files and run the following commands:
```terminal
git clone https://www.github.com/saubanbinusman/fractalTree.git
cd fractalTree/src/
```
3. a) To compile, you can use the make file by typing the following command in the same directory:
```terminal
make all
```
   b) Or, you can use the g++ compiler yourself for greater control over compilation flags and options:
```terminal
g++ main.cpp -Ofast -lSDL2 -o program.out && ./a.out
```

# User Guide
Run the program and you will be shown a randomly generated fractal binary tree.

Use the following keys to interact with the program:

| Key        | Effect                |
|:----------:|:---------------------:|
| ESC        | Quits                 |
| Space      | Generates a new tree  |

# Extras
You can uncomment any one of the two commented lines in the generateTree() function to have an animated rendering feel.

For a more reliable and consistent animated feel, you can use SDL_Delay(x), where x is an integer denoting the number of milliseconds to delay the processing.
