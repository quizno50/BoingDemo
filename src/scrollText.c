#include "scrollText.h"

extern SCROLLTEXT* newScroll(char *text)
{
   SCROLLTEXT *newScroll;
   SDL_Surface *screen;
   int i=0;
   
   newScroll = malloc(sizeof(SCROLLTEXT));
   
   screen = SDL_GetVideoSurface();
   
   if (!TTF_WasInit())
   {
      if (TTF_Init()==-1)
      {
         fprintf(stderr, "No text for you...\n");
         return NULL;
      }
   }
   
   newScroll->font = TTF_OpenFont("scrollFont.ttf", 25);
   
   newScroll->background = SDL_CreateRGBSurface(
      SDL_HWSURFACE|SDL_SRCALPHA,
      screen->w,
      TTF_FontHeight(newScroll->font) + 2,
      32, screen->format->Rmask,
      screen->format->Gmask,
      screen->format->Bmask,
      screen->format->Amask);
      
   newScroll->screenLocal.x = 0;
   newScroll->screenLocal.y = 0;
   newScroll->screenLocal.w = screen->w;
   newScroll->screenLocal.h = 1;
   
   for (i = 50; i <= 200; i += (150 / newScroll->background->h))
   {
      SDL_FillRect(newScroll->background, &newScroll->screenLocal,
         SDL_MapRGBA(screen->format, 0, i, 0, i));
      ++newScroll->screenLocal.y;
   }
   
   newScroll->textClip.x = 0;
   newScroll->textClip.y = 0;
   newScroll->textClip.w = screen->w;
   newScroll->textClip.h = newScroll->background->h;
   
   newScroll->text = text;
   
   newScroll->textColor.r = 255;
   newScroll->textColor.g = 255;
   newScroll->textColor.b = 255;
   
   newScroll->renderedText = TTF_RenderText_Blended(
      newScroll->font,
      newScroll->text,
      newScroll->textColor);
      
   return newScroll;
}

void freeScroll(SCROLLTEXT *scroll)
{
   SDL_FreeSurface(scroll->background);
   scroll->background = NULL;
   SDL_FreeSurface(scroll->renderedText);
   scroll->renderedText = NULL;
   TTF_CloseFont(scroll->font);
   scroll->font = NULL;
   scroll->text = NULL;
   free(scroll);
}

void updateScroll(SCROLLTEXT *scroll)
{
   SDL_Surface *screen;
   
   screen = SDL_GetVideoSurface();
   
   scroll->textClip.x += 4;
   scroll->screenLocal.y = (screen->h / 2 - scroll->background->h) + 
            -abs(screen->h / 2 * 
            cos((double)(SDL_GetTicks()+250) / 1000.0)) + screen->h/2;
   if (scroll->textClip.x > scroll->renderedText->w)
   {
      scroll->textClip.x = -scroll->background->w;
   }
}

void drawScroll(SDL_Surface *target, SCROLLTEXT *scroll)
{
   SDL_Surface *composite;
   composite = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA,
      scroll->background->w,
      scroll->background->h,
      32,
      target->format->Rmask,
      target->format->Gmask,
      target->format->Bmask,
      target->format->Amask);
   
   SDL_BlitSurface(scroll->background, NULL, composite, NULL);
   SDL_BlitSurface(scroll->renderedText, &scroll->textClip, composite, NULL);
   SDL_BlitSurface(composite, NULL, target, &scroll->screenLocal);
   
   SDL_FreeSurface(composite);
}