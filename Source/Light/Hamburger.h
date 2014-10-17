

#pragma once

#include "Pickup.h"
#include "Hamburger.generated.h"

/**
 * 
 */
UCLASS()
class LIGHT_API AHamburger : public APickup
{
	GENERATED_UCLASS_BODY()

	//Active on touch
	virtual void ReceiveActorBeginOverlap(class AActor* Other) override;

	//handes touch
	void PickupOnTouch(class AMainCharacter* Pawn);

	
};
