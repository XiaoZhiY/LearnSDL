#ifndef __LTEXTURE_H__
#define __LTEXTURE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include "../Defines.h"

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

	
	//Create image from font string
	bool loadFromRenderedText(std::string textureText, TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(uint8 red, uint8 green, uint8 blue);

	//Set color modulation
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(uint8 alpha);

	//Renders texture at given point
	void render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture *m_Texture;

	//Image dimensions
	int m_Width;
	int m_Height;
};


#endif