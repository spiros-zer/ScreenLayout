// Copyright 2024 Spyridon Zervos


#include "ScreenLayoutManagerSystem.h"

#include "ScreenLayout.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Player/ModularPlayerController.h"

bool UScreenLayoutManagerSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<ULocalPlayer>(Outer)->GetGameInstance()->IsDedicatedServerInstance())
	{
		TArray<UClass*> ChildClasses;
		GetDerivedClasses(GetClass(), ChildClasses, false);

		// Only create an instance if there is no override implementation defined elsewhere
		return ChildClasses.Num() == 0;
	}
	return false;
}

void UScreenLayoutManagerSystem::SetupScreenLayoutForPlayer()
{
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	Streamable.RequestAsyncLoad(ScreenLayoutClass.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &ThisClass::OnScreenLayoutLoaded));
}

void UScreenLayoutManagerSystem::OnScreenLayoutLoaded()
{
	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (APlayerController* PlayerController = LocalPlayer->GetPlayerController(GetWorld()))
		{
			if (UScreenLayout* ScreenLayout = Cast<UScreenLayout>(CreateWidget(PlayerController,
					ScreenLayoutClass.Get(), FName(TEXT("ScreenLayout")))))
			{
				ScreenLayout->AddToViewport();
				
				if (AModularPlayerController* ModularPlayerController = Cast<AModularPlayerController>(PlayerController))
				{
					ModularPlayerController->SetScreenLayout(ScreenLayout);
					
					if (PrimaryWidgetClassForState && StateTag.IsValid())
					{
						ScreenLayout->PushWidgetToLayer(StateTag, PrimaryWidgetClassForState.LoadSynchronous());
					}
				}
			}
		}
	}
}
