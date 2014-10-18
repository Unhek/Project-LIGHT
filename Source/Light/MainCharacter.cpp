

#include "Light.h"
#include "MainCharacter.h"
#include "Food.h"

AMainCharacter::AMainCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;


	bIsRunning = false;
	MaxHunger = 500.f;
	MaxStamina = 100.f;

	timer = 5;

	// Create a CameraComponent	
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera

	//CurrentHunger variables
	CurrentHunger = MaxHunger;

	//Stamina Variables
	CurrentStamina = MaxStamina;

	SpeedFactor = 0.5f;
	BaseSpeed = 1.f;

	//create collection sphere
	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	InputComponent->BindAction("Use", IE_Pressed, this, &AMainCharacter::Use);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::OnRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::EndRun);

	InputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	InputComponent->BindAxis("TurnAtRate", this, &AMainCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUpAtRate", this, &AMainCharacter::LookUpAtRate);

}

/*For Sprinting*/
void AMainCharacter::OnRun()
{
	bIsRunning = true;
	
}

void AMainCharacter::EndRun()
{
	bIsRunning = false;

}


void AMainCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMainCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::Use()
{
	float FoodQuality = 0;

	//Get all overlapping actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	//for each actor collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		//Cast actor to AFood
		AFood* const TestFood = Cast<AFood>(CollectedActors[iCollected]);

		//if cast is succes and food is active
		if (TestFood && !TestFood->IsPendingKill() && TestFood->bIsActive)
		{
			FoodQuality = FoodQuality + TestFood->FoodQuality;
			TestFood->OnPickedUp();
			TestFood->bIsActive = false;
		}

		//Collect item


	}

	if (FoodQuality > 0.f)
	{
		//Eat(FoodQuality);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, "yumyum");
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::SanitizeFloat(FoodQuality));
		CurrentHunger += FoodQuality;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::SanitizeFloat(CurrentHunger));

	}


}

/* These 2 functions effect sprinting and stamina */
void AMainCharacter::OnSprintCooldown(){
	bSprintCoolDown = true;
	CharacterMovement->MaxWalkSpeed = 100;
	this->GetWorldTimerManager().SetTimer(this, &AMainCharacter::EndSprintCooldown, 3.0f, false);
}

void AMainCharacter::EndSprintCooldown(){
	bSprintCoolDown = false;
	CharacterMovement->MaxWalkSpeed = 600;
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//CharacterMovement->MaxWalkSpeed = SpeedFactor * CurrentHunger + BaseSpeed;
	CurrentHunger -= 1 * GetWorld()->GetDeltaSeconds();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::SanitizeFloat(CurrentHunger));


	// If cooldown is active regen stamina for the duration
	if (bSprintCoolDown == true)
	{
		CurrentStamina += 10 * GetWorld()->GetDeltaSeconds();
	}

	//You can only run while pressing shift and if cooldown isnt active
	if (bIsRunning == true && bSprintCoolDown == false)
	{

		if (CurrentStamina > 0 )
		{
			CharacterMovement->MaxWalkSpeed = 1200;
			CurrentStamina -= 10 * GetWorld()->GetDeltaSeconds();

		}

		if (CurrentStamina <= 0)
		{
			OnSprintCooldown();
		}

	}

	//Regen Stamina if not holding shift
	if (bIsRunning == false)
	{
		if (bSprintCoolDown == false)
		{
			if (bSprintCoolDown == false)
			{
				CharacterMovement->MaxWalkSpeed = 600;
			}

			if (CurrentStamina < MaxStamina && bSprintCoolDown == false)
			{
				CurrentStamina += 10 * GetWorld()->GetDeltaSeconds();

				if (CurrentStamina > MaxStamina)
				{

					CurrentStamina = MaxStamina;
				}
			}
		}
	}
}