#include "LWindows.h"


//Intializes internals
LWindow::LWindow()
{
	//Initialize non-existant window
	m_Window = NULL;
    m_Renderer = NULL;
    //Default window name
    m_WindowName = "SDL Tutorial";
	m_MouseFocus = false;
	m_KeyboardFocus = false;
	m_FullScreen = false;
	m_Minimized = false;
	m_Width = 0;
	m_Height = 0;
}

LWindow::~LWindow()
{
	//Deallocate
	free();
}

//Creates default window
bool LWindow::init()
{
    //Create window
	m_Window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( m_Window != NULL )
	{
        m_WindowName = "SDL Tutorial";
		m_MouseFocus = true;
		m_KeyboardFocus = true;
		m_Width = DEFAULT_SCREEN_WIDTH;
		m_Height = DEFAULT_SCREEN_HEIGHT;
	}

	return m_Window != NULL;
}


bool LWindow::init(std::string title, int x, int y, 
                                      int w, int h,
                                      uint32 flag)
{
    //Create window
	m_Window = SDL_CreateWindow( title.c_str(), x, y, w, h, flag );
	if( m_Window != NULL )
	{
        m_WindowName = title;
		m_MouseFocus = true;
		m_KeyboardFocus = true;
		m_Width = w;
		m_Height = h;
	}

	return m_Window != NULL;
}

//Creates renderer from internal window
bool LWindow::createRenderer()
{
    m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if(m_Renderer == NULL)
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    return true;
    
}

//Get copy of renderer
SDL_Renderer* LWindow::getRenderer()
{
    if(m_Renderer != NULL)
    {
        return m_Renderer;
    }
    else
    {
        printf("please create render first.");
        return NULL;
    }
}

//Handles window events
void LWindow::handleEvent( SDL_Event& e )
{
	//Window event occured
	if( e.type == SDL_WINDOWEVENT )
	{
		//Caption update flag
		bool updateCaption = false;

		switch( e.window.event )
		{
			//Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			m_Width = e.window.data1;
			m_Height = e.window.data2;
			SDL_RenderPresent( m_Renderer );
			break;

			//Repaint on exposure
			case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent( m_Renderer );
			break;

			//Mouse entered window
			case SDL_WINDOWEVENT_ENTER:
			m_MouseFocus = true;
			updateCaption = true;
			break;
			
			//Mouse left window
			case SDL_WINDOWEVENT_LEAVE:
			m_MouseFocus = false;
			updateCaption = true;
			break;

			//Window has keyboard focus
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			m_KeyboardFocus = true;
			updateCaption = true;
			break;

			//Window lost keyboard focus
			case SDL_WINDOWEVENT_FOCUS_LOST:
			m_KeyboardFocus = false;
			updateCaption = true;
			break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
            m_Minimized = true;
            break;

			//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
			m_Minimized = false;
            break;
			
			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
			m_Minimized = false;
            break;
		}

		//Update window caption with new data
		if( updateCaption )
		{
			std::stringstream caption;
			caption << m_WindowName << " - MouseFocus:" << ( ( m_MouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( m_KeyboardFocus ) ? "On" : "Off" );
			SDL_SetWindowTitle( m_Window, caption.str().c_str() );
		}
	}
	//Enter exit full screen on return key
	else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
	{
		if( m_FullScreen )
		{
			SDL_SetWindowFullscreen( m_Window, SDL_FALSE );
			m_FullScreen = false;
		}
		else
		{
			SDL_SetWindowFullscreen( m_Window, SDL_TRUE );
			m_FullScreen = true;
			m_Minimized = false;
		}
	}
}

//Deallocates internals
void LWindow::free()
{
    if( m_Renderer != NULL)
    {
        SDL_DestroyRenderer( m_Renderer );
    }

	if( m_Window != NULL )
	{
		SDL_DestroyWindow( m_Window );
	}

	m_MouseFocus = false;
	m_KeyboardFocus = false;
	m_Width = 0;
	m_Height = 0;
}

int LWindow::getWidth()
{
	return m_Width;
}

int LWindow::getHeight()
{
	return m_Height;
}

bool LWindow::hasMouseFocus()
{
	return m_MouseFocus;
}

bool LWindow::hasKeyboardFocus()
{
	return m_KeyboardFocus;
}

bool LWindow::isMinimized()
{
	return m_Minimized;
}