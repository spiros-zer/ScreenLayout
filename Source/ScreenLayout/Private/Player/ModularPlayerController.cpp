// Copyright 2024 Spyridon Zervos


#include "Player/ModularPlayerController.h"

#include "ScreenLayoutManagerSystem.h"
#include "Game/ModularGameMode.h"
#include "Kismet/GameplayStatics.h"

void AModularPlayerController::InitState()
{
	if (AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this))
	{
		if (const AModularGameMode* ModularGameMode = Cast<AModularGameMode>(GameModeBase))
		{
			if (UScreenLayoutManagerSystem* ScreenLayoutManagerSystem = GetLocalPlayer()->GetSubsystem<UScreenLayoutManagerSystem>())
			{
				ScreenLayoutManagerSystem->SetStateTag(ModularGameMode->GetStateTag());
				ScreenLayoutManagerSystem->SetPrimaryWidgetClassForState(ModularGameMode->GetPrimaryWidgetClassForState());
			}
		}
	}
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
	
	/**
	 * The call to InitState HAS TO take pecedence over the SetupScreenLayoutForPlayer() due to the fact that in a
	 * different scenarion the state tag and primary widget will not have been set.
	 */
	InitState();
	
	if (UScreenLayoutManagerSystem* ScreenLayoutManagerSystem = GetLocalPlayer()->GetSubsystem<UScreenLayoutManagerSystem>())
	{
		ScreenLayoutManagerSystem->SetupScreenLayoutForPlayer();
	}
}
