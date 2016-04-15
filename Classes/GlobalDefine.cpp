#include "GlobalDefine.h"

void PLAYEFFECTADV(const char* soundFullName)
{
	char szTemp[256];
	memset(szTemp, 0, 256);
	sprintf(szTemp, "Sound/%s", soundFullName);

	if (getBoolFromXML(SOUND_KEY)) \
	{\
		audioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));\
		audioEngine->playEffect(szTemp);\
	}
}