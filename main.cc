#include <iostream>
#include <stdlib.h>
#include <chrono>

#include "drawer.h"
#include "linalg.h"
#include "camera.h"

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

  // init();

  // int x=300, y=300;
  
  // SDL_Texture *text = loadTexture("media/monalisa.jpg");
  // SDL_Rect dest = {100,100,300,300};
  // SDL_RenderCopy(grend, text, NULL, &dest);
  // update();
  
  // // SDL_Surface *surf = IMG_Load("media/monalisa.jpg");
  // // // printf("%x\n", surf->format->Bmask);
  
  // // using clock = std::chrono::system_clock;
  // // using sec = std::chrono::duration<double>;
// // // for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

  // // const auto before = clock::now();
  // // draw(0,0, surf);
  // // update();
  // // const sec duration = clock::now() - before;

  // // std::cout << "It took " << duration.count() << "s" << std::endl;

  // hang();
  // close();

  // Point p1 {1, 0, 1};
  // Point p2 {2, 0.5, 0.5};
  // Point p3 {0.5, 0.5, 0.5};
  // Plane pl = points2plane(p1, p2, p3);
  
  // Point D {2,2,3};
  // Point E {1,-1,0.5};
  // Line l = points2line(D, E);
  // std::cout << l << std::endl;

  // Point inter = intersect(pl, l);
  // std::cout << inter << std::endl;

  Orient o {0, 0, 0.2};
  Camera cam {{0, 0, 0}, o, (double)SCREEN_WIDTH/1000, (double)SCREEN_HEIGHT/1000, 5};
  // Rectangle r = cam.getRect();
  
  Point bl {30,0,-10};
  Vec h {0, 1.788, 0};
  Vec w {0, 0, 1.2};
  Rectangle wr {bl, bl+w, bl+h, bl+h+w};

  init();
  SDL_Texture *text = loadTexture("media/monalisa.jpg");
  // SDL_Point size = getsize(text);

  Wall wall {wr, text};

  Rectangle proj = project(wr, cam.plane, cam.p);
  proj = proj.unorient(o);
  
  cam.screenQuad(proj);

  close();
}
