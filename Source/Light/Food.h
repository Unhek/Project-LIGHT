

#pragma once

#include "Pickup.h"
#include "Food.generated.h"

/**
 * 
 */
UCLASS()
class LIGHT_API AFood : public APickup
{
	GENERATED_UCLASS_BODY()

	/** Set the quality of the food*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Food)
	float FoodQuality;

	/** Implement the onPickedIp Function  _Implementation due to blueprint*/
	void OnPickedUp_Implementation() override;

	
};
