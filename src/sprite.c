#include "sprite.h"

void loadImage(struct sprite *thisSprite, char *path, 
               unsigned int imageNumber)
{
   thisSprite->images[imageNumber] = IMG_Load(path);
   if (thisSprite->images[imageNumber] == NULL)
   {
      fprintf(stderr, "loadImage() - could not load image... %s\n", 
         IMG_GetError());
      return;
   }
   
   if ((int)imageNumber > thisSprite->maxImages)
   {
      thisSprite->maxImages = imageNumber;
   }
   
   thisSprite->location.w = thisSprite->images[imageNumber]->w;
   thisSprite->location.h = thisSprite->images[imageNumber]->h;
}

void initSprite(struct sprite *thisSprite)
{
   thisSprite->maxImages = -1; //negative one is uninitilized
   thisSprite->currentImage = 0;
}

void drawSprite(struct sprite *thisSprite, SDL_Surface *dest)
{
   SDL_BlitSurface(thisSprite->images[thisSprite->currentImage], NULL,
      dest, &thisSprite->location);
   ++thisSprite->currentImage;
   if (thisSprite->currentImage > thisSprite->maxImages)
   {
      thisSprite->currentImage = 0;
   }
}
