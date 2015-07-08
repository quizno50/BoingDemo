#ifndef SPRITE__H
#define SPRITE__H
#include "SDL.h"
#include "SDL_image.h"

struct sprite
{
   SDL_Surface *images[255];
   int maxImages;
   int currentImage;
   SDL_Rect location;
};

extern void drawSprite(struct sprite *thisSprite, SDL_Surface *dest);
extern void loadImage(struct sprite *thisSprite, char *path, 
               unsigned int imageNumber);
extern void initSprite(struct sprite *thisSprite);

#endif
