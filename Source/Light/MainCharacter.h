

#pragma once

#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

/**
 *
 */
UCLASS()
class LIGHT_API AMainCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

		/** First person camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		TSubobjectPtr<class UCameraComponent> FirstPersonCameraComponent;

	/** Base turn rate */
	float BaseTurnRate;

	/** Base look up/down rate */
	float BaseLookUpRate;

	/** Use behavior radius*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		TSubobjectPtr<class USphereComponent> CollectionSphere;

	/** Character CurrentHunger level */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		float CurrentHunger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		float MaxHunger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		float CurrentStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		float MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		float timer;

	virtual void Tick(float DeltaSeconds) override;

	/** Speed multiplier*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		float SpeedFactor;

	/** Baseline speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		float BaseSpeed;

	/** Baseline speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		bool bIsRunning;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		bool bSprintCoolDown;

	/** Use behavior handler*/
	UFUNCTION(BluePrintCallable, Category = Character)
		void Use();

	/** Called by food */
	UFUNCTION(BlueprintImplementableEvent, Category = Character)
		void Eat(float FoodQuality);

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles moving right/left */
	void MoveRight(float Val);

	/** Handles turning */
	void TurnAtRate(float Rate);

	/** Handles looing up/down */
	void LookUpAtRate(float Rate);

	void OnRun();

	void EndRun();

	void OnSprintCooldown();

	void EndSprintCooldown();

	//APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
