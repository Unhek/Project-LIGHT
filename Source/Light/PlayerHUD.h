// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class LIGHT_API APlayerHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	private:
	//crosshair pointer
	UTexture2D* CrosshairTex;
	
	virtual void DrawHUD() override;

};
