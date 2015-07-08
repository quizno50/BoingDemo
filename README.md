<h1>BoingDemo</h1>
<p>A recreation of the Amiga Boing demo in SDL 1.2</p>
<h2>Description</h2>
<p>A Boing Demo clone written in SDL 1.2 after I finished my first year at University. The goal for this project was to create something that used as many of the SDL features as possible. I still wasn't able to work in much input, but I managed to hit: fonts, audio, images, run-time image generation/manipulation, and animation. I'm kinda scared to look through this code again because I remember it being extremely frustrating to get working correctly.</p>
<h2>Compilation</h2>
<p>The directory structure matters in this one. You have to be in the project's root directory and make sure the executable is generated there.</p>
```
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libmikmod-dev build-essential
gcc -o ./boing src/boing.c src/scrollText.c src/sprite.c -Isrc -I/usr/include/SDL/ -lSDL -lSDL_ttf -lSDL_image -lmikmod -lm
```
