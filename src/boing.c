#include <stdio.h>
#include <math.h>
#include <string.h>

#include "sprite.h"
#include "mikmod.h"
#include "scrollText.h"

void loadBallImages(struct sprite *ball)
{
   initSprite(ball);
   loadImage(ball, "images/0001.png", 0);
   loadImage(ball, "images/0002.png", 1);
   loadImage(ball, "images/0003.png", 2);
   loadImage(ball, "images/0004.png", 3);
   loadImage(ball, "images/0005.png", 4);
   loadImage(ball, "images/0006.png", 5);
   loadImage(ball, "images/0007.png", 6);
   loadImage(ball, "images/0008.png", 7);
   loadImage(ball, "images/0009.png", 8);
}

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
   Uint32 *returnPixel;
   returnPixel = surface->pixels;
   returnPixel += (surface->w * y);
   returnPixel += x;
   return *returnPixel;
}

void putPixel(SDL_Surface *surface, int x, int y, SDL_Color c)
{
   Uint32 *returnPixel;
   returnPixel = surface->pixels;
   returnPixel += (surface->w * y);
   returnPixel += x;
   *returnPixel = SDL_MapRGBA(surface->format, c.r, c.g, c.b, c.unused);
}

void makeBlueBall(struct sprite *ball)
{
   int imageNumber = 0;
   int x = 0;
   int y = 0;
   Uint32 temp;
   SDL_Color theNewColor;
   
   for (imageNumber = 0; imageNumber <= ball->maxImages; ++imageNumber)
   {
      for (y = 0; y < ball->images[imageNumber]->h; ++y)
      {
         for (x = 0; x < ball->images[imageNumber]->w; ++x)
         {
            temp = getPixel(ball->images[imageNumber], x, y);
            theNewColor.unused = 
               (((temp & ball->images[imageNumber]->format->Amask) >>
               ball->images[imageNumber]->format->Ashift) <<
               ball->images[imageNumber]->format->Aloss);
            theNewColor.r = 
               (((temp & ball->images[imageNumber]->format->Rmask) >>
               ball->images[imageNumber]->format->Rshift) <<
               ball->images[imageNumber]->format->Rloss);
            theNewColor.g = 
               (((temp & ball->images[imageNumber]->format->Gmask) >>
               ball->images[imageNumber]->format->Gshift) <<
               ball->images[imageNumber]->format->Gloss);
            theNewColor.b = 
               (((temp & ball->images[imageNumber]->format->Bmask) >>
               ball->images[imageNumber]->format->Bshift) <<
               ball->images[imageNumber]->format->Bloss);
            theNewColor.r = theNewColor.r ^ theNewColor.b;
            theNewColor.b = theNewColor.r ^ theNewColor.b;
            theNewColor.r = theNewColor.r ^ theNewColor.b;
            putPixel(ball->images[imageNumber], x, y, theNewColor);
         }
      }
   }
}

SDL_Surface *makeBackground()
{
   SDL_Surface *screen;
   SDL_Surface *background;
   SDL_Rect lineToDraw;
   int i;
   
   screen = SDL_GetVideoSurface();
   background = SDL_CreateRGBSurface(SDL_HWSURFACE, screen->w, screen->h, 32, 
      screen->format->Rmask,
      screen->format->Gmask,
      screen->format->Bmask,
      screen->format->Amask);
   
   SDL_FillRect(background, NULL, 
      SDL_MapRGB(screen->format, 255/2, 255/2, 255/2));
   
   for (i = 0; i < screen->w; i += screen->w/25)
   {
      lineToDraw.x = 0;
      lineToDraw.w = screen->w;
      lineToDraw.y = i;
      lineToDraw.h = 1;
      SDL_FillRect(background, &lineToDraw, SDL_MapRGB(screen->format, 
         200, 200, 255));
   }
   for (i = 0; i < screen->w; i += screen->w/25)
   {
      lineToDraw.x = i;
      lineToDraw.w = 1;
      lineToDraw.y = 0;
      lineToDraw.h = screen->h;
      SDL_FillRect(background, &lineToDraw, SDL_MapRGB(screen->format, 
         200, 200, 255));
   }
   
   return background;
}

