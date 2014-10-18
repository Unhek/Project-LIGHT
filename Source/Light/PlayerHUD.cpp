// Fill out your copyright notice in the Description page of Project Settings.

#include "Light.h"
#include "PlayerHUD.h"


APlayerHUD::APlayerHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("Texture2D'/Game/Textures/Crosshair.Crosshair'"));
	CrosshairTex = CrosshairTexObj.Object;

}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();

	//find center
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	//align texture 
	const FVector2D CrossHairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() *0.5f)), (Center.Y - (CrosshairTex->GetSurfaceHeight() *0.5f)));

	//draw crosshair
	FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
