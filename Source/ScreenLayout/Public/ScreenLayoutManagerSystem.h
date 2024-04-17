// Copyright 2024 Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ScreenLayoutManagerSystem.generated.h"

class UCommonActivatableWidget;
class UScreenLayout;

/**
 * The heart of the screen layout plugin. Manages the proper function of the screen layout. It also provides a means of
 * setting states which refer to game concepts such as game menu, game HUD etc. These states have to have a correlation
 * with a gameplay tag. Based on that, it has the ability to display the proper first (primary) widget that should be
 * shown in said state.
 */
UCLASS(Config = ScreenLayout)
class SCREENLAYOUT_API UScreenLayoutManagerSystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	/** Allows this subsystem to be created or not depending on if there are derived classes. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
	UFUNCTION(BlueprintCallable, Category = "Screen")
	virtual void SetupScreenLayoutForPlayer();
	
	UFUNCTION(BlueprintGetter, Category = "Screen")
	TSoftClassPtr<UScreenLayout> GetScreenLayoutClass() const {return ScreenLayoutClass;}
	
	UFUNCTION(BlueprintCallable, Category = "Screen|State")
	void SetPrimaryWidgetForState(const TSoftClassPtr<UCommonActivatableWidget> InPrimaryWidget)
	{
		PrimaryWidgetClassForState = InPrimaryWidget;
	}

	UFUNCTION(BlueprintGetter, Category = "Screen|State")
	TSoftClassPtr<UCommonActivatableWidget> GetPrimaryWidgetForState() const {return PrimaryWidgetClassForState;}

	UFUNCTION(BlueprintCallable, Category = "Screen|State")
	void SetState(const FGameplayTag InStateTag) {StateTag = InStateTag;}
	
	UFUNCTION(BlueprintCallable, BlueprintGetter, Category = "Screen|State")
	FGameplayTag GetState() const {return StateTag;}

protected:

	virtual void OnScreenLayoutLoaded();

	/**
	 * The screen layout class that will be added to the player controller. The default provided contains three
	 * UCommonActivatableWidgetStacks 
	 */
	UPROPERTY(Config, BlueprintGetter = "GetScreenLayoutClass", Category = "Screen")
	TSoftClassPtr<UScreenLayout> ScreenLayoutClass;

	/** The current state at which the player has the screen layout. This could be game menu, game HUD etc. */
	UPROPERTY(BlueprintGetter = "GetState", Category = "Screen|State")
	FGameplayTag StateTag{};

	/** The first widget that will be shown in for this state. */
	UPROPERTY(BlueprintGetter = "GetPrimaryWidgetForState", Category = "Screen|State")
	TSoftClassPtr<UCommonActivatableWidget> PrimaryWidgetClassForState{};
};
