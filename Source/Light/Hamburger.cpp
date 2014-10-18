

#include "Light.h"
#include "Hamburger.h"
#include "MainCharacter.h"


AHamburger::AHamburger(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AHamburger::ReceiveActorBeginOverlap(class AActor* Other)
{
	Super::ReceiveActorBeginOverlap(Other);
	PickupOnTouch(Cast<AMainCharacter>(Other));
}

void AHamburger::PickupOnTouch(class AMainCharacter* Pawn)
{
	if(Pawn)
	{
		Pawn->Hunger = 1000;
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Picked up"));
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Picked up"));
	
}