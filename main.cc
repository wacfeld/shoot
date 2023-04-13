#include <iostream>
#include <stdlib.h>

#include "drawer.h"

int main()
{
	////Clear screen
	//SDL_SetRenderDrawColor( grend, 0xFF, 0xFF, 0xFF, 0xFF );
	//SDL_RenderClear( grend );

	////Render red filled quad
	//SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	//SDL_SetRenderDrawColor( grend, 0xFF, 0x00, 0x00, 0xFF );		
	//SDL_RenderFillRect( grend, &fillRect );

	////Render green outlined quad
	//SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	//SDL_SetRenderDrawColor( grend, 0x00, 0xFF, 0x00, 0xFF );		
	//SDL_RenderDrawRect( grend, &outlineRect );

	////Draw blue horizontal line
	//SDL_SetRenderDrawColor( grend, 0x00, 0x00, 0xFF, 0xFF );		
	//SDL_RenderDrawLine( grend, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

	////Draw vertical line of yellow dots
	//SDL_SetRenderDrawColor( grend, 0xFF, 0xFF, 0x00, 0xFF );
	//for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
	//{
	//	SDL_RenderDrawPoint( grend, SCREEN_WIDTH / 2, i );
	//}

	////Update screen
	//SDL_RenderPresent( grend );

  init();

  int x=300,y=300;
  unsigned char r, g, b;
  for(int i = 0; i < 200; i++)
  {
    r = rand();
    g = rand();
    b = rand();
    SDL_SetRenderDrawColor(grend, r, g, b, 0xFF);
    for(int j = 0; j < 200; j++)
    {
      SDL_RenderDrawPoint(grend, x+j, y+i);
    }
  update();
  getchar();
  }

  hang();
  close();
}
