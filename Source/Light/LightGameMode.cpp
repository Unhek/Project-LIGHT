

#include "Light.h"
#include "LightGameMode.h"


ALightGameMode::ALightGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/MainCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}


