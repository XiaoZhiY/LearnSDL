#include "LTexture.h"


LTexture::LTexture()
{
	//Initialize
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer *gRenderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture *newTexture = NULL;

	//Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Erroe: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_Texture = newTexture;
	return m_Texture != NULL;
}


bool LTexture::loadFromRenderedText(std::string textureText,TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		m_Texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (m_Texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_Width = textSurface->w;
			m_Height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttF Error: %s\n", TTF_GetError());
	}

	//Return success
	return m_Texture != NULL;
}


void LTexture::free()
{
	if (m_Texture != NULL)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void LTexture::setColor(uint8 red, uint8 green, uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(m_Texture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(m_Texture, blending);
}

void LTexture::setAlpha(uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void LTexture::render(SDL_Renderer *gRenderer,int x, int y, SDL_Rect * clip, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
	//Set renderint space and render to screen
	SDL_Rect renderQuad = { x,y,m_Width,m_Height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, m_Texture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return m_Width;
}

int LTexture::getHeight()
{
	return m_Height;
}
