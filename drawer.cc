#include "drawer.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

SDL_Window* gwin = NULL;
SDL_Renderer* grend = NULL;

void update()
{
	SDL_RenderPresent( grend );
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gwin = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gwin == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			grend = SDL_CreateRenderer( gwin, -1, SDL_RENDERER_ACCELERATED );
			if( grend == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( grend, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( grend );
	SDL_DestroyWindow( gwin );
	gwin = NULL;
	grend = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( grend, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void hang()
{
  bool quit = false;
  SDL_Event e;
  while(!quit)
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
	}
}

void drawPixel(int x, int y, Pixel p)
{
  SDL_SetRenderDrawColor(grend, p.r, p.g, p.b, 0xFF);
  SDL_RenderDrawPoint(grend, x, y);
}

int evenness(int n)
{
  int c = 0;
  while(n % 2 != 0)
  {
    c++;
    n >>= 1;
  }
  return c;
}

void draw(int X, int Y, SDL_Surface *surf)
{
  uint32_t R, G, B;
  R = surf->format->Rmask;
  G = surf->format->Gmask;
  B = surf->format->Bmask;

  int Rz, Gz, Bz;
  Rz = evenness(R);
  Gz = evenness(G);
  Bz = evenness(B);
  
  int b = surf->format->BytesPerPixel;
  int pitch = surf->pitch;
  
  uint32_t pix;
  Pixel p;
  for(int x = 0; x < surf->w; x++)
  {
    for(int y = 0; y < surf->h; y++)
    {
      memcpy(&pix, (char*) surf->pixels + x*pitch + y*b, b);
      p.r = pix << Rz;
      p.g = pix << Gz;
      p.b = pix << Bz;
      drawPixel(X+x, Y+y, p);
    }
  }
}

// https://discourse.libsdl.org/t/sdl2-get-the-texture-width-and-height/27053/2
SDL_Point getsize(SDL_Texture *texture)
{
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}

SDL_FPoint point2fp(Point2D p)
{
  return {(float) p.x, (float)p.y};
}

void fillPolygon(std::vector<Point2D> verts, SDL_Color col)
{
  if(verts.size() <= 2)
  {
    std::cerr << "polygon needs at least 3 vertices\n";
    return;
  }

  Point2D u = verts[0];
  for(unsigned long i = 1; i < verts.size()-1; i++)
  {
    Point2D v = verts[i];
    Point2D w = verts[i+1];
    SDL_Vertex tri[3] =
    {
      {point2fp(u), col, SDL_FPoint{0}},
      {point2fp(v), col, SDL_FPoint{0}},
      {point2fp(w), col, SDL_FPoint{0}},
    };
    SDL_RenderGeometry(grend, nullptr, tri, 3, nullptr, 0);
  }
}
