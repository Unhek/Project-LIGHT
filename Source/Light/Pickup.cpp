

#include "Light.h"
#include "Pickup.h"


APickup::APickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
	//Active when created
	bIsActive = true;

	//Create the root SphereComponent to handle the collision
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSpehereComponent"));

	//Set SphereComponent as root
	RootComponent = BaseCollisionComponent;

	//Create StaticMesh component
	PickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));

	//Add physics to the static mesh
	PickupMesh->SetSimulatePhysics(true);

	//Attach static mesh to root
	PickupMesh->AttachTo(RootComponent);
	
}

void APickup::OnPickedUp_Implementation()
{
	//There is no default behavior when picked up.
}
