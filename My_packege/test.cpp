#include "Engine.h"

int main( int argc, char* args[] )
{
	Engine myEngine;
	myEngine.init();
	myEngine.run();
	myEngine.close();
	return 0;
}