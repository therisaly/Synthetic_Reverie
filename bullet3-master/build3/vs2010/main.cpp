#include "Game.h"
#include "FreeGLUTCallbacks.h"

int main(int argc, char** argv)
{
	Game demo;
	return glutmain(argc, argv, "Intro", &demo);
}