

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

/**
 *
 */
UCLASS()
class LIGHT_API APickup : public AActor
{
	GENERATED_UCLASS_BODY()
		
	/** True when pickup is ready for pickup*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	bool bIsActive;

	/** Simple collision to use as root*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	/** StaticMeshComponent to represent the pickup*/ 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<UStaticMeshComponent> PickupMesh;

	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();

	
};
