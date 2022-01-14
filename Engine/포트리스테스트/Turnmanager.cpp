#include "stdafx.h"
#include "Turnmanager.h"

Turnmanager::Turnmanager():rand(Random(0,PLAYERS-1,PLAYERS))
{
}

Turnmanager::~Turnmanager()
{
	rand.~Random();
}
