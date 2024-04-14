// Copyright 2024 Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "ScreenLayoutManagerController.generated.h"

class UScreenLayout;

/**
 * Interface to provide the attached controller power over the screen layout.
 */
UINTERFACE(MinimalAPI, meta = (Blueprintable))
class UScreenLayoutManagerController : public UInterface
{
	GENERATED_BODY()
};

class IScreenLayoutManagerController
{
	GENERATED_BODY()

public:
	
	/** Meant to invoke the screen layout's PushWidgetToLayer. */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ScreenLayout")
	bool PushWidgetToLayer(UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag InLayerTag,
	                       TSubclassOf<UCommonActivatableWidget> InActivatableWidgetClass);
};
