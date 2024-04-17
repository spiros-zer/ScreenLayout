// Copyright 2024 Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameplayTagContainer.h"
#include "ModularGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SCREENLAYOUT_API AModularGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintSetter, Category = "Screen|State")
	void SetStateTag(const FGameplayTag InStateTag) {StateTag = InStateTag;}
	
	UFUNCTION(BlueprintGetter, Category = "Screen|State")
	FGameplayTag GetStateTag() const {return StateTag;}
	
	UFUNCTION(BlueprintSetter, Category = "Screen|State")
	void SetPrimaryWidgetClassForState(const TSoftClassPtr<UCommonActivatableWidget> InPrimaryWidget)
	{
		PrimaryWidgetClassForState = InPrimaryWidget;
	}

	UFUNCTION(BlueprintGetter, Category = "Screen|State")
	TSoftClassPtr<UCommonActivatableWidget> GetPrimaryWidgetClassForState() const {return PrimaryWidgetClassForState;}

private:
	
	/** The current state at which the player has the screen layout. This could be game menu, game HUD etc. */
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintGetter = "GetStateTag",
		BlueprintSetter = "SetStateTag",
		Category = "Screen|State",
		meta = (Categories = "UI.Layer")
		)
	FGameplayTag StateTag{};

	/** The first widget that will be shown in for this state. */
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintGetter = "GetPrimaryWidgetClassForState",
		BlueprintSetter = "SetPrimaryWidgetClassForState",
		Category = "Screen|State"
		)
	TSoftClassPtr<UCommonActivatableWidget> PrimaryWidgetClassForState{};
};