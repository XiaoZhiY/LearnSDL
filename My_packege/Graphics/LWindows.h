#ifndef __LWINDOWS_H__
#define __LWINDOWS_H__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "../Defines.h"

class LWindow
{
public:
	//Intializes internals
	LWindow();

	~LWindow();
	
	//Creates default window
	bool init();

    /**
     *  \brief Create a window with the specified position, dimensions, and flags.
     *  \param title    The title of the window, in UTF-8 encoding.
     *  \param x        The x position of the window, ::SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED
     *  \param y        The y position of the window, ::SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED
     *  \param w        The width of the window, in screen coordinates.
     *  \param h        The height of the window, in screen coordinates.
     *  \param flags    The flags for the window, a mask of any of the following:
     *                  ::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
     *                  ::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
     *                  ::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
     *                  ::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
     *                  ::SDL_WINDOW_ALLOW_HIGHDPI, ::SDL_WINDOW_VULKAN.
     */
    bool init(std::string title, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, 
                                 int w = DEFAULT_SCREEN_WIDTH, int h = DEFAULT_SCREEN_HEIGHT,
                                 uint32 flag = (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));

	//Creates renderer from internal window
	bool createRenderer();

    //Get renderer from internal window
    SDL_Renderer* getRenderer();

	//Handles window events
	void handleEvent( SDL_Event& e );

	//Deallocates internals
	void free();

	//Window dimensions
	int getWidth();
	int getHeight();

	//Window focii
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();

private:
	//Window data
	SDL_Window* m_Window;
    
    //Window name
    std::string m_WindowName;

    //Renderer
    SDL_Renderer* m_Renderer;

	//Window dimensions
	int m_Width;
	int m_Height;

	//Window focus
	bool m_MouseFocus;
	bool m_KeyboardFocus;
	bool m_FullScreen;
	bool m_Minimized;

};

#endif