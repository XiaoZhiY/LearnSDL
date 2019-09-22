#include "Engine.h"

Engine::Engine()
{
    m_Renderer = NULL;
    m_quit = false;
}

Engine::~Engine()
{
    close();
}

bool Engine::init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
    }

    //Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}
    
    //Create window
	if( !m_Window.init() )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

    //Create and get renderer for window
	m_Window.createRenderer();
    m_Renderer = m_Window.getRenderer();

    if( m_Renderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

    //Initialize renderer color
	SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
	    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}


    // 载入资源 暂且放在这里
    loadMedia();

    return true;
}

// 释放所有资源
void Engine::free()
{
    //Destroy texture
    m_Texture.free();

    //Destroy window and renderer
	m_Window.free();
	
    m_Renderer = NULL;
}

// 供外部调用
void Engine::close()
{
    free();
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Engine::loadMedia()
{
    //Loading success flag
	bool success = true;

	//Load foo' texture
	if( !m_Texture.loadFromFile( "../Texture/foo.png" , m_Renderer) )
	{
		printf( "Failed to load corner texture!\n" );
		success = false;
	}

    return success;
}

void Engine::handleEvent(SDL_Event& e)
{
    //Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			m_quit = true;
		}
		//Handle window events
		m_Window.handleEvent( e );
	}
}

void Engine::update(float deltaTime)
{
    
}

void Engine::draw()
{
    //Only draw when not minimized
    if( !m_Window.isMinimized() )
	{
		//Clear screen
		SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( m_Renderer );
			
		//Render stick figure
		m_Texture.render(m_Renderer, ( DEFAULT_SCREEN_WIDTH - m_Texture.getWidth() ) / 2, ( DEFAULT_SCREEN_HEIGHT - m_Texture.getHeight() ) / 2 );
		//Update screen
		SDL_RenderPresent( m_Renderer );
	}
}

void Engine::run()
{
	//Event handler
	SDL_Event e;

	//Keeps track of time between steps
	//后续可以搞一个计时器管理类 负责处理异步时间通知
	LTimer stepTimer;
	LTimer totalTimer;
	totalTimer.start();

	//While application is running
	while( !m_quit )
	{
		//Handle events on queue
        handleEvent(e);

		//Calculate time step
		float timeStep = stepTimer.getTicks() / 1000.f;
		//std::cout << totalTimer.getTicks() / 1000.f << std::endl;

		//Restart step timer
		stepTimer.start();

		//update
        update(timeStep);

        draw();
			
	}
}