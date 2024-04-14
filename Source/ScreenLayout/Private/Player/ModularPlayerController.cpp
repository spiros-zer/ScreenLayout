// Copyright 2024 Spyridon Zervos


#include "Player/ModularPlayerController.h"

#include "ScreenLayoutManagerSystem.h"

void AModularPlayerController::SetScreenLayout(UScreenLayout* InScreenLayout)
{
	ScreenLayout = InScreenLayout;
	OnScreenLayoutAdded.Broadcast();
}

void AModularPlayerController::ScreenLayoutReady_Implementation()
{
	///
}

void AModularPlayerController::BeginPlay()
{
	Super::BeginPlay();

	OnScreenLayoutAdded.AddUniqueDynamic(this, &ThisClass::ScreenLayoutReady);
	GetLocalPlayer()->GetSubsystem<UScreenLayoutManagerSystem>()->SetupScreenLayoutForPlayer();
}
