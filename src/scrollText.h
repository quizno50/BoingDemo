#ifndef SCROLL_TEXT__H
#define SCROLL_TEXT__H

#include "SDL.h"
#include "SDL_ttf.h"
#include <math.h>

typedef struct
{
   SDL_Surface *background;
   SDL_Surface *renderedText;
   TTF_Font *font;
   SDL_Rect screenLocal;
   SDL_Rect textClip;
   SDL_Color textColor;
   char *text;
} SCROLLTEXT;

extern SCROLLTEXT* newScroll();
extern void freeScroll(SCROLLTEXT *scroll);
extern void updateScroll(SCROLLTEXT *scroll);
extern void drawScroll(SDL_Surface *target, SCROLLTEXT *scroll);

#endif