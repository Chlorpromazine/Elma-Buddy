#include "Stats.h"


Stats Stats::stats;

void Stats::initPatch()
{
	//Called when wheel/head touches apple
	JumpPatch((BYTE*)0x0041FD62, (BYTE*)&touchApple, 0);

}

int Stats::getLevApplesTotal()
{
	return *(int*)ApplesTotal;
}

int Stats::getLevAppleCollected()
{
	return *(int*)ApplesCollected;
}

