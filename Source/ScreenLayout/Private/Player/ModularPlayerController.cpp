// Copyright 2024 Spyridon Zervos


#include "Player/ModularPlayerController.h"

#include "ScreenLayout.h"
#include "ScreenLayoutManagerSystem.h"

bool AModularPlayerController::PushWidgetToLayer(FGameplayTag InLayerTag,
	TSubclassOf<UCommonActivatableWidget> InActivatableWidgetClass)
{
	return IsValid(ScreenLayout->PushWidgetToLayer(InLayerTag, InActivatableWidgetClass));
}

void AModularPlayerController::SetScreenLayout(UScreenLayout* InScreenLayout)
{
	ScreenLayout = InScreenLayout;
	OnScreenLayoutAdded.Broadcast();
}

void AModularPlayerController::BeginPlay()
{
	Super::BeginPlay();

	OnScreenLayoutAdded.AddUniqueDynamic(this, &ThisClass::ScreenLayoutReady);
	
	if (UScreenLayoutManagerSystem* ScreenLayoutManagerSystem = GetLocalPlayer()->GetSubsystem<UScreenLayoutManagerSystem>())
	{
		ScreenLayoutManagerSystem->SetupScreenLayoutForPlayer();
	}
}
