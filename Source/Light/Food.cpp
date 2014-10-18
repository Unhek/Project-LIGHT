

#include "Light.h"
#include "Food.h"


AFood::AFood(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//the base level of food quality
	FoodQuality = 150.f;
}

void AFood::OnPickedUp_Implementation()
{
	//Call parent implementation
	Super::OnPickedUp_Implementation();

	//Destroy food
	//Destroy();
}

