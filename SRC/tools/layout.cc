#include "layout.hh"

unsigned char KeyActions::AZERTY_fun(Action a)
{
	switch (a)
	{
		case FRONT: return 'z'; break;
		case BACK:	return 's'; break;
		case LEFT:	return 'q'; break;
		case RIGHT:	return 'd'; break;
		case UP:		return 'r'; break;
		case DOWN:	return 'f'; break;
	}
	return 0;
}

unsigned char KeyActions::QWERTY_fun(Action a)
{
	switch (a)
	{
		case FRONT: return 'w'; break;
		case BACK:	return 's'; break;
		case LEFT:	return 'a'; break;
		case RIGHT:	return 'd'; break;
		case UP:		return 'r'; break;
		case DOWN:	return 'f'; break;
	}
	return 0;
}