int main(int argc, char **argv)
{
   SDL_Surface *screen;
   SDL_Surface *background;
   Uint8 stillRunning = 1;
   SDL_Event theEvent;
   struct sprite ball;
   struct sprite ball2;
   SCROLLTEXT *theScroll;
   char scrollText[1024];
   long lastTicks;
   int xVel = 3;
   int xVel2 = 2;
   MODULE *music;
   
   SDL_Init(SDL_INIT_VIDEO);
   MikMod_RegisterAllDrivers();
   MikMod_RegisterAllLoaders();
   MikMod_Init("");
   md_mode |= DMODE_SOFT_MUSIC;
   music = Player_Load("bz_pif.it", 64, 0);
   if (music == NULL)
   {
      printf("startMusic() - could not load music...\n");
   }
   Player_Start(music);
   
   screen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF|SDL_HWSURFACE);
   background = makeBackground();
   loadBallImages(&ball);
   loadBallImages(&ball2);
   makeBlueBall(&ball2);
   lastTicks = SDL_GetTicks();
   
   scrollText[0] = '\0';
   strcat(scrollText, "Hello and welcome to Yet another Boing Demo, this time");
   strcat(scrollText, " using SDL and it's many OPEN SOURCE libraries!");
   strcat(scrollText, " I would like to thank everyone that has helped me on my");
   strcat(scrollText, " to make this crazy demo, everyone from my dad who first");
   strcat(scrollText, " introduced me to computers during my childhood to");
   strcat(scrollText, " me22 and Ryan Clark who on gpwiki.org have helped");
   strcat(scrollText, " extend my knowledge of computers and game programming");
   strcat(scrollText, " far beyond anything I could have hoped for.");
   strcat(scrollText, " Secondly I would like to thank the author of");
   strcat(scrollText, " www.retroleum.co.uk for inspiring me to take on this");
   strcat(scrollText, " challange. (Yeah, go ahead: laugh, not a challange");
   strcat(scrollText, " to you guys, but definitely took more than a few hours");
   strcat(scrollText, " sitting in front of a computer coding for me).......");
   strcat(scrollText, " I guess that's all for now... This is quizno50 signing");
   strcat(scrollText, " off....");
   
   theScroll = newScroll(scrollText);
   
   while (stillRunning)
   {
      while (SDL_PollEvent(&theEvent))
      {
         if (theEvent.type == SDL_QUIT)
         {
            stillRunning = 0;
         }
         else if (theEvent.type == SDL_KEYDOWN)
         {
            if (theEvent.key.keysym.sym == SDLK_ESCAPE)
            {
               stillRunning = 0;
            }
         }
      }
      
      MikMod_Update();
      
      if (SDL_GetTicks() > lastTicks + 20)
      {
         lastTicks = SDL_GetTicks();
         SDL_BlitSurface(background, NULL, screen, NULL);
         ball.location.y = -abs(screen->h / 2 * 
            cos((double)lastTicks / 500.0)) + screen->h/2;
         ball2.location.y = -abs(screen->h / 2 * 
            sin((double)lastTicks / 500.0)) + screen->h/2;
         updateScroll(theScroll);
            
         ball.location.x += xVel;
         ball2.location.x += xVel2;
         
         if (ball.location.x > screen->w - ball.location.w)
         {
            ball.location.x = screen->w - ball.location.w;
            xVel = -xVel;
         }
         
         if (ball.location.x < 0)
         {
            ball.location.x = 0;
            xVel = -xVel;
         }
         
         if (ball2.location.x > screen->w - ball2.location.w)
         {
            ball2.location.x = screen->w - ball2.location.w;
            xVel2 = -xVel2;
         }
         
         if (ball2.location.x < 0)
         {
            ball2.location.x = 0;
            xVel2 = -xVel2;
         }
         
         drawSprite(&ball, screen);
         drawScroll(screen, theScroll);
         drawSprite(&ball2, screen);

         
         SDL_Flip(screen);
      }
   }
   
   freeScroll(theScroll);
   Player_Free(music);
   MikMod_Exit();
   
   return 0;
}
