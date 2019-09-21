#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "Graphics/LWindows.h"
#include "Graphics/LTexture.h"

//Starts up SDL and creates window
bool init();

bool loadMedia();

//Frees media and shuts down SDL
void close();

//Our custom window
LWindow gWindow;

LTexture gFooTexture;

//The window renderer
SDL_Renderer* gRenderer = NULL;


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle window events
					gWindow.handleEvent( e );
				}

				//Only draw when not minimized
				if( !gWindow.isMinimized() )
				{
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );
					
					//Render stick figure
					gFooTexture.render(gRenderer, ( DEFAULT_SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( DEFAULT_SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

					//Update screen
					SDL_RenderPresent( gRenderer );
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
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
		if( !gWindow.init() )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gWindow.createRenderer();
            gRenderer = gWindow.getRenderer();
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

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

	//Load foo' texture
	if( !gFooTexture.loadFromFile( "../Texture/foo.png" , gRenderer) )
	{
		printf( "Failed to load corner texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Destroy window
	gWindow.free();
	gFooTexture.free();

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}